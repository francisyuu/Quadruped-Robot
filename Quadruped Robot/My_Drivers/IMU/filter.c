/**
*
**/
#include "filter.h"


/**
* @Brief：kalman滤波
* @Param: 属于递归更新滤波算法，是估计均方误差最小化，主要处理随机误差
*此函数一次只能为一个数据滤波，即观察矩阵H=1，A=1
*由于系统不能控，则B=0
*卡尔曼滤波基本公式(预估(时间更新)和校正(测量更新))：
1、状态预测方程：  X(k|k-1) = A*X(k-1|k-1)+B*U(k)    //k时刻系统预测值=A*(k-1时刻系统状态变量的最优值)+B*系统输入
2、协方差预测方程：P(k|k-1)=A*P(k-1|k-1)A的转置+Q    //k时刻系统协方差矩阵预测值P(k|k-1)、k-1时刻系统协方差矩阵P(k-1|k-1)
3、卡尔曼增益计算方程：K(k)=P(k|k-1)H的转置/[H*P(k|k-1)*H的转置+R]
4、最优值更新方程： X(k|k)=X(k|k-1)+K(k)*(Z(k)-H*X(k|k-1))   //k时刻状态变量最优值X(k|k)、系统输出方程Z(k)
5、协方差更新方程： P(k|k)=(1-K(k)*H)*P(k|k-1)
6、系数Q越小，滤除噪声能力越强；系数R越小，滤波响应和收敛越迅速。
 **/
float Kalman(kalman_filter* kalman,float input)
{
    if(kalman->flag== 0)
    {
       kalman->P_last = 1.0f; 
       kalman->Q = 0.00001; //0.0001
       kalman->R = 1;   //4.57
       kalman->flag = 1;
    }
    kalman->input = input;
	/*量测更新，3组方程*/
	kalman->K = (kalman->P_last)/(kalman->P_last + kalman->R);
	kalman->X  = kalman->X_last + kalman->K * (kalman->input - kalman->X_last);
	kalman->P =  (1-kalman->K)*(kalman->P_last);
	/*时间更新，2组方程*/
	kalman->X_last = kalman->X;										
	kalman->P_last = kalman->P + kalman->Q;			
	
	return kalman->X;
}

void KalmanInit(kalman_filter* kalman,float Q,float R)
{
       kalman->P_last = 1.0f; 
       kalman->Q = Q;
       kalman->R = R;
       kalman->flag = 1;
}
/**
  * @brief   IIR滤波器（无限冲击响应滤波器）：Butterworth IIR Lowpass
  * @details 设计为低通IIR滤波器
  * @par     技术指标：中心频率f0,采样频率fs,增益dB,品质因数   
  *低通滤波中心频率=截止频率
  *角频率omega=2π*f0/sampleRate
  *记sin=sin(omega),cos=cos(omega),alpha=sin/(2*Q)
  *则二阶IIR低通滤波器的系数为：b0=(1-cos)/2, b1=1-cos, b2=(1-cos)/2, a0=1+alpha, a1=-2cos, a2=1-alpha;
  *利用matlab工具fdatool，当截止频率30Hz，输出频率800Hz,生成b0=1, b1=2, b2=1, a0=1, a1=-1.6692031429311931, a2=0.71663387350415764, Scale Values:0.011857682643241156
	*1KHz采样频率，20Hz截止频率  1,2,1,1，-1.8226949251963083,0.83718165125602262，0.0036216815149286421
  **/  
float IIR_LPF(IIR* IIR,float input)
{
	IIR->current_input = input;
  IIR->current_output = IIR->b0*IIR->current_input+IIR->b1*IIR->last_input+IIR->b2*IIR->pre_input-(IIR->a1*IIR->last_output+IIR->a2*IIR->pre_output);
	IIR->pre_input = IIR->last_input;
	IIR->last_input = IIR->current_input;
	IIR->pre_output = IIR->last_output;
	IIR->last_output = IIR->current_output;	
	return IIR->G*IIR->current_output;
}

/** 
* @brief    二阶低通滤波器
* @remarks 
* @par 日志
*/
void LPF2pSetCutoffFreq(LPF2* LPF,float sample_freq, float cutoff_freq)
{
		float fr =0;  
    float ohm =0;
    float c =0;
	
		fr= sample_freq/cutoff_freq;
		ohm=tanf(PI/fr);
		c=1.0f+2.0f*cosf(PI/4.0f)*ohm + ohm*ohm;
	
    LPF->_cutoff_freq = cutoff_freq;
    if (LPF->_cutoff_freq > 0.0f) 
		{
				LPF->_b0 = ohm*ohm/c;
				LPF->_b1 = 2.0f*LPF->_b0;
				LPF->_b2 = LPF->_b0;
				LPF->_a1 = 2.0f*(ohm*ohm-1.0f)/c;
				LPF->_a2 = (1.0f-2.0f*cosf(PI/4.0f)*ohm+ohm*ohm)/c;
		}
}

float LPF2pApply(LPF2* LPF,float sample)
{
		float delay_element_0 = 0, output=0;	
    if (LPF->_cutoff_freq <= 0.0f) {
        // no filtering
        return sample;
    }
		else
		{
				delay_element_0 = sample - LPF->_delay_element_1 * LPF->_a1 - LPF->_delay_element_2 * LPF->_a2;
				// do the filtering
				if (isnan(delay_element_0) || isinf(delay_element_0)) 
						// don't allow bad values to propogate via the filter
						delay_element_0 = sample;

				output = delay_element_0 * LPF->_b0 + LPF->_delay_element_1 * LPF->_b1 + LPF->_delay_element_2 * LPF->_b2;
				
				LPF->_delay_element_2 = LPF->_delay_element_1;
				LPF->_delay_element_1 = delay_element_0;

				// return the value.  Should be no need to check limits
				return output;
		}
}

