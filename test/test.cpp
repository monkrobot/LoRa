#include <SSD1306.h> // alias for `#include "SSD1306Wire.h"`

#include <SPI.h>
#include <LoRa.h>

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

const uint32_t STEP_DURATION = 2000; // 2 sec.

uint32_t lastStep = 0;

//Receiver
uint32_t lastPacket = 0;

//
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
  static uint32_t counter = 0;
  static bool lastBtn = false;
  //static bool lowContrast = false;
  bool btn = ! digitalRead(BTN);
  //Serial.println("Sending");

  if (btn != lastBtn) {
    if (btn) {
      display.setContrast(63);
      display.displayOn();
      lastLight = millis();
      //lowContrast = false;
    }
    lastBtn = btn;
  }
  //Display Off
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

  if ((! lastStep) || (millis() - lastStep >= STEP_DURATION)) {
    Serial.print(F("Sending packet: "));
    Serial.println(counter);

    display.clear();
    display.drawString(0, 0, F("Sending packet"));
    display.drawString(50, 15, String(counter));
    display.display();

    // send packet
    LoRa.beginPacket();
    LoRa.print(F("Hello "));
    LoRa.print(++counter);
    LoRa.print(F(" time(s)"));
    LoRa.endPacket();

    digitalWrite(LED, HIGH); // turn the LED on

    lastStep = millis();
  } else {
    //if (millis() - lastStep >= 1000) {
    //  digitalWrite(LED, LOW); // turn the LED off
    //}
  }

  //Receiver
  //if (lastPacket && (millis() - lastPacket >= 1000)) {
  //  digitalWrite(LED, LOW);
  //}

  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packets
    Serial.print(F("Received packet: \""));

    display.clear();
    display.drawString(0, 15, F("Received packet:"));

    // read packet
    while (LoRa.available()) { //Returns number of bytes available for reading.
      String data = LoRa.readString();
      Serial.print(data);
      display.drawString(0, 30, data);
    }

    // print RSSI of packet (мощность радиосигнала)
    Serial.print(F("\" with RSSI "));
    Serial.print(LoRa.packetRssi());
    Serial.print(F(" with SNR "));
    Serial.println(LoRa.packetSnr());
    // display.drawString(0, 45, "RSSI: ");
    // display.drawString(50, 45, (String)LoRa.packetRssi());

    display.drawString(0, 45, (String)LoRa.packetRssi() + F("dB (") + (String)LoRa.packetSnr() + F("dB)"));
    display.display();

    digitalWrite(LED, HIGH);
    lastPacket = millis();
  }
}































/*
 Repeat timer example
 This example shows how to use hardware timer in ESP32. The timer calls onTimer
 function every second. The timer can be stopped with button attached to PIN 0
 (IO0).
 This example code is in the public domain.
 */

// Stop button is attached to PIN 0 (IO0)

#include <SSD1306.h> // alias for `#include "SSD1306Wire.h"`

#include <SPI.h>
#include <LoRa.h>

#include <receiver.h>
#include <sender.h>

#define BTN_STOP_ALARM    0

hw_timer_t * timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile uint32_t isrCounter = 0;
volatile uint32_t lastIsrAt = 0;

int flag = 1;

void IRAM_ATTR onTimer(){
  // Increment the counter and set the time of ISR
  portENTER_CRITICAL_ISR(&timerMux);
  isrCounter++;
  lastIsrAt = millis();
  portEXIT_CRITICAL_ISR(&timerMux);
  // Give a semaphore that we can check in the loop
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
  // It is safe to use digitalRead/Write here if you want to toggle an output
}

void setup() {
  Serial.begin(9600);

  // Set BTN_STOP_ALARM to input mode
  pinMode(BTN_STOP_ALARM, INPUT);

  // Create semaphore to inform us when the timer has fired
  timerSemaphore = xSemaphoreCreateBinary();

  // Use 1st timer of 4 (counted from zero).
  // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
  // info).
  timer = timerBegin(0, 80, true);

  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &onTimer, true);

  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter)
  timerAlarmWrite(timer, 1000000, true);

  // Start an alarm
  timerAlarmEnable(timer);
}

void loop() {
  // If Timer has fired
  //if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
  //  uint32_t isrCount = 0, isrTime = 0;
  //  // Read the interrupt count and time
  //  portENTER_CRITICAL(&timerMux);
  //  isrCount = isrCounter;
  //  isrTime = lastIsrAt;
  //  portEXIT_CRITICAL(&timerMux);
  //  // Print it
  //  Serial.print("onTimer no. ");
  //  Serial.print(isrCount);
  //  Serial.print(" at ");
  //  Serial.print(isrTime);
  //  Serial.println(" ms");
  //  Serial.println("Timer");
  //  };

  while(lastIsrAt<lastIsrAt+1000){
    Serial.println(lastIsrAt);
  };


  // If button is pressed
  if (digitalRead(BTN_STOP_ALARM) == LOW) {
    // If timer is still running
    if (timer) {
      // Stop and free timer
      timerEnd(timer);
      timer = NULL;
    }
  }
}