#include <SSD1306.h> // alias for `#include "SSD1306Wire.h"`

#include <SPI.h>
#include <LoRa.h>

/*#define BTN 0
#define LED 25

SSD1306 display;

// WIFI_LoRa_32 ports
#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_CS 18
#define LORA_RST 14
#define LORA_IRQ 26

// LoRa Settings 
#define BAND 433E6
#define spreadingFactor 9
// #define SignalBandwidth 62.5E3
#define SignalBandwidth 31.25E3

#define codingRateDenominator 8

const uint32_t LOWCONTRAST_TIME = 25000; // 25 sec.
const uint32_t DISPLAYOFF_TIME = 30000; // 30 sec.

uint32_t lastLight;

uint32_t lastPacket = 0;*/

/*
void setup() {
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  Serial.begin(115200);
  while (! Serial); //if just the the basic function, must connect to a computer
  Serial.println();

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  Serial.println(F("LoRa Receiver"));
  display.drawString(0, 5, F("LoRa Receiver"));
  display.display();

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);

  if (! LoRa.begin(BAND)) {
    Serial.println(F("Starting LoRa failed!"));
    display.drawString(0, 25, F("Starting LoRa failed!"));
    display.display();
    while (1);
  }
  Serial.println(F("LoRa Initialization OK!"));

  Serial.print(F("LoRa Frequency: "));
  Serial.println(BAND);

  Serial.print(F("LoRa Spreading Factor: "));
  Serial.println(spreadingFactor);
  LoRa.setSpreadingFactor(spreadingFactor);

  Serial.print(F("LoRa Signal Bandwidth: "));
  Serial.println(SignalBandwidth);
  LoRa.setSignalBandwidth(SignalBandwidth);

  LoRa.setCodingRate4(codingRateDenominator);

  display.drawString(0, 25, F("LoRa Initializing OK!"));
  display.display();

  display.setFont(ArialMT_Plain_16);

  lastLight = millis();
}
*/

class Receiver
{
  
  void receiver() {
    //Serial.println("Receiver");
    //static bool lowContrast = false;
    //static bool lastBtn = false;
    //bool btn = ! digitalRead(BTN);
  //
    //if (btn != lastBtn) {
    //  if (btn) {
    //    display.setContrast(63);
    //    display.displayOn();
    //    lastLight = millis();
    //    lowContrast = false;
    //  }
    //  lastBtn = btn;
    //}
  //
    //if (lastLight) {
    //  if (millis() - lastLight >= DISPLAYOFF_TIME) {
    //    display.displayOff();
    //    lastLight = 0;
    //  } else if (millis() - lastLight >= LOWCONTRAST_TIME) {
    //    if (! lowContrast) {
    //      display.setContrast(15);
    //      lowContrast = true;
    //    }
    //  }
    //}

    //if (lastPacket && (millis() - lastPacket >= 1000)) {
    //  digitalWrite(LED, LOW);
    //}

    // try to parse packet
    int packetSize = LoRa.parsePacket();
    //Serial.print("packetSize ");
    //Serial.println(packetSize);
    if (packetSize) {
      // received a packets
      Serial.print(F("Received packet: \""));

      //display.clear();
      //display.drawString(0, 0, F("Received packet:"));

      // read packet
      while (LoRa.available()) {
        String data = LoRa.readString();
        Serial.print(data);
        //display.drawString(0, 22, data);
      }

      // print RSSI of packet
      Serial.print(F("\" with RSSI "));
      Serial.print(LoRa.packetRssi());
      Serial.print(F(" with SNR "));
      Serial.println(LoRa.packetSnr());
      // display.drawString(0, 45, "RSSI: ");
      // display.drawString(50, 45, (String)LoRa.packetRssi());

      //display.drawString(0, 45, (String)LoRa.packetRssi() + F("dB (") + (String)LoRa.packetSnr() + F("dB)"));
      //display.display();

      //digitalWrite(LED, HIGH);
      //lastPacket = millis();
    }
  }

};