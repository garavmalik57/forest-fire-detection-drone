#include <SPI.h>
#include <LoRa.h>
#include "DHT.h"

// ---------- pins (your mapping) ----------
#define LORA_SCK   5
#define LORA_MISO  19
#define LORA_MOSI  27
#define LORA_SS    18
#define LORA_RST   14
#define LORA_DIO0  26
#define LORA_BAND  433E6

#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ135_PIN 34   // ADC1_6

// resistor divider on MQ-135 output: R1 above, R2 to GND
const float R1 = 5600.0;   // top resistor (ohms)
const float R2 = 10000.0;  // bottom resistor (ohms)

// Node ID
const char *nodeId = "node01";

// DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }
  Serial.println("\n=== ESP32 LoRa Sensor Transmitter ===");

// init DHT
  dht.begin();

// SPI + LoRa
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

Serial.print("Initializing LoRa @ "); Serial.print(LORA_BAND/1e6); Serial.println(" MHz...");
  if (!LoRa.begin(LORA_BAND)) {
    Serial.println("❌ LoRa init failed. Check wiring/power/antenna.");
    while (1) delay(500);
  }
  LoRa.setTxPower(17);
  Serial.println("✅ LoRa initialized. Starting sensor loop...");
  delay(200);
}

void loop() {
  // --- read sensors ---
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

if (isnan(temperature) || isnan(humidity)) {
    Serial.println("⚠️ DHT11 read failed — will retry next loop.");
    delay(2000);
    return;
  }

int raw = analogRead(MQ135_PIN); // 0..4095 (ESP32 ADC)
  const float ADC_MAX = 4095.0;
  const float VREF = 3.3; // approximate ADC reference after divider
  float v_adc = (raw / ADC_MAX) * VREF;
  float v_sensor = v_adc * ((R1 + R2) / R2); // recover sensor voltage pre-divider

// --- build packet ---
  String packet = String("id:") + nodeId +
                  ",T:" + String(temperature, 2) +
                  ",H:" + String(humidity, 2) +
                  ",MQ:" + String(raw) +
                  ",Vs:" + String(v_sensor, 3);

// --- send via LoRa ---
  LoRa.beginPacket();
  LoRa.print(packet);
  LoRa.endPacket();

// --- serial debug ---
  Serial.println("----------------------------------");
  Serial.print("Sent: "); Serial.println(packet);
  Serial.print("Raw ADC: "); Serial.print(raw);
  Serial.print("  V_adc: "); Serial.print(v_adc, 3);
  Serial.print(" V  V_sensor: "); Serial.print(v_sensor, 3); Serial.println(" V");
  Serial.println("----------------------------------");

delay(3000); // 3s between sends
}