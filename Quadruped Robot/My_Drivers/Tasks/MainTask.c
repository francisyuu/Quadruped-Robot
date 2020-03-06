#include "MainTask.h"
#include "cmsis_os.h"
#include "tim.h"
#include "DBUS.h"
#include "bsp_imu.h"
//1  600 1800  1300
//2  750 1550  1250
//3 1300 2000 1700
//4 1100 1700 1350
//5  800 2000 
//6  800 2000
//7           2500
//8           800
//9  1200 1700
//10 1500 2000
//11 850  1350
//12 1300 1800
int STEER[12] = {1300,1200,1700,1375,1700,1200,1800,1500,1700,1500,1300,1350};
void StartMainTask(void const * argument)
{
	for(;;)
	{
		IMU_UPDATE();
//				__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,a);
//			HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
//		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,STEER[0]);
//			HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);
//		__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_3,STEER[1]);
//			HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
//		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,STEER[2]);
//			HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
//		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,STEER[3]);
//			HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
//		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,STEER[4]);
//			HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_4);
//		__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_4,STEER[5]);
//			HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
//		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,STEER[6]);
//			HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
//		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,STEER[7]);
//			HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
//		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,STEER[8]-RC_Ctl.rc0.ch0);
//			HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
//		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,STEER[9]+RC_Ctl.rc0.ch0);
//			HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
//		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,STEER[10]-RC_Ctl.rc0.ch0);
//			HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);
//			__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,STEER[11]+RC_Ctl.rc0.ch0);
//			HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
		osDelay(1);
	}
}

void StartShowTask(void const * argument)
{
//	__HAL_TIM_SET_AUTORELOAD(&htim4,38000);
//	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,(38000/2+1));
}
