#include "Brose_DotMatrix.h"

Brose_DotMatrix::Brose_DotMatrix(
	uint8_t data,
	uint8_t clock,
	uint8_t latch,
	uint8_t enable,
	uint8_t addr0,
	uint8_t addr1,
	uint8_t addr2) :
	Adafruit_GFX(120, 8),
	_data(data),
	_clock(clock),
	_latch(latch),
	_enable(enable),
	_addr0(addr0),
	_addr1(addr1),
	_addr2(addr2) {
	// oops, nothing to do here. Could be inline in .h but for reference.
}

void Brose_DotMatrix::begin() {
	pinMode(_data, OUTPUT);
	pinMode(_clock, OUTPUT);
	pinMode(_latch, OUTPUT);
	pinMode(_enable, OUTPUT);
	pinMode(_addr0, OUTPUT);
	pinMode(_addr1, OUTPUT);
	pinMode(_addr2, OUTPUT);
	digitalWrite(_latch, LOW);
	digitalWrite(_enable, HIGH);
	/*
	 * You may try different values here.
	 * Higher may flicker
	 * Lower may block your code from execution
	 *  -> Setting pixel by pixel @ 1-2Hz
	 */
	Timer1.initialize(3000);
	Timer1.attachInterrupt(displayMatrix);
	fillScreen(1);
	delay(100);
	fillScreen(0);
}

void Brose_DotMatrix::selectRow(uint8_t row) {
	digitalWrite(_addr0, row & 1);
	digitalWrite(_addr1, row & 2);
	digitalWrite(_addr2, row & 4);
}

void Brose_DotMatrix::fillScreen(uint16_t color) {
	uint8_t fillByte = 0x00;
	if (color) fillByte = 0xFF;
	//Fast magic ;-)
	for (uint8_t y = 0; y < 8; y++)
		for (uint8_t reg = 0; reg < 16; reg++)
			_imageBuffer[y][reg] = fillByte;
}
			

void Brose_DotMatrix::drawPixel(int16_t x, int16_t y, uint16_t color) {
	if (x < 0 || y < 0 || x >= width() || y >= height()) return;
	uint8_t paddingBits = ((x + 30) / 30) * 2;
	uint8_t registerOut = (x + paddingBits) / 8;
	//Some nasty magic.
	if (color > 0) {
		_imageBuffer[7-y][registerOut] |= 1 << ((x + paddingBits) & 7);
	} else {
		_imageBuffer[7-y][registerOut] &= ~(1 << ((x + paddingBits) & 7));
	}
}

void Brose_DotMatrix::display(void) {
	for (int8_t reg = 15; reg >= 0; reg--) {
		//reverse magic
		shiftOut(_data, _clock, MSBFIRST, _imageBuffer[_currentRow][reg]);
	}
	digitalWrite(_enable, HIGH);
	digitalWrite(_latch, HIGH); //shift the data to the pins
	digitalWrite(_latch, LOW);
	selectRow(_currentRow);
	digitalWrite(_enable, LOW);
	_currentRow++;    // increment row
	_currentRow &= 7; // fall back to 0 if > 7
}