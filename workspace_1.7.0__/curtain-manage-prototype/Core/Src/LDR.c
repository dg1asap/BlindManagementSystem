#include "LDR.h"

struct _LDR {
	bool isDark; // 0 - Zwinieta ___ 1 - rozwianieta
};

uint16_t messureFromLdr[NUMBER_OF_LDR_MEASURE] = {0};
uint16_t averageMeasureFromLdr = 0;
uint8_t ldrMeasureNumber = 1;

uint16_t minLDRreading = 1;
uint16_t maxLDRreading = 3000;
uint16_t upperLDRControlLimit = 2000;
uint16_t lowerLDRControlLimit = 500;

void SetDarkness(LDR *ldr, bool val)
{
	ldr->isDark = val;
}

bool GetDarkness(LDR *ldr)
{
	return ldr->isDark;
}

uint16_t getLightIntensity() {
	HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);

	uint16_t lightIntensity;
	/* Check if the continous conversion of regular channel is finished */
	if ((HAL_ADC_GetState(&hadc) & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC)
	{
		/*##-6- Get the converted value of regular channel  ########################*/
		lightIntensity = HAL_ADC_GetValue(&hadc);
	}

	return lightIntensity;
}

void measureLDR() {
	messureFromLdr[ldrMeasureNumber - 1] = getLightIntensity();
	ldrMeasureNumber++;

	if (measureIsAutoOfRange()) {
		ldrMeasureNumber = 1;
	}
}

bool measureIsAutoOfRange() {
	return ldrMeasureNumber > NUMBER_OF_LDR_MEASURE;
}

bool areNewMeassures() {
	return ldrMeasureNumber >= NUMBER_OF_LDR_MEASURE;
}

uint16_t getAverageMeassure() {
	averageMeasureFromLdr = 0;
	for (int i = 0; i < NUMBER_OF_LDR_MEASURE; i++) {
		averageMeasureFromLdr += messureFromLdr[i];
	}

	return (averageMeasureFromLdr/NUMBER_OF_LDR_MEASURE);
}

uint16_t convertPercentToLDRvalue(uint16_t percent) {
	uint16_t range = maxLDRreading - minLDRreading;
	return (minLDRreading + (range * percent / 100));
}

bool isAboveUpperLimit() {
	return getAverageMeassure() > upperLDRControlLimit;
}

bool isBelowLowerLimit() {
	return getAverageMeassure() < lowerLDRControlLimit;
}

void setMinLDRreading(uint16_t minLDRreading_) {
	minLDRreading = minLDRreading_;
}

void setMaxLDRreading(uint16_t maxLDRreading_) {
	maxLDRreading = maxLDRreading_;
}

void setUpperLDRControlLimit(uint16_t upperLDRContolLimit_) {
	upperLDRControlLimit = upperLDRContolLimit_;
}

void setLowerLDRControlLimit(uint16_t lowerLDRControlLimit_) {
	lowerLDRControlLimit = lowerLDRControlLimit_;
}

uint16_t getMinLDRreading() {
	return minLDRreading;
}

uint16_t getMaxLDRreading() {
	return maxLDRreading;
}

uint16_t getUpperLDRControlLimit() {
	return upperLDRControlLimit;
}

uint16_t getLowerLDRControlLimit() {
	return lowerLDRControlLimit;
}

