#ifndef BASIC_PARAMETER_H
#define BASIC_PARAMETER_H

#include "stdint.h"

#define a1 130
#define a2 137
#define d1 40
#define THETA0 0.5191f  //�����˶ԽǶ��� Լ29.7��
#define LR 181.4f //�����˶Խ��ߵ�һ�� mm
#define L1_half 157.5f //�����˳��ߵ�һ�� mm
#define L2_half 90.0f //�����˶̱ߵ�һ�� mm
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

#define bodyheight 0.2f //��� m ����޸���������� Ҫ�ǵ�ͬʱ�޸�k_midpar
#define k_midpar 7.0f					//�м������(g/h)^0.5 
#define Tsupport 0.2f	//֧�������� s
#define Timpend 0.2f 	//���������� s
#define kcycloid 1.0f 	//����ϵ�� 
#define x_offset_Robot 0 	//����ƫ����
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
	}pos;//��Ը���������� mm
	
	struct{
		float x;
		float y;
		float z;
	}pos0;//��Ի����������� mm
	
	struct{
		float theta1;
		float theta2;
		float theta3;
	}theta;//���ת�� rad
	
	struct{
		float pwm1;
		float pwm2;
		float pwm3;
	}pwm;//pwmռ�ձ�
	
	struct{
		uint32_t starttime;
		float footheight;//̧�ȸ߶� m
		float v0z;//���Ե��ٶ�
		float v0y;
		float z0;//֧���࿪ʼλ�� mm
		float y0;
		float z1;//֧�������λ�� mm
		float y1;
	}trot;
}leg_t;

#endif
