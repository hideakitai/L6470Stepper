#include "L6470Stepper.h"


L6470Stepper::L6470Stepper(int pinCS, int nDaisyChain, int* motorSteps)
: SPIDaisyChain(pinCS, nDaisyChain)
{
	_spiData = new L6470SpiData(nDaisyChain);
	_motor = new L6470MotorData[nDaisyChain];
	_readData = new int[nDaisyChain];

	// pin settings
	_pinBUSY = 0xFF;	// NOT USE, default
	_pinSTEP = 0xFF;	// NOT USE, default
	useBusy = false;
	useStep = false;

	for (int i=0; i<nDaisyChain; i++) {
		if (motorSteps == NULL)	_motor[i].setMotorStep(DEFAULT_MOTOR_STEP);
		else					_motor[i].setMotorStep(motorSteps[i]);
	}

	resetDriver();
}

L6470Stepper::~L6470Stepper()
{
	delete[] _motor;
	delete[] _spiData;
	delete[] _readData;
}


void L6470Stepper::setup(registerStruct* regParamList, int size, int id)
{
	// set motor driver as L6480
	if (regParamList == NULL)	regParamList = (registerStruct*)L6470DefaultRegParamList;
	_writableRegNum = WRITABLE_REG_NUM_L6470;
	for (int i=0; i<getDaisyChainNum(); i++) {
		_motor[i].setup(L6470_REGISTER);
	}

	// initialize register
	if (id < 0) {
		for (int i=0; i<getDaisyChainNum(); i++) {
			initRegister(regParamList, _writableRegNum, i);
		}
	} else {
		if (size == 0)	size = _writableRegNum;
		initRegister(regParamList, size, id);
	}
}

void	L6470Stepper::angle(int degree)
{
	for (int i=0; i<getDaisyChainNum(); i++) {
		setAngle(degree, i);
	}
	transferAction();
}

void	L6470Stepper::setAngle(int degree, int id)
{
	if(id >= getDaisyChainNum())
		return;
	_motor[id].setAction(GOTO, degree);
}

void	L6470Stepper::step(int steps)
{
	for (int i=0; i<getDaisyChainNum(); i++) {
		setStep(steps, i);
	}
	transferAction();
}

void	L6470Stepper::setStep(int steps, int id)
{
	if(id >= getDaisyChainNum())
		return;
	if (steps < 0) {
		_motor[id].setAction(MOVE, abs(steps), CCW);
	} else {
		_motor[id].setAction(MOVE, abs(steps), CW);
	}
}

void	L6470Stepper::rotate(motorDirection dir, int rps)
{
	for (int i=0; i<getDaisyChainNum(); i++) {
		setRotate(dir, i, rps);
	}
	transferAction();
}

void	L6470Stepper::setRotate(motorDirection dir, int id, int rps)
{
	if(id >= getDaisyChainNum())
		return;
	if (rps == 0) {
		rps = _motor[id].getCurRps();
	}
	_motor[id].setAction(RUN, abs(rps), dir);
}

void L6470Stepper::setRps(int rps)
{
	for (int i=0; i<getDaisyChainNum(); i++) {
		setRps(rps, i);
	}
	transferRegister();
}

void L6470Stepper::setRps(int rps, int id)
{
	if(id >= getDaisyChainNum())
		return;
	_motor[id].setRegister(REG_MAX_SPEED, rps);
}

int& L6470Stepper::readRegister(int reg)
{
	for (int i=0; i<getDaisyChainNum(); i++) {
		requestRegister(reg, i);
	}
	transferRegister();
	return *(_readData);
}

void L6470Stepper::requestRegister(int reg, int id)
{
	if(id >= getDaisyChainNum())
		return;
	_motor[id].requestRegister(reg);
}

void L6470Stepper::execute()
{
	bool needToSetReg = false;
	bool needToSetCmd = false;

	// check if spi action is needed
	for (int i=0; i<getDaisyChainNum(); i++) {
		needToSetReg |= _motor[i].isRegChanged();
		needToSetCmd |= _motor[i].isCmdChanged();
	}

	if (needToSetReg) {
		transferRegister();
	}

	if (needToSetCmd) {
		transferAction();
	}
}

void L6470Stepper::transferAction()
{
	_spiData->updateAsAppCmd(_motor);

	transferDaisyChain(_spiData->getCmd());
	for (int i=SPI_VAL_MAXSIZE-_spiData->getSize(); i<SPI_VAL_MAXSIZE; i++) {
		transferDaisyChain(_spiData->getVal(i));
	}
}

void L6470Stepper::transferRegister()
{
	// send data order / 0: MSB n: LSB
	// read data order / 0: LSB n: MSB

	_readUnion readUnion[getDaisyChainNum()];
	_spiData->updateAsRegCmd(_motor);

	transferDaisyChain(_spiData->getCmd());
	int startByte = SPI_VAL_MAXSIZE-_spiData->getSize();
	for (int i=startByte; i<SPI_VAL_MAXSIZE; i++) {
		byte* readBytes;
		readBytes = transferDaisyChain(_spiData->getVal(i));	// get pointer, read data comes from MSB
		for (int j=0; j<getDaisyChainNum(); j++) {
			readUnion[j].bval[SPI_VAL_MAXSIZE-1-i] = readBytes[j];
		}
	}

	// copy data to array
	for (int i=0; i<getDaisyChainNum(); i++) {
		_readData[i] = readUnion[i].ival;
	}
}

void	L6470Stepper::clearMotorActions()
{
	for (int i=0; i<getDaisyChainNum(); i++) {
		clearMotorAction(i);
	}
}

void	L6470Stepper::clearMotorAction(int id)
{
	_motor[id].setAction(NOP);
	_motor[id].setRegister(REG_NOP);
}

void L6470Stepper::resetDriver()
{
	for (int i=0; i<getDaisyChainNum(); i++)
	{
		_motor[i].setAction(NOP);
	}
	transferAction();

	for (int i=0; i<getDaisyChainNum(); i++)
	{
		_motor[i].setAction(RESETDEVICE);
	}
	transferAction();
}

void L6470Stepper::initRegister(registerStruct* regParamList, int size, int id)
{
	for (int i=0; i<size; i++) {
		for (int j=0; j<getDaisyChainNum(); j++) {
			if (j == id)	_motor[j].setRegister(regParamList[i].reg, regParamList[i].val);
			else			_motor[j].setRegister(REG_NOP, 0);
		}
		transferRegister();
	}
}

// optional
void	L6470Stepper::setBusyEnable(int pinBUSY)
{
	_pinBUSY = pinBUSY;
	useBusy = true;
}

void	L6470Stepper::setStepEnable(int pinSTEP)
{
	_pinSTEP = pinSTEP;
	useStep = true;
}

byte	L6470Stepper::isBusy()
{
	// todo: faster one
	// todo: status register has the mirror
	return !digitalRead(_pinBUSY);	// BUSY: LOW, FREE: HIGH
}



L6480Stepper::L6480Stepper(int pinCS, int nDaisyChain, int* motorSteps)
:L6470Stepper(pinCS, nDaisyChain, motorSteps)
{
}

L6480Stepper::~L6480Stepper()
{

}

void L6480Stepper::setup(registerStruct* regParamList, int size, int id)
{
	// set motor driver as L6480
	if (regParamList == NULL)	regParamList = (registerStruct*)L6480DefaultRegParamList;
	_writableRegNum = WRITABLE_REG_NUM_L6480;
	for (int i=0; i<getDaisyChainNum(); i++) {
		_motor[i].setup(L6480_REGISTER);
	}

	// initialize register
	if (id < 0) {
		for (int i=0; i<getDaisyChainNum(); i++) {
			initRegister(regParamList, _writableRegNum, i);
		}
	} else {
		if (size == 0)	size = _writableRegNum;
		initRegister(regParamList, size, id);
	}
}
