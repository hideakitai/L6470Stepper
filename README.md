# L6470Stepper

L6470 / L6480 wrapper for Arduino

## Dependencies

[SPIDaisyChain](https://github.com/hideakitai/SPIDaisyChain)

## Usage

``` c++
#include <SPI.h> 
#include <L6470Stepper.h>

int pinCS 10
L6470Stepper stepper(pinCS);

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
		stepper.angle(360);
	} else {
		stepper.angle(0);
	}

	// switch direction
	goForward = !goForward;
}
```


## License

MIT
