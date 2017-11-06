#ifndef __STEP_H
#define __STEP_H

#include "stm32f10x.h"

void Step_Motor_GPIO_Init(void);
void SetMotor(unsigned char InputData);
void motorNcircle(int n,bool position);
void Head_Action(void);
#endif