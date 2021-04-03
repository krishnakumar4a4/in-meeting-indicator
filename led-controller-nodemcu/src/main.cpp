#include <Arduino.h>
#include <WiFiManager.h>
#include "RestClient.h"
#include <ESP8266HTTPClient.h>
#include "Config.h"

#define MICLED D5
#define CAMERALED D6

WiFiManager wifiManager;
String hostname;

int readMicStatus();
int readCameraStatus();
String getServerHostname();

void setup() {
  pinMode(MICLED, OUTPUT);
  pinMode(CAMERALED, OUTPUT);

  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(9600);
  //reset settings - wipe credentials for testing
  //wm.resetSettings();

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result
	// wifiManager.setConfigPortalBlocking(false);

  if(!wifiManager.autoConnect(HOTSPOT_SSID, HOTSPOT_PWD)) {
        Serial.println("Failed to connect");
        delay(5000);
        ESP.restart();
  } else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
  }
}

void loop() {
	// wifiManager.process();
  if (readMicStatus() == 1) {
    digitalWrite(MICLED, HIGH);
  } else {
    digitalWrite(MICLED, LOW);
  }

  if (readCameraStatus() == 1) {
    digitalWrite(CAMERALED, HIGH);
  } else {
    digitalWrite(CAMERALED, LOW);
  }

  delay(2000);
}

int readMicStatus() {
  int ret = -1;
  HTTPClient http;
  http.begin(MIC_ENDPOINT);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.print("mic status: ");
    Serial.println(payload);
    if (payload == "true") {
      ret = 1;
    } else {
      ret = 0;
    }
  }
  http.end();
  return ret;
}


int readCameraStatus() {
  int ret = -1;
  HTTPClient http;
 
  http.begin(CAMERA_ENDPOINT);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.print("camera status: ");
    Serial.println(payload);
    if (payload == "true") {
      ret = 1;
    } else {
      ret = 0;
    }
  }
  http.end();
  return ret;
}