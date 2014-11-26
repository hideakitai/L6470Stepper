#include <SPI.h> 			// also need to include SPI
#include <L6470Stepper.h>	// include library

#define CHAINED_MOTOR_NUM	2
#define pinCS	10
L6470Stepper stepper(pinCS, CHAINED_MOTOR_NUM);	// pass CS pin number & number of chained motors

void setup()
{
	stepper.setup();
	stepper.angle(360);	// this makes all motors do the same motion
	delay(3000);
	stepper.angle(0);
}

void loop()
{
	static boolean goForward = true;
	static int motorSelect = 0;

	delay(3000);

	// you can set speed individually
	stepper.setRps(100+100*motorSelect, motorSelect);

	// also you can set angle individually
	if (goForward) {
		stepper.setAngle(360, motorSelect);
	} else {
		stepper.setAngle(0, motorSelect);
	}

	// in the individual motion, you must call this function
	stepper.execute();

	// switch direction
	if(++motorSelect >= CHAINED_MOTOR_NUM) {
		goForward = !goForward;
		motorSelect = 0;
	}
}

