#ifndef SPIDAISYCHAIN_H_INCLUDED
#define SPIDAISYCHAIN_H_INCLUDED

#include <Arduino.h>
#include "pins_arduino.h"
#include <SPI.h>


class SPIDaisyChain : public SPIClass
{
public:

	// chain id = 0 : the farthest motor
	// chain id = n : the nearest motor
	SPIDaisyChain(const int pinCS = 10, const int nDaisyChains = 1);
	~SPIDaisyChain();

	byte*	transferDaisyChain(byte* chainedValue);
	int		getDaisyChainNum();

private:
	uint8_t _pinCS;
	uint8_t _nDaisyChains;
	uint8_t _bitOrder;
	uint8_t _spiMode;

	byte* readBytes;

	void (SPIDaisyChain::*fallCS)();
	void (SPIDaisyChain::*riseCS)();

	inline void fallCSPORTD();
	inline void fallCSPORTB();
	inline void riseCSPORTD();
	inline void riseCSPORTB();

};

#endif
