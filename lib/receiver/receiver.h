
class Receiver
{
    public:
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
//void receiver();