#ifndef BROSE_DOTMATIX_H
#define BROSE_DOTMATIX_H

#include <Adafruit_GFX.h>
#ifndef ESP8266
#include "TimerOne.h"
#endif

#ifndef PWMRANGE
#define PWMRANGE 255
#endif

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
		uint16_t _dim = PWMRANGE;
		boolean _enabled = true;
		uint8_t _imageBuffer[8][16];
		void selectRow(uint8_t);
		
	public:
		Brose_DotMatrix(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
		void begin(void);
		void enable(boolean);
		boolean enabled();
		int16_t width(void) const {return 120;}; //Dirty hack again to allow 20 chars
		void fillScreen(uint16_t);
		void drawPixel(int16_t, int16_t, uint16_t);
		void display(void);
		void dim(uint8_t dimmed);
};

#endif //BROSE_DOTMATIX_H