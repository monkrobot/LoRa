#ifndef sender_h
#define sender_h

#include <SSD1306.h> // alias for `#include "SSD1306Wire.h"`
#include <SPI.h>
#include <LoRa.h>

class Sender
{
  public:
    Sender(int sender_num);
    void sender();
};


#endif