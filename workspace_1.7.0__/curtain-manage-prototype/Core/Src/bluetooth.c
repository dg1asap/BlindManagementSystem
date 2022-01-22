#include "bluetooth.h"

uint8_t buffer_index = 0;
uint8_t timer_count = 0;
char buffer[50];
char info[50];

void msg_handler(void)
{
	if (string_compare(buffer, "SERWO MAX UP", strlen("SERWO MAX UP"))) {
		setBlindPositionToMax();
		HAL_UART_Transmit(&huart1, (uint8_t*)"Servo going up to min.\n", strlen("Servo going up to min.\n"), 500);
	} else if (string_compare(buffer, "SERWO MIN DOWN", strlen("SERWO MIN DOWN"))) {
		setBlindPositionToMin();
		HAL_UART_Transmit(&huart1, (uint8_t*)"Servo going down to max.\n", strlen("Servo going down to max.\n"), 500);
	} else if (string_compare(buffer, "SERWO UP", strlen("SERWO UP"))) {
		increaseBlindPositionByLength(1);
		HAL_UART_Transmit(&huart1, (uint8_t*)"Servo going up by 1.\n", strlen("Servo going up by 1.\n"), 500);
	} else if (string_compare(buffer, "SERWO DOWN", strlen("SERWO DOWN"))) {
		increaseBlindPositionByLength(-1);
		HAL_UART_Transmit(&huart1, (uint8_t*)"Servo going down by 1.\n", strlen("Servo going down by 1.\n"), 500);
	} else if (strncmp (buffer, "SET MIN LDR READING xxx", strlen("SET MIN LDR READING")) == 0) {
		uint16_t percent = getLastWordAsInt(buffer);
		setMinLDRreading(percent);
	} else if (strncmp (buffer, "SET MAX LDR READING xxx", strlen("SET MAX LDR READING")) == 0) {
		uint16_t percent = getLastWordAsInt(buffer);
		setMaxLDRreading(percent);
	} else if (strncmp (buffer, "SET UPPER LDR CONTROL LIMIT xxx", strlen("SET UPPER LDR CONTROL LIMIT")) == 0) {
		uint16_t percent = getLastWordAsInt(buffer);
		setUpperLDRControlLimit(percent);
	} else if (strncmp (buffer, "SET LOWER LDR CONTROL LIMIT xxx", strlen("SET LOWER LDR CONTROL LIMIT")) == 0) {
		uint16_t percent = getLastWordAsInt(buffer);
		setLowerLDRControlLimit(percent);
	} else if (string_compare(buffer, "PRINT MIN LDR READING", strlen("PRINT MIN LDR READING"))) {
		sprintf(info, "minLdrReading=%d", getMinLDRreading());
		strcpy(info, "\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)info, strlen(info), 500);
	} else if (string_compare(buffer, "PRINT MAX LDR READING", strlen("PRINT MAX LDR READING"))) {
		sprintf(info, "minLdrReading=%d", getMaxLDRreading());
		strcpy(info, "\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)info, strlen(info), 500);
	} else if (string_compare(buffer, "PRINT UPPER LDR CONTROL LIMIT", strlen("PRINT UPPER LDR CONTROL LIMIT"))) {
		sprintf(info, "minLdrReading=%d", getUpperLDRControlLimit());
		strcpy(info, "\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)info, strlen(info), 500);
	} else if (string_compare(buffer, "PRINT LOWER LDR CONTROL LIMIT", strlen("PRINT LOWER LDR CONTROL LIMIT"))) {
		sprintf(info, "minLdrReading=%d", getLowerLDRControlLimit());
		strcpy(info, "\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)info, strlen(info), 500);
	} else {
		strcat(buffer, "\n");
		HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 500);
	}

	memset(buffer, 0, sizeof(buffer));
	buffer_index = 0;
	timer_count = 0;


}