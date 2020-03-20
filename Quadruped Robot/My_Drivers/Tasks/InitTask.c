#include "InitTask.h"
#include "MainTask.h"
#include "cmsis_os.h"
#include "task.h"
#include "tim.h"
#include "DBUS.h"
#include "bsp_imu.h"
#include "legctrl.h"


osThreadId MainHandle;
osThreadId MonitorHandle;
osThreadId ShowHandle;

void StartInitTask(void const * argument)
{
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
	
//	__HAL_TIM_SET_AUTORELOAD(&htim12,2000);
//	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,1000);
//	osDelay(100);
//	__HAL_TIM_SET_AUTORELOAD(&htim12,1500);
//	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,750);
//	osDelay(180);
//	__HAL_TIM_SET_AUTORELOAD(&htim12,500);
//	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,250);
//	osDelay(280);
//	__HAL_TIM_SET_AUTORELOAD(&htim12,500);
//	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);

	DBUS_Init();
	IMU_INIT();
	robot_init(legs);
	HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin|D2_Pin|D3_Pin|D4_Pin|D5_Pin|D6_Pin|D7_Pin|D8_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_R_GPIO_Port,LED_R_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_SET);
	
//		__HAL_TIM_SET_AUTORELOAD(&htim12,500);
//	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,250);
//	osDelay(180);
//		__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
//		osDelay(180);
//		__HAL_TIM_SET_AUTORELOAD(&htim12,500);
//	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,250);
//	osDelay(180);
//	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
//		osDelay(180);
		
	osThreadDef(MainTask,StartMainTask,osPriorityHigh,0,2048);
	MainHandle = osThreadCreate(osThread(MainTask),NULL);
//	
//	osThreadDef(MonitorTask,StartMonitorTask,osPriorityAboveNormal,0,1024);
//	MonitorHandle = osThreadCreate(osThread(MonitorTask),NULL);
//	
	osThreadDef(ShowTask,StartShowTask,osPriorityNormal,0,512);
	MonitorHandle = osThreadCreate(osThread(ShowTask),NULL);
	
	osThreadTerminate(NULL);
}
