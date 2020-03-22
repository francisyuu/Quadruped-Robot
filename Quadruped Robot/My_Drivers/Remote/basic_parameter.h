#ifndef BASIC_PARAMETER_H
#define BASIC_PARAMETER_H

#include "stdint.h"

#define a1 130
#define a2 137
#define d1 40
#define THETA0 0.5191f  //机器人对角度数 约29.7°
#define LR 181.4f //机器人对角线的一半 mm
#define L1_half 157.5f //机器人长边的一半 mm
#define L2_half 90.0f //机器人短边的一半 mm
#define PI 3.1415926f

#define STEER1_TIM htim5
#define STEER2_TIM htim8
#define STEER3_TIM htim4
#define STEER4_TIM htim2
#define STEER5_TIM htim5
#define STEER6_TIM htim8
#define STEER7_TIM htim4
#define STEER8_TIM htim2
#define STEER9_TIM htim4
#define STEER10_TIM htim2
#define STEER11_TIM htim5
#define STEER12_TIM htim8

#define STEER1_CHANNEL TIM_CHANNEL_3
#define STEER2_CHANNEL TIM_CHANNEL_3
#define STEER3_CHANNEL TIM_CHANNEL_2
#define STEER4_CHANNEL TIM_CHANNEL_1
#define STEER5_CHANNEL TIM_CHANNEL_4
#define STEER6_CHANNEL TIM_CHANNEL_4
#define STEER7_CHANNEL TIM_CHANNEL_1
#define STEER8_CHANNEL TIM_CHANNEL_2
#define STEER9_CHANNEL TIM_CHANNEL_3
#define STEER10_CHANNEL TIM_CHANNEL_3
#define STEER11_CHANNEL TIM_CHANNEL_2
#define STEER12_CHANNEL TIM_CHANNEL_2

#define bodyheight 0.2f //肩高 m 如果修改了这个变量 要记得同时修改k_midpar
#define k_midpar 7.0f					//中间变量，(g/h)^0.5 
#define Tsupport 0.2f	//支撑相周期 s
#define Timpend 0.2f 	//浮空相周期 s
#define kcycloid 1.0f 	//摆线系数 
#define x_offset_Robot 0 	//重心偏移量
#define y_offset_Robot 0
#define z_offset_Robot -17

#define Trot_Mode_PAR 0
#define Balance_Mode_PAR 1
#define Twist_Mode_PAR 2
		
#define r2p 57.3f*2000/300 //rad to pwm

typedef struct
{
	struct{
		float x;
		float y;
		float z;
	}pos;//相对各腿零点坐标 mm
	
	struct{
		float x;
		float y;
		float z;
	}pos0;//相对机体中心坐标 mm
	
	struct{
		float theta1;
		float theta2;
		float theta3;
	}theta;//舵机转角 rad
	
	struct{
		float pwm1;
		float pwm2;
		float pwm3;
	}pwm;//pwm占空比
	
	struct{
		uint32_t starttime;
		float footheight;//抬腿高度 m
		float v0z;//中性点速度
		float v0y;
		float z0;//支撑相开始位置 mm
		float y0;
		float z1;//支撑相结束位置 mm
		float y1;
	}trot;
}leg_t;

#endif
