#include "legctrl.h"
#include "math.h"
#include "bsp_imu.h"

int STEER_OFFSET[12] = {1300,1220,1715,1395,1485,1400,1485,1920,1500,1750,1175,1525};
leg_t legs[4];
PID PIT_PID,ROL_PID,SPEED_Y_PID,SPEED_Z_PID;

float Limit(float a,float amax,float amin)
{
	if(a>amax)return amax;
	else if(a<amin)return amin;
	else return a;
}
/*******PWM相关函数**********************************************/
void pwm_start_all()
{
	HAL_TIM_PWM_Start(&STEER1_TIM,STEER1_CHANNEL);
	HAL_TIM_PWM_Start(&STEER2_TIM,STEER2_CHANNEL);
	HAL_TIM_PWM_Start(&STEER3_TIM,STEER3_CHANNEL);
	HAL_TIM_PWM_Start(&STEER4_TIM,STEER4_CHANNEL);
	HAL_TIM_PWM_Start(&STEER5_TIM,STEER5_CHANNEL);
	HAL_TIM_PWM_Start(&STEER6_TIM,STEER6_CHANNEL);
	HAL_TIM_PWM_Start(&STEER7_TIM,STEER7_CHANNEL);
	HAL_TIM_PWM_Start(&STEER8_TIM,STEER8_CHANNEL);
	HAL_TIM_PWM_Start(&STEER9_TIM,STEER9_CHANNEL);
	HAL_TIM_PWM_Start(&STEER10_TIM,STEER10_CHANNEL);
	HAL_TIM_PWM_Start(&STEER11_TIM,STEER11_CHANNEL);
	HAL_TIM_PWM_Start(&STEER12_TIM,STEER12_CHANNEL);
}
void pwm_calcu(leg_t *leg)
{
		leg[0].pwm.pwm1=STEER_OFFSET[0]+Limit(leg[0].theta.theta1,PI/4,-PI/4)*r2p;
		leg[0].pwm.pwm2=STEER_OFFSET[4]+Limit(leg[0].theta.theta2,PI/2,-PI/2)*r2p;
		leg[0].pwm.pwm3=STEER_OFFSET[8]-Limit(leg[0].theta.theta3+PI/2,PI/3,-PI/6)*r2p;
	
		leg[1].pwm.pwm1=STEER_OFFSET[1]+Limit(leg[1].theta.theta1,PI/4,-PI/4)*r2p;
		leg[1].pwm.pwm2=STEER_OFFSET[5]+Limit(leg[1].theta.theta2,PI/2,-PI/2)*r2p;
		leg[1].pwm.pwm3=STEER_OFFSET[9]-Limit(leg[1].theta.theta3-PI/2,PI/6,-PI/3)*r2p;
	
		leg[2].pwm.pwm1=STEER_OFFSET[2]-Limit(leg[2].theta.theta1,PI/4,-PI/4)*r2p;
		leg[2].pwm.pwm2=STEER_OFFSET[6]+Limit(leg[2].theta.theta2,PI/2,-PI/2)*r2p;
		leg[2].pwm.pwm3=STEER_OFFSET[10]-Limit(leg[2].theta.theta3+PI/2,PI/3,-PI/6)*r2p;

		leg[3].pwm.pwm1=STEER_OFFSET[3]-Limit(leg[3].theta.theta1,PI/4,-PI/4)*r2p;
		leg[3].pwm.pwm2=STEER_OFFSET[7]+Limit(leg[3].theta.theta2,PI/2,-PI/2)*r2p;
		leg[3].pwm.pwm3=STEER_OFFSET[11]-Limit(leg[3].theta.theta3-PI/2,PI/6,-PI/3)*r2p;
}
void pwm_set(leg_t *leg)
{
	__HAL_TIM_SET_COMPARE(&STEER1_TIM,STEER1_CHANNEL,leg[0].pwm.pwm1);
	__HAL_TIM_SET_COMPARE(&STEER2_TIM,STEER2_CHANNEL,leg[1].pwm.pwm1);
	__HAL_TIM_SET_COMPARE(&STEER3_TIM,STEER3_CHANNEL,leg[2].pwm.pwm1);
	__HAL_TIM_SET_COMPARE(&STEER4_TIM,STEER4_CHANNEL,leg[3].pwm.pwm1);
	__HAL_TIM_SET_COMPARE(&STEER5_TIM,STEER5_CHANNEL,leg[0].pwm.pwm2);
	__HAL_TIM_SET_COMPARE(&STEER6_TIM,STEER6_CHANNEL,leg[1].pwm.pwm2);
	__HAL_TIM_SET_COMPARE(&STEER7_TIM,STEER7_CHANNEL,leg[2].pwm.pwm2);
	__HAL_TIM_SET_COMPARE(&STEER8_TIM,STEER8_CHANNEL,leg[3].pwm.pwm2);
	__HAL_TIM_SET_COMPARE(&STEER9_TIM,STEER9_CHANNEL,leg[0].pwm.pwm3);
	__HAL_TIM_SET_COMPARE(&STEER10_TIM,STEER10_CHANNEL,leg[1].pwm.pwm3);
	__HAL_TIM_SET_COMPARE(&STEER11_TIM,STEER11_CHANNEL,leg[2].pwm.pwm3);
	__HAL_TIM_SET_COMPARE(&STEER12_TIM,STEER12_CHANNEL,leg[3].pwm.pwm3);
}
void pwm_offset_run(leg_t *leg)
{
		leg[0].pwm.pwm1=STEER_OFFSET[0];
		leg[0].pwm.pwm2=STEER_OFFSET[4];
		leg[0].pwm.pwm3=STEER_OFFSET[8];
	
		leg[1].pwm.pwm1=STEER_OFFSET[1];
		leg[1].pwm.pwm2=STEER_OFFSET[5];
		leg[1].pwm.pwm3=STEER_OFFSET[9];
	
		leg[2].pwm.pwm1=STEER_OFFSET[2];
		leg[2].pwm.pwm2=STEER_OFFSET[6];
		leg[2].pwm.pwm3=STEER_OFFSET[10];

		leg[3].pwm.pwm1=STEER_OFFSET[3];
		leg[3].pwm.pwm2=STEER_OFFSET[7];
		leg[3].pwm.pwm3=STEER_OFFSET[11];
	
		__HAL_TIM_SET_COMPARE(&STEER1_TIM,STEER1_CHANNEL,leg[0].pwm.pwm1);
		__HAL_TIM_SET_COMPARE(&STEER2_TIM,STEER2_CHANNEL,leg[1].pwm.pwm1);
		__HAL_TIM_SET_COMPARE(&STEER3_TIM,STEER3_CHANNEL,leg[2].pwm.pwm1);
		__HAL_TIM_SET_COMPARE(&STEER4_TIM,STEER4_CHANNEL,leg[3].pwm.pwm1);
		__HAL_TIM_SET_COMPARE(&STEER5_TIM,STEER5_CHANNEL,leg[0].pwm.pwm2);
		__HAL_TIM_SET_COMPARE(&STEER6_TIM,STEER6_CHANNEL,leg[1].pwm.pwm2);
		__HAL_TIM_SET_COMPARE(&STEER7_TIM,STEER7_CHANNEL,leg[2].pwm.pwm2);
		__HAL_TIM_SET_COMPARE(&STEER8_TIM,STEER8_CHANNEL,leg[3].pwm.pwm2);
		__HAL_TIM_SET_COMPARE(&STEER9_TIM,STEER9_CHANNEL,leg[0].pwm.pwm3);
		__HAL_TIM_SET_COMPARE(&STEER10_TIM,STEER10_CHANNEL,leg[1].pwm.pwm3);
		__HAL_TIM_SET_COMPARE(&STEER11_TIM,STEER11_CHANNEL,leg[2].pwm.pwm3);
		__HAL_TIM_SET_COMPARE(&STEER12_TIM,STEER12_CHANNEL,leg[3].pwm.pwm3);
}
/*******姿态解算**********************************************/
void inverse_kinematics(leg_t *leg)
{
	float x,y,z,C3,S3,midpar;
	for(uint8_t i=0;i<4;i++)
	{
		x=leg[i].pos.x+x_offset_Robot;
		y=leg[i].pos.y+y_offset_Robot-bodyheight*1000*tan(PIT_PID.output/180*PI);
		z=leg[i].pos.z+z_offset_Robot+bodyheight*1000*tan(ROL_PID.output/180*PI);
		midpar=sqrt(x*x+y*y);
		if((i==0)|(i==2))
		{
			leg[i].theta.theta1=atan2(-d1/midpar,sqrt(1-d1*d1/midpar/midpar))+atan2(y,x);//第1处else里需要改符号的地方
			C3=(x*x+y*y+z*z-a1*a1-a2*a2-d1*d1)/(2*a1*a2);
			S3=-sqrt(1-C3*C3);//2
			leg[i].theta.theta3=atan2(S3,C3);
			midpar=sqrt((a1+a2*C3)*(a1+a2*C3)+(a2*S3)*(a2*S3));
			leg[i].theta.theta2=atan2(a1+a2*C3,a2*S3)-atan2(sqrt(1-z*z/midpar/midpar),-z/midpar);//3
		}
		else
		{
			leg[i].theta.theta1=atan2(d1/midpar,sqrt(1-d1*d1/midpar/midpar))+atan2(y,x);
			C3=(x*x+y*y+z*z-a1*a1-a2*a2-d1*d1)/(2*a1*a2);
			S3=sqrt(1-C3*C3);
			leg[i].theta.theta3=atan2(S3,C3);
			midpar=sqrt((a1+a2*C3)*(a1+a2*C3)+(a2*S3)*(a2*S3));
			leg[i].theta.theta2=atan2(a1+a2*C3,a2*S3)-atan2(sqrt(1-z*z/midpar/midpar),z/midpar);
		}
	}
}



/*******PID相关函数**********************************************/
/** 
* @brief  
* @param [in]   input 传入pid环的误差 
* @param [in]   * Din 自定义微分数据
* @retval  pid的运行输出 
* @par 日志 
*
*/
float pid_run(PID* pid,float input,float* Din)
{
	pid->CurrentInput = input;
	
	if(pid->Tolerance!=0&&(input>-pid->Tolerance)&&(input<pid->Tolerance))pid->Pout = 0;//M增加允差判断
	else pid->Pout = pid->CurrentInput*pid->P;
	
	if((pid->CurrentInput < pid->I_Limited)&&(pid->CurrentInput > -pid->I_Limited))//仅在小于误差区间时进行I积分
		pid->Iout += pid->I *	pid->CurrentInput;
	else pid->Iout=0;
	
	if(Din!=NULL)
		pid->Dout=*Din*pid->D;
	else
		pid->Dout=(pid->CurrentInput - pid->LastInput)*pid->D;
	
	pid->Iout=Limit(pid->Iout,pid->IMax,-pid->IMax);
	
	pid->output = pid->Pout + pid->Iout + pid->Dout;
	
	pid->output=Limit(pid->output,pid->PIDMax,-pid->PIDMax);
	
	pid->LastInput=pid->CurrentInput;
	return pid->output;
}

struct{
	float T;//单腿周期，单位ms
	float ekT2;//exp(k_midpar*Tsupport/2)
	float _ekT2;//exp(-k_midpar*Tsupport/2)
	float ektS;//exp(k_midpar*timeS)
	float _ektS;//exp(k_midpar*timeS)
	float ektI;//exp(k_midpar*timeI)
	float _ektI;//exp(k_midpar*timeS)
	float kt_1000;//1000.0f*k_midpar*Tsupport
	float PI2_T;//2*PI/Timpend
	float kPI2_T;//kcycloid*2*PI/Timpend
	float k2PI;//kcycloid*2*PI
	
}chs;//trot_simple,用于存储固定变量从而节约运算时间的数组
void chs_INIT(void)
{
	chs.T=(Timpend+Tsupport)*1000.0f;
	chs.ekT2=exp(k_midpar*Tsupport/2);
	chs._ekT2=exp(-k_midpar*Tsupport/2);
	chs.kt_1000=k_midpar*Tsupport/1000;
	chs.PI2_T=2*PI/Timpend;
	chs.kPI2_T=kcycloid*2*PI/Timpend;
	chs.k2PI=kcycloid*2*PI;
}

/** 
* @brief  姿态计算——Trot步态 
* @par log 输入速度前两个单位为mm/s 理论值，turnspeed对应每一步的度数，最大值约660*0.00075*2*57.3=56.7°
*/
void trot(leg_t *leg,int16_t zspeed,int16_t yspeed,int16_t turnspeed)
{
	imu.speedx.v+=pid_run(&SPEED_Y_PID,zspeed-imu.speedx.v,NULL);
	static uint32_t time,time1;
	time=HAL_GetTick()%(uint32_t)(chs.T);
	time1=(HAL_GetTick()-(uint32_t)(chs.T/2))%(uint32_t)(chs.T);
	if(time<(Tsupport*1000))
	{
		float timeS;
		timeS=(time/1000.0f-Tsupport/2);
		
		float zturn,yturn,zturn0,yturn0,thetaturn;
		thetaturn=THETA0-0.00075f*turnspeed+0.0015*turnspeed*time/1000.0f/Tsupport;
		zturn=LR*cos(thetaturn)-L1_half;
		yturn=LR*sin(thetaturn)-L2_half;
		zturn0=LR*cos(THETA0-0.00075f*turnspeed)-L1_half;
		yturn0=LR*sin(THETA0-0.00075f*turnspeed)-L2_half;
		
		chs.ektS=exp(k_midpar*timeS);
		chs._ektS=1/chs.ektS;
		
		leg[0].trot.v0z=zspeed*chs.kt_1000/
										 (chs.ekT2-chs._ekT2);
		leg[0].pos.z=zturn-1000*leg[0].trot.v0z*(chs.ektS-chs._ektS)/(2*k_midpar);
		leg[0].trot.z0=zturn0-1000*leg[0].trot.v0z*(chs._ekT2-chs.ekT2)/(2*k_midpar);
		leg[0].trot.z1=leg[0].pos.z;
		
		leg[0].trot.v0y=yspeed*chs.kt_1000/
										 (chs.ekT2-chs._ekT2);
		leg[0].pos.y=yturn+50+1000*leg[0].trot.v0y*(chs.ektS-chs._ektS)/(2*k_midpar);
		leg[0].trot.y0=yturn0+50+1000*leg[0].trot.v0y*(chs._ekT2-chs.ekT2)/(2*k_midpar);
		leg[0].trot.y1=leg[0].pos.y;
		
		leg[0].pos.x=1000*bodyheight;
		
		leg[3].trot.v0z=leg[0].trot.v0z;
		leg[3].pos.z=-zturn*2+leg[0].pos.z;
		leg[3].trot.z0=-zturn0*2+leg[0].trot.z0;
		leg[3].trot.z1=leg[3].pos.z;
		
		leg[3].trot.v0y=leg[0].trot.v0y;
		leg[3].pos.y=-yturn*2-100+leg[0].pos.y;
		leg[3].trot.y0=-yturn0*2-100+leg[0].trot.y0;
		leg[3].trot.y1=leg[3].pos.y;
		
		leg[3].pos.x=leg[0].pos.x;
	}
	//抬腿摆线部分
	else
	{
		float timeI;
		timeI=(time/1000.0f-Tsupport);
		leg[0].pos.z=leg[0].trot.z1+(leg[0].trot.z0-leg[0].trot.z1)/(chs.k2PI)
																*(chs.kPI2_T*timeI-sin(2*PI*timeI/Timpend));
		leg[0].pos.y=leg[0].trot.y1+(leg[0].trot.y0-leg[0].trot.y1)/(chs.k2PI)
																*(chs.kPI2_T*timeI-sin(2*PI*timeI/Timpend));
		leg[0].pos.x=1000*(bodyheight-leg[0].trot.footheight/2*(1-cos(chs.PI2_T*timeI)));
		
		leg[3].pos.z=leg[3].trot.z1+(leg[3].trot.z0-leg[3].trot.z1)/(chs.k2PI)
																*(chs.kPI2_T*timeI-sin(2*PI*timeI/Timpend));
		leg[3].pos.y=leg[3].trot.y1+(leg[3].trot.y0-leg[3].trot.y1)/(chs.k2PI)
																*(chs.kPI2_T*timeI-sin(2*PI*timeI/Timpend));
		leg[3].pos.x=1000*(bodyheight-leg[3].trot.footheight/2*(1-cos(chs.PI2_T*timeI)));
	}
	if(time1<(Tsupport*1000))
	{
		float timeS;
		timeS=(time1/1000.0f-Tsupport/2);
		
		float zturn,yturn,zturn0,yturn0,thetaturn;
		thetaturn=THETA0+0.00075f*turnspeed-0.0015*turnspeed*time1/1000.0f/Tsupport;
		zturn=-LR*cos(thetaturn)+L1_half;
		yturn=LR*sin(thetaturn)-L2_half;
		zturn0=-LR*cos(THETA0+0.00075f*turnspeed)+L1_half;
		yturn0=LR*sin(THETA0+0.00075f*turnspeed)-L2_half;
		
		chs.ektS=exp(k_midpar*timeS);
		chs._ektS=1/chs.ektS;
		
		leg[2].trot.v0z=zspeed*chs.kt_1000/
										 (chs.ekT2-chs._ekT2);
		leg[2].pos.z=zturn-1000*leg[2].trot.v0z*(chs.ektS-chs._ektS)/(2*k_midpar);
		leg[2].trot.z0=zturn0-1000*leg[2].trot.v0z*(chs._ekT2-chs.ekT2)/(2*k_midpar);
		leg[2].trot.z1=leg[2].pos.z;
		
		leg[2].trot.v0y=yspeed*chs.kt_1000/
										 (chs.ekT2-chs._ekT2);
		leg[2].pos.y=yturn+50+1000*leg[2].trot.v0y*(chs.ektS-chs._ektS)/(2*k_midpar);
		leg[2].trot.y0=yturn0+50+1000*leg[2].trot.v0y*(chs._ekT2-chs.ekT2)/(2*k_midpar);
		leg[2].trot.y1=leg[2].pos.y;
		
		leg[2].pos.x=1000*bodyheight;
		
		leg[1].trot.v0z=leg[2].trot.v0z;
		leg[1].pos.z=-zturn*2+leg[2].pos.z;
		leg[1].trot.z0=-zturn0*2+leg[2].trot.z0;
		leg[1].trot.z1=leg[1].pos.z;
		
		leg[1].trot.v0y=leg[2].trot.v0y;
		leg[1].pos.y=-yturn*2-100+leg[2].pos.y;
		leg[1].trot.y0=-yturn0*2-100+leg[2].trot.y0;
		leg[1].trot.y1=leg[1].pos.y;
		
		leg[1].pos.x=leg[2].pos.x;
	}
	else
	{
		float timeI;
		timeI=(time1/1000.0f-Tsupport);
		leg[2].pos.z=leg[2].trot.z1+(leg[2].trot.z0-leg[2].trot.z1)/(chs.k2PI)
																*(chs.kPI2_T*timeI-sin(chs.PI2_T*timeI));
		leg[2].pos.y=leg[2].trot.y1+(leg[2].trot.y0-leg[2].trot.y1)/(chs.k2PI)
																*(chs.kPI2_T*timeI-sin(chs.PI2_T*timeI));
		leg[2].pos.x=1000*(bodyheight-leg[2].trot.footheight/2*(1-cos(chs.PI2_T*timeI)));
		
		leg[1].pos.z=leg[1].trot.z1+(leg[1].trot.z0-leg[1].trot.z1)/(chs.k2PI)
																*(chs.kPI2_T*timeI-sin(chs.PI2_T*timeI));
		leg[1].pos.y=leg[1].trot.y1+(leg[1].trot.y0-leg[1].trot.y1)/(chs.k2PI)
																*(chs.kPI2_T*timeI-sin(chs.PI2_T*timeI));
		leg[1].pos.x=1000*(bodyheight-leg[1].trot.footheight/2*(1-cos(chs.PI2_T*timeI)));
	}
	
}
/** 
    * @brief 将pos的位置更新到pos0
*/
void pos0_update_pos(leg_t *leg)
{

		leg[0].pos0.x=leg[0].pos.x;
		leg[0].pos0.y=leg[0].pos.y+L2_half;
		leg[0].pos0.z=leg[0].pos.z+L1_half;
		
		leg[1].pos0.x=leg[1].pos.x;
		leg[1].pos0.y=leg[1].pos.y-L2_half;
		leg[1].pos0.z=leg[1].pos.z+L1_half;
		
		leg[2].pos0.x=leg[2].pos.x;
		leg[2].pos0.y=leg[2].pos.y+L2_half;
		leg[2].pos0.z=leg[2].pos.z-L1_half;
		
		leg[3].pos0.x=leg[3].pos.x;
		leg[3].pos0.y=leg[3].pos.y-L2_half;
		leg[3].pos0.z=leg[3].pos.z-L1_half;
}
/** 
    * @brief 将pos0的位置更新到pos
*/
void pos_update_pos0(leg_t *leg)
{
		leg[0].pos.x=leg[0].pos0.x;
		leg[0].pos.y=leg[0].pos0.y-L2_half;
		leg[0].pos.z=leg[0].pos0.z-L1_half;
		
		leg[1].pos.x=leg[1].pos0.x;
		leg[1].pos.y=leg[1].pos0.y+L2_half;
		leg[1].pos.z=leg[1].pos0.z-L1_half;
		
		leg[2].pos.x=leg[2].pos0.x;
		leg[2].pos.y=leg[2].pos0.y-L2_half;
		leg[2].pos.z=leg[2].pos0.z+L1_half;
		
		leg[3].pos.x=leg[3].pos0.x;
		leg[3].pos.y=leg[3].pos0.y+L2_half;
		leg[3].pos.z=leg[3].pos0.z+L1_half;
}
/** 
* @brief  姿态计算——平衡模式 
* @brief rol pit yaw是陀螺仪坐标系
*/
void balance(leg_t *leg,float rol,float pit,float yaw)
{
	float R[3][3],//旋转矩阵
				position[3][4];//坐标缓存
	//robot_x=imu_z,robot_y=-imu_x,robot_z=imu_y
	float cr,sr,cp,sp,cy,sy;
	cr=cos(rol/180*PI);
	sr=sin(rol/180*PI);
	cp=cos(pit/180*PI);
	sp=sin(pit/180*PI);
	cy=cos(yaw/180*PI);
	sy=sin(yaw/180*PI);
	
	R[0][0]=cr*cp;
	R[0][1]=sr*sy-cr*cy*sp;
	R[0][2]=cy*sr+cr*sp*sy;
	R[1][0]=sp;
	R[1][1]=cp*cy;
	R[1][2]=-cp*sy;
	R[2][0]=-sr*cp;
	R[2][1]=cr*sy+cy*sp*sr;
	R[2][2]=cr*cy-sp*sr*sy;
	
	pos0_update_pos(leg);
	
	for(uint8_t i=0;i<4;i++)
	{
		for(uint8_t j=0;j<3;j++)
		{
			position[j][i]=R[j][0]*leg[i].pos0.x+R[j][1]*leg[i].pos0.y+R[j][2]*leg[i].pos0.z;
		}
		leg[i].pos0.x=position[0][i];
		leg[i].pos0.y=position[1][i];
		leg[i].pos0.z=position[2][i];
	}
	
	pos_update_pos0(leg);
}
/** 
    * @brief PID参数更新函数
*/
void PIT_ROL_PID_Set(uint8_t mode)
{
	switch(mode){
		case Trot_Mode_PAR:
			PIT_PID.P=0;
			PIT_PID.I=0;
			PIT_PID.D=0;
			PIT_PID.Iout=0;
			PIT_PID.PIDMax=0;
			PIT_PID.IMax=0;
			PIT_PID.I_Limited=0;

			ROL_PID.P=0;
			ROL_PID.I=0;
			ROL_PID.D=0;
			ROL_PID.Iout=0;
			ROL_PID.PIDMax=0;
			ROL_PID.IMax=0;
			ROL_PID.I_Limited=0;
			break;
		case Balance_Mode_PAR:
			PIT_PID.P=2;
			PIT_PID.I=0.008;
			PIT_PID.D=-8;
			PIT_PID.Iout=0;
			PIT_PID.PIDMax=45;
			PIT_PID.IMax=45;
			PIT_PID.I_Limited=45;

			ROL_PID.P=1.5;
			ROL_PID.I=0.015;
			ROL_PID.D=2;
			ROL_PID.Iout=0;
			ROL_PID.PIDMax=45;
			ROL_PID.IMax=45;
			ROL_PID.I_Limited=45;
			break;
		case Twist_Mode_PAR:
			PIT_PID.P=0;
			PIT_PID.I=0;
			PIT_PID.D=0;
			PIT_PID.Iout=0;
			PIT_PID.PIDMax=45;
			PIT_PID.IMax=45;
			PIT_PID.I_Limited=45;

			ROL_PID.P=0;
			ROL_PID.I=0;
			ROL_PID.D=0;
			ROL_PID.Iout=0;
			ROL_PID.PIDMax=45;
			ROL_PID.IMax=45;
			ROL_PID.I_Limited=45;
			break;
		default:
			break;
	}
}
/** 
    * @brief 初始化
*/
void robot_init(leg_t *leg)
{
	pwm_start_all();
	chs_INIT();
}
/** 
    * @brief 姿态执行，放在姿态计算后面
*/
void robot_run(leg_t *leg)
{
	inverse_kinematics(leg);
	pwm_calcu(leg);
	pwm_set(leg);
}
/** 
    * @brief 周期性计算PID
*/
void PID_cal()
{
	pid_run(&ROL_PID,imu.rol,&imu.wx);
	pid_run(&PIT_PID,imu.pit,&imu.wy);
}
	