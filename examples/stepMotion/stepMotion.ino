#include <SPI.h> 			// also need to include SPI
#include <L6470Stepper.h>	// include library

#define	pinCS	10
L6470Stepper stepper(pinCS);	// pass CS pin number

void setup()
{
	stepper.setup();
	stepper.angle(0);
}

void loop()
{
	static boolean goForward = true;

	delay(2000);

	if (goForward) {
		stepper.step(200);	// 360deg at 200 step motor
	} else {
		stepper.step(-200);
	}

	// switch direction
	goForward = !goForward;
}

