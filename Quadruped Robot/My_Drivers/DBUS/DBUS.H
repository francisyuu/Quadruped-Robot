#ifndef DBUS_H
#define DBUS_H
#include "stm32f4xx_hal.h"

#define DBUS huart1  //步兵 新工程 新哨兵 3 旧工程6 哨兵2  

#define KEY_W					(0x0001<<0)
#define KEY_S						(0x0001<<1)
#define KEY_A						(0x0001<<2)
#define KEY_D						(0x0001<<3)
#define KEY_Q						(0x0001<<4)
#define KEY_E						(0x0001<<5)
#define KEY_SHIFT			(0x0001<<6)
#define KEY_Ctrl					(0x0001<<7)

void DBUS_Init(void);
void DBUS_IT(void);
uint8_t IsPress(uint16_t KeyValue);
uint8_t IsRelease(uint16_t KeyValue);
uint16_t IsSet(uint16_t KeyValue);

 typedef struct
{
	struct
	{
		int16_t ch0;
		int16_t ch1;
		int16_t ch2;                
		int16_t ch3;
		uint8_t s1;
		uint8_t s2;
	}rc;
		struct
	{
		int16_t ch0;
		int16_t ch1;
		int16_t ch2;                
		int16_t ch3;
	}rc0;
	struct
	{
		int16_t x;
		int16_t y;
		int16_t z;
		uint8_t press_l;//鼠标左键
		uint8_t press_r;
		uint8_t press_l_flag; //按下标志位，在相邻两次按键检测中检测到按键从未按下变成按下会被置1，在下一次检测中被置回0
		uint8_t press_r_flag; //松开标志位
		uint8_t release_l_flag; 
		uint8_t release_r_flag;
	}mouse;
	
	struct
	{
		uint16_t raw;//  bit0:W bit1:S bit2:A bit3:D bit4:Q bit5:E bit6:Shift bit7:Ctrl
		uint16_t press_flag;
		uint16_t release_flag;
	}key;
	
}RC_Ctl_t;

extern RC_Ctl_t RC_Ctl;


#endif
