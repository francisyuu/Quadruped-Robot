#include "MainTask.h"
#include "cmsis_os.h"
#include "tim.h"
#include "DBUS.h"
#include "bsp_imu.h"
#include "legctrl.h"
#include "remote.h"
int glen;
void StartMainTask(void const * argument)
{
	
	for(;;)
	{
		IMU_UPDATE();
		PID_cal();
		Remote_Handle();
		osDelay(1);
	}
}

void StartShowTask(void const * argument)
{
	for(;;)
	{

		osDelay(5);
	}

}
