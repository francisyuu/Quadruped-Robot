#ifndef LEGCTRL_H
#define LEGCTRL_H

#include "tim.h"
#include "basic_parameter.h"

typedef struct
{
	float P;
	float I;
	float D;
	float CurrentInput;
	float LastInput;
	float Tolerance;
	float I_Limited;
	float IMax;
	float PIDMax;
	float Pout;
	float Iout;
	float Dout;
	float output;
}PID;
extern leg_t legs[];
extern PID PIT_PID,ROL_PID;


void robot_init(leg_t *leg);
void robot_run(leg_t *leg);
void PID_cal();
void PIT_ROL_PID_Set(uint8_t mode);
void pwm_offset_run(leg_t *leg);
void trot(leg_t *leg,int16_t zspeed,int16_t yspeed,int16_t turnspeed);
void balance(leg_t *leg,float rol,float pit,float yaw);
#endif
