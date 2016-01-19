#ifndef L6470SPIDATA_H_INCLUDED
#define L6470SPIDATA_H_INCLUDED

#include "L6470Common.h"
#include "L6470MotorData.h"

#define SPI_VAL_MAXSIZE	3

class L6470SpiData
{
public:
	// this class get the cmd-data-size based on L6470 spi interface
	L6470SpiData(const int nDaisyChains);
	~L6470SpiData();

	uint8_t*	getCmd();
	uint8_t*	getVal(int nThByte);
	uint8_t		getSize();

	void updateAsAppCmd(L6470MotorData* motor);
	void updateAsRegCmd(L6470MotorData* motor);

private:
	uint8_t*	cmd;
	uint8_t**	val;
	uint8_t		size;
	const int	_nDaisyChains;
};


#endif
