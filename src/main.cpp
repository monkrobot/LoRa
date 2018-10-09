#include <SSD1306.h> // alias for `#include "SSD1306Wire.h"`

#include <SPI.h>
#include <LoRa.h>
#include <receiver.h>
#include <sender.h>

#define BTN 0
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


uint32_t timer_loop = millis();
int receiver_time = 5000;
int sender_time = 5000;

//
void setup() {
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT); // Send success, LED will bright 1 second

  Serial.begin(9600);
  while (! Serial); // If just the the basic function, must connect to a computer
  Serial.println();

// Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 5, F("LoRa Sender"));
  display.display();

  display.drawString(0, 20, F("LoRa Receiver"));
  display.display();

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  Serial.println(F("LoRa Sender"));

  if (! LoRa.begin(BAND)) {
    Serial.println(F("Starting LoRa failed!"));
    display.drawString(0, 40, F("Starting LoRa failed!"));
    display.display();
    while (1);
  }

  Serial.println(F("LoRa Initialization OK!"));
  Serial.print(F("LoRa Frequency: "));
  Serial.println(BAND);

  Serial.print(F("LoRa Spreading Factor: "));
  Serial.println(spreadingFactor);
  LoRa.setSpreadingFactor(spreadingFactor); //Spreading factor affects how far apart the radio's transmissions are,
                                            //across the available bandwidth.
                                            //Radios with different spreading factors will not receive each
                                            //other's transmissions.
                                            //This is one way you can filter out radios you want to ignore,
                                            //without making an addressing scheme.
                                             
  Serial.print(F("LoRa Signal Bandwidth: "));
  Serial.println(SignalBandwidth);
  LoRa.setSignalBandwidth(SignalBandwidth); //Change the signal bandwidth (пропускная способность) of the radio.

  LoRa.setCodingRate4(codingRateDenominator);
  LoRa.setPreambleLength(preambleLength);

  display.drawString(0, 40, F("LoRa Initializing OK!"));
  display.display();

  display.setFont(ArialMT_Plain_16);
  delay(1500);
  display.setContrast(63);
}

void loop() {
  

  int timer_l = timer_loop;
  while (timer_loop < timer_l+receiver_time)
  {
    Receiver receiver_instance = Receiver(1);
    receiver_instance.receiver();

    timer_loop = millis();
  };
  
  timer_l = timer_loop;
  while (timer_loop < timer_l+sender_time)
  {
    Sender sender_instance = Sender(1);
    sender_instance.sender();

    timer_loop = millis();
  };
}