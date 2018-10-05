class Sender
{
    public:
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
};