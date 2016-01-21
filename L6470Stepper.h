#ifndef L6470STEPPER_H_INCLUDED
#define L6470STEPPER_H_INCLUDED

#include <Arduino.h>
#include <SPI.h>
#include "pins_arduino.h"

#include "SPIDaisyChain.h"
#include "L6470Common.h"
#include "L6470MotorData.h"
#include "L6470SpiData.h"
#include "L6470InitRegParam.h"

typedef union {
	uint8_t		bval[4];
	uint32_t			ival;
} _readUnion;

class L6470Stepper : public SPIDaisyChain
{
public:
	// chain id = 0 : the farthest motor
	// chain id = n : the nearest motor
	L6470Stepper(int pinCS, int nDaisyChain = 1, int* motorSteps = NULL);
	~L6470Stepper();

	void	setup(registerStruct* regParamList = NULL, int size = 0, int id = -1);

	// all motor action
	void	angle(int degree);
	void	step(int steps);
	void	rotate(motorDirection dir, int rps = 0);

	// individual motor action
	void	setAngle(int degree, int id);
	void	setStep(int steps, int id);
	void	setRotate(motorDirection dir, int id, int rps = 0);
	void 	setStepClockMode(_motorDirection dir, int id = 0);

	float	angleToStep(long step);
	long	stepToAngle(float angle);
	void 	stepClock(float angle, float duration);
	void 	stepClock(int step, float duration);

	void 	stepClock(unsigned int step, _motorDirection dir);

	void 	stepPulse(unsigned int step);

	// set speed
	void	setRps(int rps);
	void	setRps(int rps, int id);

	// we must call this in the end of loop()
	// this function transfers spi data to L6470
	void	execute();

	// read register value from L6470
	long	readRegister(int reg, int motor_id = 0);
	void	requestRegister(int reg, int id);

	// optional
	void	setBusyEnable(int pinBUSY);
	void	setStepEnable(int pinSTEP);
	boolean	isBusy();
	void	resetDriver();

protected:

	void	transferAction();
	void	transferRegister();
	void	clearMotorActions();
	void	clearMotorAction(int id);
	void	initRegister(registerStruct* regParamList, int size, int id);

	L6470MotorData*		_motor;
	L6470SpiData*		_spiData;
	uint32_t*			_readData;	// current read data from register

  	byte	_pinBUSY;					// additional function pins
  	byte	_pinSTEP;					// additional function pins
  	bool	useBusy;
  	bool	useStep;

	int		_writableRegNum;
};


class L6480Stepper : public L6470Stepper
{
public:
	L6480Stepper(int pinCS, int nDaisyChain = 1, int* motorSteps = NULL);
	~L6480Stepper();
	void	setup(registerStruct* regParamList = NULL, int size = 0, int id = -1);
};

#endif
