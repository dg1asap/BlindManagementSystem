#ifndef INC_MYLIBRARY_H_
#define INC_MYLIBRARY_H_

#include <string.h>

#include "main.h"
#include "tim.h"
#include "myutilities.h"

extern char buffer[50];
extern uint8_t timer_count, buffer_index;
extern UART_HandleTypeDef huart1;

void msg_handler();

#endif /* INC_MYLIBRARY_H_ */