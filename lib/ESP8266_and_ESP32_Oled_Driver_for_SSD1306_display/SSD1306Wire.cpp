#include "SSD1306Wire.h"

void SSD1306Wire::display(void) {
  #ifdef OLEDDISPLAY_DOUBLE_BUFFER
	uint8_t minBoundY = ~0;
	uint8_t maxBoundY = 0;

	uint8_t minBoundX = ~0;
	uint8_t maxBoundX = 0;
	uint8_t x, y;

	// Calculate the Y bounding box of changes
	// and copy buffer[pos] to buffer_back[pos];
	for (y = 0; y < (DISPLAY_HEIGHT / 8); y++) {
	  for (x = 0; x < DISPLAY_WIDTH; x++) {
	   uint16_t pos = x + y * DISPLAY_WIDTH;
	   if (buffer[pos] != buffer_back[pos]) {
		 minBoundY = _min(minBoundY, y);
		 maxBoundY = _max(maxBoundY, y);
		 minBoundX = _min(minBoundX, x);
		 maxBoundX = _max(maxBoundX, x);
	   }
	   buffer_back[pos] = buffer[pos];
	 }
	 yield();
	}

	// If the minBoundY wasn't updated
	// we can savely assume that buffer_back[pos] == buffer[pos]
	// holdes true for all values of pos
	if (minBoundY == ~0) return;

	sendCommand(COLUMNADDR);
	sendCommand(minBoundX);
	sendCommand(maxBoundX);

	sendCommand(PAGEADDR);
	sendCommand(minBoundY);
	sendCommand(maxBoundY);

	byte k = 0;
	for (y = minBoundY; y <= maxBoundY; y++) {
	  for (x = minBoundX; x <= maxBoundX; x++) {
		if (k == 0) {
		  Wire.beginTransmission(_address);
		  Wire.write(0x40);
		}
		Wire.write(buffer[x + y * DISPLAY_WIDTH]);
		k++;
		if (k == 16)  {
		  Wire.endTransmission();
		  k = 0;
		}
	  }
	  yield();
	}

	if (k != 0) {
	  Wire.endTransmission();
	}
  #else

	sendCommand(COLUMNADDR);
	sendCommand(0x0);
	sendCommand(0x7F);

	sendCommand(PAGEADDR);
	sendCommand(0x0);
	sendCommand(0x7);

	for (uint16_t i=0; i < DISPLAY_BUFFER_SIZE; i++) {
	  Wire.beginTransmission(this->_address);
	  Wire.write(0x40);
	  for (uint8_t x = 0; x < 16; x++) {
		Wire.write(buffer[i]);
		i++;
	  }
	  i--;
	  Wire.endTransmission();
	}
  #endif
}
