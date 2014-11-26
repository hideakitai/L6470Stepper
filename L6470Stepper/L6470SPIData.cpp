#include "L6470SPIData.h"


L6470SpiData::L6470SpiData(const int nDaisyChains)
: _nDaisyChains(nDaisyChains)
{
	cmd = new uint8_t  [_nDaisyChains];

	val = new uint8_t* [SPI_VAL_MAXSIZE];
	for (int i=0; i<SPI_VAL_MAXSIZE; i++) { val[i] = new uint8_t [_nDaisyChains]; }

	size = 0;
}

L6470SpiData::~L6470SpiData()
{
	delete[] cmd;

	for (int i=0; i<SPI_VAL_MAXSIZE; i++) { delete[] val[i]; }
	delete[] val;
}


uint8_t* L6470SpiData::getCmd()
{
	return cmd;
}

uint8_t* L6470SpiData::getVal(int nThByte)
{
	return (uint8_t*)val[nThByte];
}

uint8_t	 L6470SpiData::getSize()
{
	return size;
}


void L6470SpiData::updateAsAppCmd(L6470MotorData* motor)
{
	size = 0;
	for (int i=0; i<_nDaisyChains; i++)
	{
		cmd[i] = (uint8_t)(motor[i].getAppCmd());

		if (motor[i].getAppSize() > size) {
			size = (uint8_t)(motor[i].getAppSize());
		}

		for (int j=0; j<SPI_VAL_MAXSIZE; j++) {
			val[SPI_VAL_MAXSIZE-1-j][i] = (uint8_t)((motor[i].getAppValue() >> (8*j)) & 0xFF);	// MSB first
		}
		motor[i].setCmdChanged(false);
		motor[i].clearCmd();
	}
}

void L6470SpiData::updateAsRegCmd(L6470MotorData* motor)
{
	size = 0;
	for (int i=0; i<_nDaisyChains; i++)
	{
		cmd[i] = (uint8_t)(motor[i].getRegCmd());

		if (motor[i].getRegSize() > size) {
			size = (uint8_t)(motor[i].getRegSize());
		}

		for (int j=0; j<SPI_VAL_MAXSIZE; j++) {
			val[SPI_VAL_MAXSIZE-1-j][i] = (uint8_t)((motor[i].getRegValue() >> (8*j)) & 0xFF);	// MSB first
		}
		motor[i].setRegChanged(false);
		motor[i].clearReg();
	}
}

