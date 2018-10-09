#include <SSD1306.h> // alias for `#include "SSD1306Wire.h"`

#include <SPI.h>
#include <LoRa.h>

#include "sender.h"

Sender::Sender(int sender_num)
{
}

void Sender::sender()
{
  const uint32_t STEP_DURATION = 2000; // 2 sec.
  uint32_t lastStep = 0;

  static uint32_t counter = 0;
  
  if ((! lastStep) || (millis() - lastStep >= STEP_DURATION)) {
    Serial.print(F("Sending packet: "));
    Serial.println(counter);

    // send packet
    LoRa.beginPacket();
    LoRa.print(F("Hello "));
    LoRa.print(++counter);
    LoRa.print(F(" time(s)"));
    LoRa.endPacket();

    lastStep = millis();
  }
};