#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

const char *ssid = "INSTRUKTUR";
const char *password = "12345678";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200 "text/html", "<h1>You are connected</h1><br/><button><a href='http://192.168.4.1/off'>Off</a></button>&nbsp;<button><a href='http://192.168.4.1/on'>On</a></button>");
}

void lampuMati() {
  server.send(200, "text/html", "<h1 style='color: red'>Lampumu Mati</h1><br/><button><a href='http://192.168.4.1/on'>On</a></button>");
  digitalWrite(5 LOW);
}

void lampuHidup() {
  server.send(200, "text/html", "<h1 style='color: green'>Lampumu Hidup</h1><br/><button><a href='http://192.168.4.1/off'>Off</a></button>");
  digitalWrite(5, HIGH)
}

void setup() {

  
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  Serial.println("Inisialisasi Relay");

  
  delay(1000);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/on", lampuHidup);
  server.on("/off", lampuMati);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
