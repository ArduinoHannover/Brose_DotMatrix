#ifndef BROSE_DOTMATIX_H
#define BROSE_DOTMATIX_H

#include <Adafruit_GFX.h>
#include "TimerOne.h"

void displayMatrix();

class Brose_DotMatrix : public Adafruit_GFX {
	private:
		uint8_t
			_data,
			_clock,
			_latch,
			_enable,
			_addr0,
			_addr1,
			_addr2,
			_currentRow;
		uint8_t _imageBuffer[8][16];
		void selectRow(uint8_t);
		
	public:
		Brose_DotMatrix(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
		void begin(void);
		void fillScreen(uint16_t);
		void drawPixel(int16_t, int16_t, uint16_t);
		void display(void);
};

#endif //BROSE_DOTMATIX_H