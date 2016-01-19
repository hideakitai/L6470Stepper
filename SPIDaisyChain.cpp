#include "SPIDaisyChain.h"


SPIDaisyChain::SPIDaisyChain(const int pinCS, const int nDaisyChains)
{
	// default setting
	_pinCS			= (uint8_t)pinCS;
	_nDaisyChains	= (uint8_t)nDaisyChains;
	_bitOrder		= (uint8_t)MSBFIRST;
	_spiMode 		= (uint8_t)SPI_MODE3;


	readBytes = new byte[_nDaisyChains];

	// SPI settings
	pinMode(_pinCS, OUTPUT);
	digitalWrite(_pinCS, HIGH);
	SPIClass::begin();
	setBitOrder(_bitOrder);
	setDataMode(_spiMode);

	// select function for rise/fall CS
	if (_pinCS > 7) {
		_pinCS -= 8;
		fallCS = &SPIDaisyChain::fallCSPORTB;
		riseCS = &SPIDaisyChain::riseCSPORTB;
	} else {
		fallCS = &SPIDaisyChain::fallCSPORTD;
		riseCS = &SPIDaisyChain::riseCSPORTD;
	}
}

SPIDaisyChain::~SPIDaisyChain()
{
	delete[] readBytes;
	SPIClass::end();
}

byte* SPIDaisyChain::transferDaisyChain(byte* chainedValue)
{
	(this->*fallCS)();
	for (int i=0; i<_nDaisyChains; i++)	readBytes[i] = transfer(chainedValue[i]);
	(this->*riseCS)();
	return readBytes;
}

int	 SPIDaisyChain::getDaisyChainNum()
{
	return _nDaisyChains;
}

inline void SPIDaisyChain::fallCSPORTD()
{
	PORTD &= ~_BV(_pinCS);
}

inline void SPIDaisyChain::fallCSPORTB()
{
	PORTB &= ~_BV(_pinCS);
}

inline void SPIDaisyChain::riseCSPORTD()
{
	PORTD |= _BV(_pinCS);
}

inline void SPIDaisyChain::riseCSPORTB()
{
	PORTB |= _BV(_pinCS);
}
