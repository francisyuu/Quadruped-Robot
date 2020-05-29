#include "remote.h"
#include "DBUS.h"

#include "legctrl.h"
/**
* @name ���в��� Ҳ�����Զ���ģʽuint8_t�Ǹ����͵Ĵ������
* @{
*/

#define RUNNING		0//<����ʱ����
#define STARTING	1//<����ʱ����
#define ENDING		2//<����ʱ����
#define UU 11
#define UM 13
#define UD 12
#define MU 31
#define MM 33
#define MD 32
#define DU 21
#define DM 23
#define DD 22


/**
    * @brief mode ��һ���ֽ���Ϊң����ģʽ�����ϵ�λ����ߵ�ң������Ϊ��λ���ұߵ�ң������Ϊ��λ �� ���Ϊ1 �ұ�Ϊ3 ��Ϊ13 00Ϊ��Ч
		* @brief last_mode��һ��ң������ֵ�����ڶԱ��л�ģʽ
    */
uint8_t mode=0;
uint8_t last_mode=0xff;


/** 
* @brief  ��ȫģʽ
* @param  NULL
*/
static void Safe_ctl(uint8_t type)
{
			__HAL_TIM_SET_COMPARE(&STEER1_TIM,STEER1_CHANNEL,0);
			__HAL_TIM_SET_COMPARE(&STEER2_TIM,STEER2_CHANNEL,0);
			__HAL_TIM_SET_COMPARE(&STEER3_TIM,STEER3_CHANNEL,0);
			__HAL_TIM_SET_COMPARE(&STEER4_TIM,STEER4_CHANNEL,0);
			__HAL_TIM_SET_COMPARE(&STEER5_TIM,STEER5_CHANNEL,0);
			__HAL_TIM_SET_COMPARE(&STEER6_TIM,STEER6_CHANNEL,0);
			__HAL_TIM_SET_COMPARE(&STEER7_TIM,STEER7_CHANNEL,0);
			__HAL_TIM_SET_COMPARE(&STEER8_TIM,STEER8_CHANNEL,0);
			__HAL_TIM_SET_COMPARE(&STEER9_TIM,STEER9_CHANNEL,0);
			__HAL_TIM_SET_COMPARE(&STEER10_TIM,STEER10_CHANNEL,0);
			__HAL_TIM_SET_COMPARE(&STEER11_TIM,STEER11_CHANNEL,0);
			__HAL_TIM_SET_COMPARE(&STEER12_TIM,STEER12_CHANNEL,0);
}
/** 
* @brief  Trot��̬
* @param  NULL
*/
static void Trot_Mode(uint8_t type)//
{
	    switch(type)
    {
    case STARTING:
				PIT_ROL_PID_Set(Trot_Mode_PAR);
    case RUNNING:
			
				if(RC_Ctl.rc0.ch0==0&&RC_Ctl.rc0.ch2==0&&RC_Ctl.rc0.ch3==0)
				{
					for(uint8_t i=0;i<4;i++)
					{
						legs[i].trot.footheight=0.05;
					}
				}
				else
				{
					for(uint8_t i=0;i<4;i++)
					{
						legs[i].trot.footheight=0.05;
					}
				}
				
				trot(legs,RC_Ctl.rc0.ch3,RC_Ctl.rc0.ch2,RC_Ctl.rc0.ch0);
				//balance(legs,ROL_PID.output,PIT_PID.output,0);
				robot_run(legs);
        break;
    case ENDING:

        break;
    }

}
/** 
* @brief  ƽ��ģʽ
* @param  NULL
*/
static void Balance_Mode(uint8_t type)//
{
	    switch(type)
    {
			case STARTING:
			{
				PIT_ROL_PID_Set(Balance_Mode_PAR);
				break;
			}
			case RUNNING:	
			{
				
								for(uint8_t i=0;i<4;i++)
				{
					legs[i].pos.x=200;
					legs[i].pos.y=-100*(i%2)+50;
					legs[i].pos.z=0;
				}
					balance(legs,ROL_PID.output,PIT_PID.output,0);
					robot_run(legs);
					break;
			}
			case ENDING:
			{
			
					break;
			}
			default:
				break;
    }

}
/** 
* @brief  Ĭ��ֵģʽ
* @param  NULL
*/
static void OFFSET_ADJ(uint8_t type)//
{
	    switch(type)
    {
			case STARTING:
			{
	
				break;
			}
			case RUNNING:	
			{
				pwm_offset_run(legs);
				break;
			}
			case ENDING:
			{
					break;
			}
			default:
				break;
    }

}
/** 
* @brief  Ť��ģʽ
* @param  NULL
*/
static void Twist(uint8_t type)//
{
	    switch(type)
    {
			case STARTING:
			{
				PIT_ROL_PID_Set(Twist_Mode_PAR);
					break;
			}
			case RUNNING:	
			{
								for(uint8_t i=0;i<4;i++)
				{
					legs[i].pos.x=200;
					legs[i].pos.y=-100*(i%2)+50;
					legs[i].pos.z=0;
				}
					balance(legs,RC_Ctl.rc0.ch3/20,-RC_Ctl.rc0.ch2/20,-RC_Ctl.rc0.ch0/30);
					robot_run(legs);
					break;
			}
			case ENDING:
			{
				
					break;
			}
    }

}
/** 
* @brief  
* @param  NULL
*/
static void l_safe(uint8_t type)//
{
	    switch(type)
    {
			case STARTING:
			{
			
					break;
			}
			case RUNNING:	
			{
				
					break;
			}
			case ENDING:
			{
					break;
			}
    }

}

/**
* @brief  ����ң����ģʽ�ĺ���
* @detail ��������Ҫ���Լ���������к�������ң����ģʽ�����switch�е���
* @par ��־
* @retval none
*
*/
static void Mode_Ctrl(uint8_t mode,uint8_t type)
{
    switch(mode)
    {
    case 0:
        Safe_ctl(type);
        return;
    case UU:
				Trot_Mode(type);
        return;
    case UM:
        Balance_Mode(type);
        return;
    case UD:     
				Twist(type);
        return;
		
    case MU:
        //CmptControl(type);
        return;
    case MM:
         Safe_ctl(type);
        return;
    case MD:
				//Twist(type);
        return;
		
    case DU:
        //MouseControl(type);
        return;	
    case DM:
        OFFSET_ADJ(type);
        return;
    case DD:
        Safe_ctl(type);
        return;
    default:
        Safe_ctl(type);
        return;
    }
}

/**
* @brief  ��׼�������� �;��幦���޹�
* @detail ֻ��Ҫ�Ѹú�������һ����������ִ�еĵط����ɽ���ң��������
* @retval  0 OK
* @log ����ֵĿǰ��Ч
*
*/
uint8_t Remote_Handle(void)
{

	if(1)
	{
    mode=RC_Ctl.rc.s1*10+RC_Ctl.rc.s2;
    if(mode!=last_mode)//�ո��л���ģʽ������ģʽ��ʼ��
    {
        Mode_Ctrl(last_mode,ENDING);//�˳�֮ǰ��ģʽ
        Mode_Ctrl(mode,STARTING);//���õ�ǰģʽ
        last_mode = mode;
        return 0;
    }
	}
	else
	{
		mode=DD;
	}
	Mode_Ctrl(mode,0);//������ǰģʽ
    return 0;
}

