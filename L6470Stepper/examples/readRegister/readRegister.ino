#include <SPI.h> 			// also need to include SPI
#include <L6470Stepper.h>	// include library

#define pinCS	10
L6470Stepper stepper(pinCS);	// pass CS pin number

void setup()
{
	Serial.begin(115200);

	stepper.setup();
	stepper.rotate(CW);
}

void loop()
{
	int data;
	data = stepper.readRegister(REG_ABS_POS);

	Serial.print("reg ");
	Serial.print(REG_ABS_POS, HEX);
	Serial.print(": ");
	Serial.println(data, HEX);
}

