// NodeMCU: receive LoRa, parse and POST JSON to local server (fixed HTTPClient API)
#include <SPI.h>
#include <LoRa.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* WIFI_SSID = "OPPO Reno8 T 5G";
const char* WIFI_PASS = "90909090";

#define LORA_SS   15
#define LORA_RST  16
#define LORA_DIO0 4
#define LORA_BAND 433E6

void setup() {
  Serial.begin(115200);
  delay(50);
  Serial.println("\nReceiver starting...");

  // Connect Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting WiFi");
  unsigned long t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t0 < 15000) {
    Serial.print(".");
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected: " + WiFi.localIP().toString());
  } else {
    Serial.println("\nWiFi connect failed - will keep running and try later.");
  }

  // Initialize LoRa
  SPI.begin(); // default HSPI pins on NodeMCU
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(LORA_BAND)) {
    Serial.println("LoRa init failed");
    while (1) delay(500);
  }
  LoRa.receive();
  Serial.println("LoRa ready");
}

String parseField(const String &s, const String &key) {
  int i = s.indexOf(key);
  if (i == -1) return String();
  i += key.length();
  int j = i;
  while (j < s.length() && s[j] != ',' && s[j] != ' ') j++;
  return s.substring(i, j);
}


void loop() {
  int packetSize = LoRa.parsePacket();
  if (!packetSize) { delay(5); return; }

  String packet = "";
  while (LoRa.available()) packet += (char)LoRa.read();
  packet.trim();
  Serial.println("Got: " + packet);

  String id = parseField(packet, "id:");
  String t  = parseField(packet, "T:");
  String h  = parseField(packet, "H:");
  String mq = parseField(packet, "MQ:");
  String vs = parseField(packet, "Vs:");
  if (vs.length() == 0) vs = parseField(packet, "V:");

  String json = "{";
  json += "\"node\":\"" + id + "\",";
  json += "\"temperature\":" + (t.length()?t:"null") + ",";
  json += "\"humidity\":" + (h.length()?h:"null") + ",";
  json += "\"mq_raw\":" + (mq.length()?mq:"null") + ",";
  json += "\"vsensor\":" + (vs.length()?vs:"null");
  json += "}";
  LoRa.receive();
}