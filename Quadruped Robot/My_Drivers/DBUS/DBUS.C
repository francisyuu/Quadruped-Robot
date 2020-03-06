
/** 
* @brief        MY_Drivers——DBUS
* @details  参考WMD模块化散装库——Dbus库
* @author      mijures
* @date     2018.10.11
* @version  v0.1
* @par Copyright (c):      mijures
* @par 0级驱动
* @par 使用方法：1.在头文件中更改对应uart的宏定义 2.将DBUS_IT放到对应串口中断函数中 3.使用DBUS_Init初始化DBUS 
* @par 更换串口时除以上外还要注意波特率等设置
* @par v0.1 调整了函数位置和头文件的部分内容，使调用更加方便，更新了标准化注释
*/  


#include "DBUS.h"
#include "usart.h"
#include "cmsis_os.h"


unsigned char DBUS_rx_buffer[25]={0};//DBUS数据缓存
RC_Ctl_t RC_Ctl; //处理后的遥控器控制量
QueueHandle_t xDBUSSemaphore;
osThreadId DBUSHandle;



/** 
* @brief  DBUS数据存储
* @details  将接受到的数据处理存储到RC_Ctl中
* @param  NULL
* @retval  NULL
* @par log
*/
void StartDBUSTask(void const * argument)
{
	for(;;)
	{
		xSemaphoreTake(xDBUSSemaphore,portMAX_DELAY);	
		uint8_t i;
			for(i=0;i<18;i++)
			{
				if(DBUS_rx_buffer[i]==0)continue;
				break;
			}
			if(i!=18)//有数据 
			{
					for(i=18;i<25;i++)//0缓冲区检测
						{
							if(DBUS_rx_buffer[i]!=0)		//0缓冲区（18-24）若出现数据 接收/发射错误
							{
								for(i=18;i<25;i++)
								{
									DBUS_rx_buffer[i]=0;
								}
								i=0;
								break ;
							}
						}
					if(i==25)
					{
									uint8_t mouse_l_last=RC_Ctl.mouse.press_l;
									uint8_t mouse_r_last=RC_Ctl.mouse.press_r;
									uint16_t raw_last=RC_Ctl.key.raw;//保存上次操作
									//数据存储
									RC_Ctl.rc.ch0 = (DBUS_rx_buffer[0]| (DBUS_rx_buffer[1] << 8)) & 0x07ff; //!< Channel 0
									RC_Ctl.rc.ch1 = ((DBUS_rx_buffer[1] >> 3) | (DBUS_rx_buffer[2] << 5)) & 0x07ff; //!< Channel 1
									RC_Ctl.rc.ch2 = ((DBUS_rx_buffer[2] >> 6) | (DBUS_rx_buffer[3] << 2) | //!< Channel 2
									(DBUS_rx_buffer[4] << 10)) & 0x07ff;
									RC_Ctl.rc.ch3 = ((DBUS_rx_buffer[4] >> 1) | (DBUS_rx_buffer[5] << 7)) & 0x07ff; //!< Channel 3
									RC_Ctl.rc0.ch0=RC_Ctl.rc.ch0-1024;if((RC_Ctl.rc0.ch0>-5)&&(RC_Ctl.rc0.ch0<5))RC_Ctl.rc0.ch0=0;
									RC_Ctl.rc0.ch1=RC_Ctl.rc.ch1-1024;if((RC_Ctl.rc0.ch1>-5)&&(RC_Ctl.rc0.ch1<5))RC_Ctl.rc0.ch1=0;
									RC_Ctl.rc0.ch2=RC_Ctl.rc.ch2-1024;if((RC_Ctl.rc0.ch2>-5)&&(RC_Ctl.rc0.ch2<5))RC_Ctl.rc0.ch2=0;
									RC_Ctl.rc0.ch3=RC_Ctl.rc.ch3-1024;if((RC_Ctl.rc0.ch3>-5)&&(RC_Ctl.rc0.ch3<5))RC_Ctl.rc0.ch3=0;
									
									RC_Ctl.rc.s1 = ((DBUS_rx_buffer[5] >> 4)& 0x000C) >> 2; //!< Switch left
									RC_Ctl.rc.s2 = ((DBUS_rx_buffer[5] >> 4)& 0x0003); //!< Switch right
									RC_Ctl.mouse.x = DBUS_rx_buffer[6] | (DBUS_rx_buffer[7] << 8); //!< Mouse X axis
									RC_Ctl.mouse.y = DBUS_rx_buffer[8] | (DBUS_rx_buffer[9] << 8); //!< Mouse Y axis
									RC_Ctl.mouse.z = DBUS_rx_buffer[10] | (DBUS_rx_buffer[11] << 8); //!< Mouse Z axis
									RC_Ctl.mouse.press_l = DBUS_rx_buffer[12]; //!< Mouse Left Is Press ?
									RC_Ctl.mouse.press_r = DBUS_rx_buffer[13]; //!< Mouse Right Is Press ?
									RC_Ctl.key.raw = DBUS_rx_buffer[14] | (DBUS_rx_buffer[15] << 8); //!< KeyBoard value
									
									RC_Ctl.mouse.release_r_flag= !RC_Ctl.mouse.press_r && mouse_r_last;//记录鼠标左右键操作
									RC_Ctl.mouse.release_l_flag= !RC_Ctl.mouse.press_l && mouse_l_last;
									RC_Ctl.mouse.press_l_flag= RC_Ctl.mouse.press_l && (!mouse_l_last);
									RC_Ctl.mouse.press_r_flag= RC_Ctl.mouse.press_r && (!mouse_r_last);
									
									RC_Ctl.key.press_flag = ~RC_Ctl.key.raw & (RC_Ctl.key.raw^raw_last);//记录按下操作
									RC_Ctl.key.release_flag = RC_Ctl.key.raw & (RC_Ctl.key.raw^raw_last);//记录释放操作
					}
			}	
	}
}

/** 
* @brief  按键按下动作检测
* @details  
* @param   KeyValue 按键值
* @retval  1 按下动作 0 没有按下动作
* @par 
*/
uint8_t IsPress(uint16_t KeyValue)
{
	if(RC_Ctl.key.press_flag & KeyValue)
	{
		RC_Ctl.key.press_flag &= ~KeyValue;//擦除标志
		return 1;
	}else return 0;
}

/** 
* @brief  按键松开动作检测
* @details  This is the detail description. 
* @param    KeyValue 按键值
* @retval  1 松开动作 0 没有松开动作
* @par log
*/
uint8_t IsRelease(uint16_t KeyValue)
{
	if(RC_Ctl.key.release_flag & KeyValue)
	{
		RC_Ctl.key.release_flag &= ~KeyValue;//擦除标志
		return 1;
	}else return 0;
}

/** 
* @brief  按键状态检测
* @details  This is the detail description. 
* @param   KeyValue 按键值
* @retval  1 按下 0 松开
* @par log
*/
uint16_t IsSet(uint16_t KeyValue)
{
	return (RC_Ctl.key.raw&KeyValue)>0;
}

/** 
* @brief  DBUS初始化
* @details  This is the detail description. 
* @param   NULL
* @retval  NULL
* @par log
*/
void DBUS_Init(void)
{
	vSemaphoreCreateBinary(xDBUSSemaphore);//创建二值信号量，首次创建信号量计数值为0
	while(!xDBUSSemaphore);
	osThreadDef(DBUSTask,StartDBUSTask,osPriorityRealtime,0,256);
	DBUSHandle = osThreadCreate(osThread(DBUSTask),NULL);
	__HAL_UART_ENABLE_IT(&DBUS,UART_IT_IDLE);
	HAL_UART_Receive_DMA(&DBUS,(uint8_t *)DBUS_rx_buffer,sizeof(DBUS_rx_buffer));
}


/** 
* @brief  DBUS中断处理
* @details  收到数据会进中断，将数据存储到Ctl结构体中,要将此函数放进HDBUS_IRQHandler中
* @param   NULL
* @retval  NULL
* @par log
*/
void DBUS_IT(void) 
{
	static BaseType_t xHigherPriorityTaskWoken;  //高优先级任务是否被唤醒的状态保存                  
	if(__HAL_UART_GET_FLAG(&DBUS,UART_FLAG_IDLE))
	{
		HAL_UART_DMAStop(&DBUS);
		__HAL_UART_CLEAR_IDLEFLAG(&DBUS);
		HAL_UART_Receive_DMA(&DBUS,DBUS_rx_buffer,25);
		 xSemaphoreGiveFromISR(xDBUSSemaphore,&xHigherPriorityTaskWoken);
		if( xHigherPriorityTaskWoken == pdTRUE )portEND_SWITCHING_ISR(xHigherPriorityTaskWoken); //如果 xHigherPriorityTaskWoken = pdTRUE,则切换到当前最高任务执行，然后退出中断 } 
	}
}
