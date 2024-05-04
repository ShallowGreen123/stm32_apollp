
#pragma once
#include "hardware.h"

#define KEY0        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_3)  //KEY0按键PH3
#define KEY1        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_2)  //KEY1按键PH2
#define KEY2        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) //KEY2按键PC13
#define WK_UP       HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)  //WKUP按键PA0

#define KEY0_PRES 	1
#define KEY1_PRES   2
#define KEY2_PRES   3
#define WKUP_PRES   4

#define KEY_LONG_PRESS_ON  1
#define KEY_LONG_PRESS_OFF 0

uint8_t Key_Scan(uint8_t mode);

