#include "main.h"
#include <WiFi.h>

// SSID & Password
const char* ssid = "SensirionMA";  // Enter your SSID here
const char* password = "W1Fi4Employ33";  //Enter your Password here

void Setup_Wifi(){
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
}
