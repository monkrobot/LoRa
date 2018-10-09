#ifndef receiver_h
#define receiver_h

#include <SSD1306.h> // alias for `#include "SSD1306Wire.h"`
#include <SPI.h>
#include <LoRa.h>

class Receiver
{
  public:
    Receiver(int receiver_num);
    void receiver();
};



#endif