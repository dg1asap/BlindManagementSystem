#include "Servo.h"

void steer(Servo servo) {
	if (canRollDown(servo))
		rollDown(servo);
	else if (canRollUp(servo))
		rollUp(servo);
	else if (canStopRolling(servo))
		stopRolling(servo);
}

void increasePositionBy(Servo servo, uint16_t length) {
	uint16_t newPosition_ = length + servo.newPosition;
	if (canSetPosition(servo, newPosition_))
		setPosition(servo, newPosition_);
}

bool canSetPosition(Servo servo, uint16_t newPosition_) {
	return !isLongerThan(servo, newPosition_) && isPositiveLength(servo, newPosition_);
}

void setPosition(Servo servo, uint16_t newPosition_) {
	if (canSetPosition(servo, newPosition_))
		servo.newPosition = newPosition_;
}

void setPositionToMax(Servo servo) {
	servo.newPosition = servo.maxPosition;
}

void setPositionToMin(Servo servo) {
	servo.newPosition = 0;
}

bool canRollUp(Servo servo) {
	return isBelowNewPosition(servo) && isRolledMaxUp(servo);
}

bool canRollDown(Servo servo) {
	return isAboveNewPosition(servo) && isRolledMaxDown(servo);
}

bool canStopRolling(Servo servo) {
	return servo.currentPositon == servo.newPosition;
}

bool isRolledMaxUp(Servo servo) {
	return servo.currentPositon < servo.maxPosition;
}

bool isRolledMaxDown(Servo servo) {
	return servo.currentPositon > 0;
}

bool isBelowNewPosition(Servo servo) {
	return servo.currentPositon < servo.newPosition;
}

bool isAboveNewPosition(Servo servo) {
	return servo.currentPositon > servo.newPosition;
}

bool isLongerThan(Servo servo, uint16_t blindLength) {
	return blindLength > servo.maxPosition;
}

bool isPositiveLength(Servo servo, uint16_t blindLength) {
	return blindLength >= 0;
}

void rollDown(Servo servo) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1394);
	servo.currentPositon--;
}

void rollUp(Servo servo) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1568);
	servo.currentPositon++;
}

void stopRolling(Servo servo) {
//	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1474);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1460);
}
