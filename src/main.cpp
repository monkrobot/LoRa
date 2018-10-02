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

const uint32_t LOWCONTRAST_TIME = 25000; // 25 sec.
const uint32_t DISPLAYOFF_TIME = 30000; // 30 sec.

uint32_t lastLight;

//uint32_t receiver_loop;
//uint32_t sender_loop;

const uint32_t STEP_DURATION = 2000; // 2 sec.

uint32_t lastStep = 0;

//Receiver
uint32_t lastPacket = 0;
int last_rec_l = 0;
int last_send_l = 0;

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

  // Receiver
  Serial.println(F("LoRa Receiver"));
  display.drawString(0, 20, F("LoRa Receiver"));
  display.display();

  //
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  Serial.println(F("LoRa Sender"));

  if (! LoRa.begin(BAND)) {
    Serial.println(F("Starting LoRa failed!"));
    display.drawString(0, 40, F("Starting LoRa failed!"));
    display.display();
    while (1);
  }

  //Receiver
  Serial.println(F("LoRa Initialization OK!"));

  Serial.print(F("LoRa Frequency: "));
  Serial.println(BAND);

  //
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

  Serial.println(F("LoRa Initialization OK!"));
  display.drawString(0, 40, F("LoRa Initializing OK!"));
  display.display();

  display.setFont(ArialMT_Plain_16);

  delay(1500);

  display.setContrast(63);

  lastLight = millis();
  
  
}

void loop() {
  uint32_t receiver_loop = millis();
  
  //for (int i=0;i<10000;i++){
  //  receiver();
  //}
  while ((receiver_loop - last_rec_l) < 2000)
  {
    //Serial.println("Receiver");
    //Serial.println(receiver_loop);
    //Serial.println(last_rec_l);
    receiver_loop = millis();
    receiver();
  };
  
  //delay(100);

  uint32_t sender_loop = millis();
  while ((sender_loop - last_send_l) < 5000)
  {
    Serial.println("Sender");
    Serial.println(sender_loop);
    Serial.println(last_send_l);
    sender_loop = millis();
    sender();
  };
  last_rec_l = millis();
  last_send_l = millis();
}