#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include "arduino_secrets.h"

// Confirmed DRV8833 wiring:
// MKR pin 5 -> AIN1
// MKR pin 4 -> AIN2
// MKR VCC (3.3 V) -> SLP
// MKR GND -> DRV8833 GND
const int AIN1 = 5;
const int AIN2 = 4;

const unsigned int UDP_PORT = 4210;
const unsigned long FAILSAFE_MS = 500;

WiFiUDP udp;
unsigned long lastDrivePacketMs = 0;
bool motorRunning = false;

void motorForward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  motorRunning = true;
}

void motorStop() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  motorRunning = false;
}

void connectWiFi() {
  motorStop();

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    Serial.print(".");
    delay(3000);
  }

  Serial.println();
  Serial.println("Wi-Fi connected.");
  Serial.print("MKR IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  motorStop();

  Serial.begin(115200);
  unsigned long serialWaitStart = millis();
  while (!Serial && millis() - serialWaitStart < 4000) {
    // Give the USB serial port a moment to appear, but do not wait forever.
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("ERROR: WiFiNINA module not detected.");
    while (true) {
      motorStop();
      delay(1000);
    }
  }

  connectWiFi();

  udp.begin(UDP_PORT);
  Serial.print("Listening for UDP motor commands on port ");
  Serial.println(UDP_PORT);
  Serial.println("Hold SPACE on the laptop controller to run the motor.");
}

void loop() {
  // If Wi-Fi drops, stop first. Never leave the motor running on a lost link.
  if (WiFi.status() != WL_CONNECTED) {
    motorStop();
    connectWiFi();
    udp.stop();
    udp.begin(UDP_PORT);
  }

  int packetSize = udp.parsePacket();
  if (packetSize > 0) {
    char command = 0;
    int bytesRead = udp.read(&command, 1);

    if (bytesRead == 1) {
      if (command == '1') {
        motorForward();
        lastDrivePacketMs = millis();
      } else if (command == '0') {
        motorStop();
        lastDrivePacketMs = millis();
      }
    }

    // Discard any remaining bytes in this packet.
    while (udp.available()) {
      udp.read();
    }
  }

  // Safety watchdog: laptop sends repeated '1' packets while SPACE is held.
  // If packets stop arriving, the motor shuts off automatically.
  if (motorRunning && millis() - lastDrivePacketMs > FAILSAFE_MS) {
    motorStop();
  }
}
