# ZipIt WESO timer 

## Hardware

[XIAO ESP32C6](https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/)

Treedix IR Break Beam Sensor 5MM LEDs Counting Module Split Through-Beam Photoelectric Switch

## ESP Library
URL: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

ESP32 by Espressif Systems
Version: 3.1.1

## LIttleFS Upload Tool

Use PlatformIO to upload the LittleFS filesystem to the ESP32.

```bash
pio run -t uploadfs
```

## Wiring

[XIAO ESP32C6 Pin Description](https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/)


ESP32 PIN | Device                | Pin  | Pin Description | Color
----------|-----------------------|------|-----------------| ------
D0        | IR Break Beam Start   | X    | Signal          | white/green
5V        | IR Break Beam Start   | X    | VCC             | red
GND       | IR Break Beam Start   | X    | GND             | black
5V        | IR LED Start          | X    | VCC             | red
GND       | IR LED Start          | X    | GND             | black
D2        | IR Break Beam Stop    | X    | Signal          | white
5V        | IR Break Beam Stop    | X    | GND             | black
GND       | IR Break Beam Stop    | X    | VCC             | red
5V        | IR LED Stop           | X    | VCC             | red
GND       | IR LED Stop           | X    | GND             | black

## Setup

1. Connect the wiring harness to the sensors on the brackets with ESP32C6 on side of the lower bracket.
2. Connect the device you will be using to display the timer to the Wifi SSID named `ZipIt`.
3. Open a web browser and navigate to 192.168.4.1.
 

## wsl USB connection

Find the USB device to connect to the WSL2 VM

```bash
usbipd list
```
Bind and attach the device to the WSL2 VM
```bash
usbipd bind --busid=1-4
usbipd attach --wsl --busid 1-4
```