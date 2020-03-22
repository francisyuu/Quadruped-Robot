#ifndef _FILTER_H
#define _FILTER_H

#include "stm32f4xx_hal.h"

#include <math.h>
#define 	PI 		3.1415926535f

typedef struct  //< butterworth lowpass filter 
{
    float b0;
    float b1;
    float b2;
    float a1;
    float a2;
    float G;   //输出增益
    
    float current_input;		     
    float last_input;			       
    float pre_input;
    
    float current_output;		            //y[n]
    float last_output;			            //y[n-1]
    float pre_output;	                  //y[n-2]
}IIR;

typedef struct 
{
    float P_last;				/*上次预测过程协方差矩阵P(k|k-1)*/
    float X_last;				/*系统状态预测矩阵X(k|k-1)，列矩阵*/
    
    float Q;						/*过程白噪声协方差系数*/
    float R;						/*观测白噪声协方差系数*/
    
    float K;						/*卡尔曼增益K(k)，列矩阵*/
    float X;						/*最优估计状态变量矩阵X(k|k)，列矩阵*/
    float P;						/*最优估计协方差矩阵P(k|k)*/
                                                        
    float input;				    /*系统输出值，即Z(k)*/
    uint8_t flag;
}kalman_filter;	

typedef struct 
{
	float _cutoff_freq;
	float _a1;
	float _a2;
	float _b0;
	float _b1;
	float _b2;
	float _delay_element_1;        // buffered sample -1
	float _delay_element_2;        // buffered sample -2	
}LPF2;

void LPF2pSetCutoffFreq(LPF2* LPF,float sample_freq, float cutoff_freq);
float LPF2pApply(LPF2* LPF,float sample);


float Kalman(kalman_filter* kalman,float input);
void KalmanInit(kalman_filter* kalman,float Q,float R);
#endif

