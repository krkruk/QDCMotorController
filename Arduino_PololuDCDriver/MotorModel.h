/*
 * MotorModel.h
 *
 *  Created on: Dec 6, 2016
 *      Author: krzysztof
 */

#ifndef MOTORMODEL_H_
#define MOTORMODEL_H_
#include "MotorData.h"

class MotorModel {
public:
	static const int8_t COUNTERCLOCKWISE = -1;
	static const int8_t CLOCKWISE = 1;

	MotorModel(MotorData *motor);
	int getPwm();
	int8_t isHalted() const { return _isHalted; }

private:
	MotorData *_motor;
	int8_t _direction {0};
	int8_t _isHalted {0};

	int8_t getDirection(const int& pwm);
};

#endif /* MOTORMODEL_H_ */
