#include <Brose_DotMatrix.h>

/*
 * Test for Brose DotMatrix Display
 * 
 * TimerOne is needed:
 * https://github.com/PaulStoffregen/TimerOne
 */

Brose_DotMatrix dotmatrix(2,3,4,5,10,11,12);
//data, clock, latch, enable, addr0, addr1, addr2

void setup() {
	dotmatrix.begin();
	dotmatrix.print("Hello");
	delay(1000);
	dotmatrix.fillScreen(0);
	dotmatrix.setCursor(0,0);
	dotmatrix.print("This is a long one");

}

//This must be defined to allow the TimerInterrupt to call a static method
void displayMatrix() {
	dotmatrix.display();
}

void loop() {
	//nothing to do here.
}