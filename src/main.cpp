#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <TimeStamp.hpp>
#include <stdint.h>
#include <LittleFS.h>

TaskHandle_t Task0;
TaskHandle_t Task1;


const int startPin = D0;
const int stopPin = D1;

WebServer server(80);

TimeStamp startTime;
TimeStamp stopTime;

int isStartPrev = 0;
int isStopPrev = 0;
bool startDetected = false;

void listLittleFsFiles() {
  Serial.println("Listing LittleFS files:");
  File root = LittleFS.open("/");
  File file = root.openNextFile();
  while (file) {
    Serial.print("FILE: ");
    Serial.print(file.name());
    Serial.print(" SIZE: ");
    Serial.println(file.size());
    file = root.openNextFile();
  }
}

void ProcessUpdates() {
  String reset = server.arg("reset");
  if (reset == "1" || reset == "True" || reset == "true") {
    startTime.setStamp(millis());
    stopTime.setStamp(startTime.getStamp());
  } else if (reset == "0" || reset == "False" || reset == "false") {
    Serial.println("Reset is false");
  }

  uint32_t delta = stopTime.getStamp() - startTime.getStamp();
  char zip_time[9];
  sprintf(zip_time, "%7.3f", delta / 1000.0);
  String s = "{\"zip_time\":" + String(zip_time) + "}";
  server.send(200, "application/json", s);
  Serial.println(s);
}

void ProcessRoot() {
  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  String fileContent = file.readString();
  file.close();
  // Serial.println(fileContent);
  server.send(200, "text/html", fileContent);
  Serial.println("got request from device");
}


void taskCore0(void* parameter) {
  // Code to run on core 0
  while (true) {
    int isStart = digitalRead(startPin);
    if (isStart == LOW && isStartPrev == HIGH) {
      Serial.println(">>> Start time set");
      startTime.setStamp(millis());
      stopTime.setStamp(millis());
      startDetected = true;
      ProcessUpdates();
    }
    isStartPrev = isStart;

    bool isStop = digitalRead(stopPin);

    if (isStop == LOW && isStopPrev == HIGH) {
      Serial.println("--- Gate tripped");
      if (startDetected) {
        Serial.println("<<< Stop time set");
        stopTime.setStamp(millis());
        startDetected = false;
        ProcessUpdates();
      }
    }
    isStopPrev = isStop;
  }
}

void taskCore1(void* parameter) {
  // Code to run on core 1
  while (true) {
    server.handleClient();
  }
}


void setup() {
  Serial.begin(115200);

  pinMode(startPin, INPUT);  // Set LED pin as output
  pinMode(stopPin, INPUT);   // Set button pin as input

  pinMode(startPin, INPUT_PULLUP);
  pinMode(stopPin, INPUT_PULLUP);

  startTime.setStamp(millis());
  stopTime.setStamp(startTime.getStamp());

  if (!LittleFS.begin(true)) {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // Check if the file exists
  if (LittleFS.exists("/index.html")) {
    Serial.println("File exists");
  } else {
    Serial.println("File does not exist");
  }

  IPAddress local_IP(192, 168, 4, 1);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 0, 0);
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  const char* ssid = "ZipIt";
  const char* password = "";
  WiFi.softAP(ssid, password);

  server.on("/", ProcessRoot);
  server.on("/update", ProcessUpdates);

  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());

  // Initialize core 0
  xTaskCreatePinnedToCore(
      taskCore0,    // Function to run on core 0
      "taskCore0",  // Name of the task
      10000,        // Stack size (bytes)
      NULL,         // Parameter to pass to the task
      1,            // Priority (0 = lowest, 1 = default, 2 = highest)
      &Task0,       // Task handle
      0             // Core0
  );

  // Initialize core 1
  xTaskCreatePinnedToCore(
      taskCore1,    // Function to run on core 1
      "taskCore1",  // Name of the task
      10000,        // Stack size (bytes)
      NULL,         // Parameter to pass to the task
      1,            // Priority
      &Task1,       // Task handle
      0             // Core1 - updated based on ESP32C6 LP core not addressable
  );
}

void loop() {}
