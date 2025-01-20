#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "src/TimeStamp/src/TimeStamp.hpp"
#include <stdint.h>

#include "html.h"

const char* ssid = "ZipIt";
const char* password = "";

const int startPin = D0;
const int stopPin = D2;

IPAddress local_IP(192, 168, 4, 2);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

WebServer server(80);

TimeStamp startTime;
TimeStamp stopTime;


void setup() {
  Serial.begin(115200);

  pinMode(startPin, INPUT);  // Set LED pin as output
  pinMode(stopPin, INPUT);   // Set button pin as input

  pinMode(startPin, INPUT_PULLUP);
  pinMode(stopPin, INPUT_PULLUP);

  startTime.setStamp(millis());
  stopTime.setStamp(startTime.getStamp());

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

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
          NULL,         // Task handle
          0             // Core to run the task on (0 or 1)
  );

  // Initialize core 1
  xTaskCreatePinnedToCore(
          taskCore1,    // Function to run on core 1
          "taskCore1",  // Name of the task
          10000,        // Stack size (bytes)
          NULL,         // Parameter to pass to the task
          1,            // Priority
          NULL,         // Task handle
          1             // Core to run the task on (0 or 1)
  );
}

void loop() {}

void taskCore0(void* parameter) {
  // Code to run on core 0
  while (true) {
    bool isStart = digitalRead(startPin);
    if (isStart == LOW) {
      Serial.println(">>> Start time set");
      startTime.setStamp(millis());
    }

    bool isStop = digitalRead(stopPin);
    if (isStop == LOW) {
      Serial.println("<<< Stop time set");
      stopTime.setStamp(millis());
      ProcessUpdates();
    }
  }
}

void taskCore1(void* parameter) {
  // Code to run on core 1
  while (true) {

    server.handleClient();
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
  server.send(200, "text/html", char_html);
  Serial.println("got request from device");
}