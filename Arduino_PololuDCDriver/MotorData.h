/*
 * Motor.h
 *
 *  Created on: Dec 6, 2016
 *      Author: krzysztof
 */

#ifndef MOTORDATA_H_
#define MOTORDATA_H_
#include "Arduino.h"


class MotorData {
public:
	MotorData(uint8_t ccwisePin, uint8_t cwisePin);

	void init();
	void readLimitSwitchesState();

	uint8_t getCounterClockwisePinState() const { return _ccwiseState; }
	uint8_t getClockwisePinState() const { return _cwiseState; }

	int getPwm() const { return _pwm; }

	void setPwm(int pwm) { _pwm = pwm; }

private:
	const uint8_t _ccwisePin;
	const uint8_t _cwisePin;

	uint8_t _ccwiseState {0};
	uint8_t _cwiseState {0};

	int _pwm {0};
};

#endif /* MOTORDATA_H_ */
