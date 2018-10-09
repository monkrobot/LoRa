#include <SSD1306.h> // alias for `#include "SSD1306Wire.h"`

#include <SPI.h>
#include <LoRa.h>

#include "receiver.h"

Receiver::Receiver(int receiver_num)
{
}

void Receiver::receiver()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packets
    Serial.print(F("Received packet: \""));

    // read packet
    while (LoRa.available()) {
      String data = LoRa.readString();
      Serial.print(data);
    }

    // print RSSI of packet
    Serial.print(F("\" with RSSI "));
    Serial.print(LoRa.packetRssi());
    Serial.print(F(" with SNR "));
    Serial.println(LoRa.packetSnr());
  }
};