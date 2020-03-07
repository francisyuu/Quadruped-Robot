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
#define BUZZER_TIM htim12
#define BUZZER_CHANNEL TIM_CHANNEL_1
#define C0  262
#define C0U 277
#define D0  294
#define D0U 311
#define E0  330
#define F0  349
#define F0U 370
#define G0  392
#define G0U 415
#define A0  440
#define A0U 464
#define B0  494
#define C1  523
#define C1U 554
#define D1  587
#define D1U 622
#define E1  659
#define F1  698
#define F1U 740
#define G1  784
#define G1U 831
#define A1  880
#define A1U 932
#define B1  988
#define C2  1046
#define C2U 1109
#define D2  1175
#define D2U 1245
#define E2  1318
#define F2  1397
#define F2U 1480
#define G2  1568
#define G2U 1661
#define A2  1760
#define A2U 1865
#define B2  1976
#define SPEED 0.8f
int STEER[12] = {1300,1200,1700,1375,1700,1200,1800,1500,1700,1500,1300,1350};
int a=800,b=0,c=1;
void MusicPlay(uint16_t name,uint16_t length,uint16_t time1,uint16_t time2);
void MusicTurn(uint16_t name1,uint16_t name2,uint16_t length,uint16_t time1,uint16_t time2);
void MusicPlay1(uint16_t name,uint16_t length);
void Musicdisap(uint16_t length);
void StartMainTask(void const * argument)
{
	for(;;)
	{
		 HAL_TIM_PWM_Start(&BUZZER_TIM,BUZZER_CHANNEL);
		if(RC_Ctl.rc.s1==3)
		{
			
			MusicTurn(B0,C1,1000,50,100);
			MusicPlay(B0,500,50,350);
			MusicTurn(C1,A0,500,400,450);
			MusicPlay(A0,1000,50,1000);
			MusicPlay(A0,500,50,400);
			MusicPlay(C1,500,50,400);
			
			MusicPlay(D1,500,50,400);
			MusicPlay(B0,500,50,400);
			MusicPlay(B0,500,50,400);
			MusicPlay(A0,250,50,200);
			MusicPlay(A0,750,50,600);
			MusicPlay(G0,500,50,200);
			MusicPlay(E0,500,50,200);
			MusicPlay(G0,500,50,0);
			
			MusicPlay(C1,750,50,0);
			MusicPlay(B0,750,50,0);
			MusicPlay(C1,500,50,0);
			MusicPlay(A0,750,50,0);
			MusicPlay(C1,250,50,0);
			MusicPlay(A0,500,50,0);
			MusicPlay(C1,500,50,0);
			
			MusicTurn(C1,D1,1000,300,400);
			Musicdisap(2000);
			MusicPlay(E0,500,50,0);
			MusicPlay(G0,500,50,0);
			
			MusicPlay(C1,1000,50,0);
			MusicPlay(B0,500,50,350);
			MusicTurn(C1,B0,500,250,350);
			MusicPlay(A0,1000,50,1000);
			MusicPlay(A0,500,50,400);
			MusicPlay(C1,500,50,400);
			
			MusicPlay(D1,500,50,400);
			MusicPlay(B0,500,50,400);
			MusicPlay(B0,500,50,400);
			MusicPlay(A0,250,50,200);
			MusicPlay(A0,750,50,600);
			MusicPlay(G0,500,50,200);
			MusicPlay(E0,500,50,200);
			MusicPlay(G0,500,50,0);
			
			MusicPlay(C1,1000,50,0);
			MusicPlay(B0,500,50,0);
			MusicPlay(C1,500,50,0);
			MusicTurn(C1,E1,500,50,100);
			Musicdisap(250);
			MusicPlay(E1,250,50,0);
			MusicPlay(E1,500,50,0);
			MusicPlay(D1,2500,50,0);
			
			MusicPlay(0,500,50,0);
			MusicPlay(E1,500,50,0);
			MusicPlay(D1,500,50,0);
			MusicPlay(C1,250,50,0);
			MusicPlay(A0,750,50,0);
			MusicPlay(E1,500,50,0);
			MusicPlay(D1,500,50,0);
			MusicPlay(C1,250,50,0);
			MusicPlay(A0,1250,50,0);
			MusicPlay(0,500,50,0);
			MusicPlay(A0,250,50,0);
			MusicPlay(C1,250,50,0);
			
			MusicPlay(D1,500,50,0);
			MusicPlay(B0,250,50,0);
			MusicPlay(B0,250,50,0);
			MusicPlay(B0,500,50,0);
			MusicPlay(A0,250,50,0);
			MusicPlay(A0,250,50,0);
			MusicTurn(A0,G0,1000,400,600);
			MusicPlay(E1,500,50,0);
			MusicPlay(D1,500,50,0);
			
			MusicPlay(C1,500,50,0);
			MusicPlay(E1,500,50,0);
			MusicPlay(D1,500,50,0);
			MusicPlay(C1,250,50,0);
			MusicPlay(F1,1250,50,0);
			MusicPlay(0,500,50,0);
			MusicPlay(A0,250,50,0);
			MusicPlay(C1,250,50,0);
			
			MusicPlay(D1,250,50,0);
			MusicPlay(D1,250,50,0);
			MusicPlay(D1,250,50,0);
			MusicPlay(D1,250,50,0);
			MusicPlay(D1,500,50,0);
			MusicPlay(E1,250,50,0);
			MusicPlay(F1,250,50,0);
			MusicPlay(F1,500,50,0);
			MusicPlay(E1,500,50,0);
			MusicPlay(C1,500,50,0);
			MusicPlay(D1,500,50,0);
			
			MusicTurn(D1,E1,500,100,175);
			MusicPlay(E1,500,50,0);
			MusicTurn(E1,G1,500,100,175);
			MusicPlay(A1,250,50,0);
			MusicTurn(G1,A1,750,200,300);
			MusicPlay(C1,500,50,0);
			MusicPlay(C1,500,50,0);
			MusicTurn(C1,E1,500,50,100);
			
			MusicTurn(D1,C1,1000,850,950);
			MusicPlay(C1,500,50,0);
			MusicPlay(D1,500,50,0);
			MusicPlay(E1,1000,50,0);
			MusicPlay(C1,500,50,0);
			MusicPlay(D1,500,50,0);
			
			MusicTurn(D1,E1,500,100,175);
			MusicPlay(E1,500,50,0);
			MusicTurn(E1,G1,500,100,175);
			MusicPlay(A1,250,50,0);
			MusicTurn(G1,A1,750,200,300);
			MusicPlay(C1,500,50,0);
			MusicPlay(C1,500,50,0);
			MusicTurn(C1,E1,500,50,100);
			
			MusicTurn(D1,C1,1000,750,900);
			MusicPlay(C1,500,50,0);
			MusicTurn(C1,B0,500,50,100);
			MusicPlay(C1,1000,50,0);
			MusicPlay(C1,500,50,0);
			MusicPlay(D1,500,50,0);
			
			MusicTurn(D1,E1,500,100,175);
			MusicPlay(E1,500,50,0);
			MusicTurn(E1,G1,500,50,100);
			MusicPlay(A1,250,50,0);
			MusicTurn(G1,A1,750,100,150);
			MusicPlay(C1,500,50,0);
			MusicPlay(C1,500,50,0);
			MusicTurn(C1,E1,500,50,100);
			
			MusicTurn(D1,C1,1000,600,800);
			MusicPlay(C1,500,50,0);
			MusicPlay(D1,500,50,0);
			MusicTurn(D1,E1,800,100,175);
			Musicdisap(150);
			MusicPlay(C1,500,50,0);
			MusicPlay(D1,500,50,0);
			
			MusicTurn(D1,E1,500,100,175);
			MusicPlay(E1,500,50,0);
			MusicTurn(E1,G1,500,50,100);
			MusicPlay(A1,250,50,0);
			MusicTurn(G1,A1,750,50,100);
			MusicPlay(C1,500,50,0);
			MusicPlay(C1,500,50,0);
			MusicTurn(C1,E1,500,50,100);
			
			MusicPlay(D1,500,50,0);
			MusicPlay(C1,250,50,0);
			MusicPlay(C1,750,50,0);
			MusicTurn(C1,B0,800,50,100);
			Musicdisap(150);
			MusicTurn(B0,C1,1500,250,750);
			Musicdisap(1500);
		}
		else
		{MusicPlay1(0,750);}
	//	osDelay(1);
	}
}
void MusicPlay(uint16_t name,uint16_t length,uint16_t time1,uint16_t time2)
{
	length*=SPEED;
	time1*=SPEED;
	time2*=SPEED;
	if(time2==0)time2=length*0.8f;
	switch(name){
		case C0: HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET);break;
		case C1: HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET);break;
		case C2: HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET);break;
		case D0: HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_RESET);break;
		case D1: HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_RESET);break;
		case D2: HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_RESET);break;
		case E0: HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_RESET);break;
		case E1: HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_RESET);break;
		case E2: HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_RESET);break;
		case F0: HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case F1: HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case F1U:HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case F2: HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case G0: HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET);break;
		case G1: HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET);break;
		case G2: HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET);break;
		case A0: HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET);break;
		case A1: HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET);break;
		case A2: HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET);break;
		case B0: HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET);break;
		case B1: HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET);break;
		case B2: HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET);break;
		default: break;
	}
	uint8_t i;
	__HAL_TIM_SET_AUTORELOAD(&BUZZER_TIM,1000000/name);
	for(i=0;i<50;i++)
	{
	__HAL_TIM_SET_COMPARE(&BUZZER_TIM,BUZZER_CHANNEL,i*2);
	HAL_Delay(time1/50);
	}
	HAL_Delay(time2-time1);
	for(i=0;i<50;i++)
	{
	__HAL_TIM_SET_COMPARE(&BUZZER_TIM,BUZZER_CHANNEL,100-i*2);
	HAL_Delay((length-time2)/50);
	}
	
	HAL_GPIO_WritePin(D1_GPIO_Port,GPIO_PIN_All,GPIO_PIN_SET);
}
void MusicTurn(uint16_t name1,uint16_t name2,uint16_t length,uint16_t time1,uint16_t time2)
{
		length*=SPEED;
	time1*=SPEED;
	time2*=SPEED;
	switch(name1){
		case C0: HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET);break;
		case C1: HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET);break;
		case C2: HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET);break;
		case D0: HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_RESET);break;
		case D1: HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_RESET);break;
		case D2: HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_RESET);break;
		case E0: HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_RESET);break;
		case E1: HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_RESET);break;
		case E2: HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_RESET);break;
		case F0: HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case F1: HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case F1U:HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case F2: HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case G0: HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET);break;
		case G1: HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET);break;
		case G2: HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET);break;
		case A0: HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET);break;
		case A1: HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET);break;
		case A2: HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET);break;
		case B0: HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET);break;
		case B1: HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET);break;
		case B2: HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET);break;
		default: break;
	}
	uint8_t i;
	__HAL_TIM_SET_AUTORELOAD(&BUZZER_TIM,1000000/name1);
	__HAL_TIM_SET_COMPARE(&BUZZER_TIM,BUZZER_CHANNEL,100);
	HAL_Delay(time1);
	for(i=0;i<50;i++)
	{
	__HAL_TIM_SET_AUTORELOAD(&BUZZER_TIM,1000000/(name1+(name2-name1)/50.0f*i));	HAL_Delay((time2-time1)/50);
	}
	HAL_Delay(length-time2);
	HAL_GPIO_WritePin(D1_GPIO_Port,GPIO_PIN_All,GPIO_PIN_SET);
}
void MusicPlay1(uint16_t name,uint16_t length)
{
		length*=SPEED;

	switch(name){
		case C0: HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET);break;
		case C1: HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET);break;
		case C2: HAL_GPIO_WritePin(D1_GPIO_Port,D1_Pin,GPIO_PIN_RESET);break;
		case D0: HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_RESET);break;
		case D1: HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_RESET);break;
		case D2: HAL_GPIO_WritePin(D2_GPIO_Port,D2_Pin,GPIO_PIN_RESET);break;
		case E0: HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_RESET);break;
		case E1: HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_RESET);break;
		case E2: HAL_GPIO_WritePin(D3_GPIO_Port,D3_Pin,GPIO_PIN_RESET);break;
		case F0: HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case F1: HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case F1U:HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case F2: HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET);break;
		case G0: HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET);break;
		case G1: HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET);break;
		case G2: HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET);break;
		case A0: HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET);break;
		case A1: HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET);break;
		case A2: HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET);break;
		case B0: HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET);break;
		case B1: HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET);break;
		case B2: HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET);break;
		default: break;
	}
	__HAL_TIM_SET_AUTORELOAD(&BUZZER_TIM,1000000/name);
	__HAL_TIM_SET_COMPARE(&BUZZER_TIM,BUZZER_CHANNEL,100);
	HAL_Delay(length);
	HAL_GPIO_WritePin(D1_GPIO_Port,GPIO_PIN_All,GPIO_PIN_SET);
}
void Musicdisap(uint16_t length)
{
	uint8_t i;
	for(i=0;i<50;i++)
	{
	__HAL_TIM_SET_COMPARE(&BUZZER_TIM,BUZZER_CHANNEL,100-i*2);
	HAL_Delay(length/50);
	}
}
	
void StartShowTask(void const * argument)
{
//	__HAL_TIM_SET_AUTORELOAD(&htim4,38000);
//	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,(38000/2+1));
}
			
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
/*******************************************************************************************************************
jojo标准结局
			MusicPlay1(D0,75);
			MusicPlay(E0,2450,0,1000);
			MusicPlay1(G1,75);
			MusicPlay1(B2,75);
			MusicPlay(E2,3250,0,1000);
			MusicPlay1(B1,1000);
			MusicPlay1(A1,166);
			MusicPlay1(B1,166);
			MusicPlay1(A1,166);
			MusicPlay1(G1,250);
			MusicPlay1(F1U,1000);
			MusicPlay(A1,3000,0,2000);
			
			MusicPlay1(D0,75);
			MusicPlay(E0,2450,0,1000);
			MusicPlay1(G1,75);
			MusicPlay1(B2,75);
			MusicPlay(E2,3250,0,1000);
			MusicPlay1(B1,1000);
			MusicPlay1(A1,166);
			MusicPlay1(B1,166);
			MusicPlay1(A1,166);
			MusicPlay1(G1,250);
			MusicPlay1(F1U,1000);
			MusicPlay1(B0,166);
			MusicPlay1(C1,166);
			MusicPlay1(D1,166);
			MusicPlay1(F0U,166);
			MusicPlay1(G0,166);
			MusicPlay1(A0,166);
			MusicPlay(C0,4000,0,2500);
			
			MusicPlay1(D0,75);
			MusicPlay(E0,2450,0,1000);
			MusicPlay1(G1,75);
			MusicPlay1(B2,75);
			MusicPlay(E2,3250,0,1000);
			MusicPlay1(B1,1000);
			MusicPlay1(A1,166);
			MusicPlay1(B1,166);
			MusicPlay1(A1,166);
			MusicPlay1(G1,250);
			MusicPlay1(F1U,1000);
			MusicPlay1(A1,1000);
			MusicPlay(F1U,4000,0,2500);
			
			MusicPlay1(F1U,325*0.95);
			MusicPlay1(G1,250*0.95);
			MusicPlay1(G1,83*0.95);
			MusicPlay1(F1U,83*0.95);
			MusicPlay1(E1,83*0.95);
			MusicPlay1(D1,250*0.95);
			MusicPlay1(E1,250*0.95);
			MusicPlay1(D1,250*0.95);
			MusicPlay1(C1,250*0.95);
			MusicPlay1(B0,250*0.95);
			MusicPlay1(D1,250*0.95);
			MusicPlay1(B0,250*0.95);
			MusicPlay1(C1,250*0.95);
			MusicPlay1(A0,250*0.95);
			MusicPlay1(B0,250*0.95);
			MusicPlay1(G0,250*0.95);
			MusicPlay1(A0,250*0.95);

			MusicPlay1(E0,500*0.95);
			MusicPlay1(E1,300*0.95);
			MusicPlay1(F1U,500*0.95);
			MusicPlay1(G1,500*0.95);
			MusicPlay1(F1U,500*0.95);
			MusicPlay1(G1,500*0.95);
			MusicPlay1(F1U,250*0.95);
			MusicPlay1(E1,750*0.95);
			MusicPlay1(E0,250*0.95);
			MusicPlay1(E1,500*0.95);
			MusicPlay1(E1,250*0.95);
			MusicPlay1(F1U,500*0.95);
			MusicPlay1(G1,500*0.95);
			MusicPlay1(F1U,250*0.95);
			MusicPlay1(E1,750*0.95);
			MusicPlay1(E0,300*0.95);
			MusicPlay1(E2,120*0.95);
			MusicPlay1(D2,120*0.95);
			MusicPlay1(B1,120*0.95);
			MusicPlay1(A1,120*0.95);
			MusicPlay1(B1,120*0.95);
			MusicPlay1(A1,120*0.95);
			MusicPlay1(G1,120*0.95);
			MusicPlay1(F1,120*0.95);
			MusicPlay1(E0,250*0.95);
			MusicPlay1(E1,250*0.95);
			MusicPlay1(F1U,500*0.95);
			MusicPlay1(G1,500*0.95);
			MusicPlay1(F1U,500*0.95);
			MusicPlay1(G1,500*0.95);
			MusicPlay1(F1U,250*0.95);
			MusicPlay1(E1,750*0.95);
			MusicPlay1(E0,250*0.95);
			MusicPlay1(E1,500*0.95);
			MusicPlay1(E1,250*0.95);
			MusicPlay1(F1U,500*0.95);
			MusicPlay1(G1,500*0.95);
			MusicPlay1(F1U,250*0.95);
			MusicPlay1(E1,750*0.95);
			MusicPlay1(E0,300*0.95);
			MusicPlay1(E2,120*0.95);
			MusicPlay1(D2,120*0.95);
			MusicPlay1(B1,120*0.95);
			MusicPlay1(A1,120*0.95);
			MusicPlay1(B1,120*0.95);
			MusicPlay1(A1,120*0.95);
			MusicPlay1(G1,120*0.95);
			MusicPlay1(F1,120*0.95);
*******************************************************************************************************************/
