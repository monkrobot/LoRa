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

// #define BAND 429E6 // 915E6
#define BAND 433E6
#define spreadingFactor 9
// #define SignalBandwidth 62.5E3
#define SignalBandwidth 31.25E3
#define preambleLength 8
#define codingRateDenominator 8

const uint32_t LOWCONTRAST_TIME = 25000; // 25 sec.
const uint32_t DISPLAYOFF_TIME = 30000; // 30 sec.

uint32_t lastLight;

const uint32_t STEP_DURATION = 2000; // 2 sec.

uint32_t lastStep = 0;
*/

/*
void setup() {
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT); // Send success, LED will bright 1 second

  Serial.begin(115200);
  while (! Serial); // If just the the basic function, must connect to a computer
  Serial.println();

// Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 5, F("LoRa Sender"));
  display.display();

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  Serial.println(F("LoRa Sender"));
  if (! LoRa.begin(BAND)) {
    Serial.println(F("Starting LoRa failed!"));
    display.drawString(0, 20, F("Starting LoRa failed!"));
    display.display();
    while (1);
  }

  Serial.print(F("LoRa Spreading Factor: "));
  Serial.println(spreadingFactor);
  LoRa.setSpreadingFactor(spreadingFactor);

  Serial.print(F("LoRa Signal Bandwidth: "));
  Serial.println(SignalBandwidth);
  LoRa.setSignalBandwidth(SignalBandwidth);

  LoRa.setCodingRate4(codingRateDenominator);
  LoRa.setPreambleLength(preambleLength);

  Serial.println(F("LoRa Initialization OK!"));
  display.drawString(0, 20, F("LoRa Initializing OK!"));
  display.display();

  display.setFont(ArialMT_Plain_16);

  delay(2000);

  display.setContrast(63);

  lastLight = millis();
}
*/


void sender() {
  Serial.println("Sender");
  const uint32_t STEP_DURATION = 2000; // 2 sec.
  uint32_t lastStep = 0;

  static uint32_t counter = 0;
  //static bool lastBtn = false;
  //static bool lowContrast = false;
  //bool btn = ! digitalRead(BTN);
  //Serial.println("Sending");
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
//
  if ((! lastStep) || (millis() - lastStep >= STEP_DURATION)) {
    Serial.print(F("Sending packet: "));
    Serial.println(counter);

    //display.clear();
    //display.drawString(0, 5, F("Sending packet"));
    //display.drawString(50, 30, String(counter));
    //display.display();

    // send packet
    LoRa.beginPacket();
    LoRa.print(F("Hello "));
    LoRa.print(++counter);
    LoRa.print(F(" time(s)"));
    LoRa.endPacket();

    //digitalWrite(LED, HIGH); // turn the LED on

    lastStep = millis();
  } /*else {
    if (millis() - lastStep >= 1000) {
      digitalWrite(LED, LOW); // turn the LED off
    }
  }*/
}
