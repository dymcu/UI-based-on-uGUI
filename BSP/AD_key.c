#include "AD_key.h"
/**********************************************************************
**��·���ܣ�2ͨ��ADC������1��ADCͨ���������8��������һ��8*2=16������
**(ADC1)PB0�Žӣ�----KEY_1----KEY_4----KEY_7----KEY_POINT----KEY_0----KEY_8----KEY_5----KEY_2----
**                  0.302v   0.611v   0.901v     1.19v      1.48V    1.82V    2.09V    2.4V
**(ADC2)PC5�Žӣ�----KEY_3----KEY_6----KEY_9----KEY_CLR----KEY_OK----KEY_DOWN----KEY_UP----KEY_SET----
**                  0.302v   0.611v   0.901v     1.19v      1.48V    1.82V       2.09V     2.4V
**��ע����û���κΰ������µ�ʱ��ADC����Ϊ�͵�ƽ0V
**********************************************************************/

//����������ͨ���õ�dmaֵ��ÿ��ͨ������16�Σ�ͨ��DMA��䵽��buffer�ڣ�
u32 ADC_DMAStorageValue[16][2];
//����������ͨ���ֱ�16��ֵ����ó���ƽ��ֵ
u32 ADC_AveraValue[2];
//�����ݲ�ֵ

/**********************************************************************
** ��������         :KeyConfig
** ������           :liupcngcheng
** ��������         :2017-9-2
** �����޸���       :
** ����޸�����      :
** ��������         :��ʼ������IO��Ӧ�����������
** ��ڲ���         :none
** ���ز���         :none
** ��ע/ע��        :��ʼ��/PB0/PC5/��Ϊģ�����벢����ΪADC����ģʽ
** QQ              : 1240612852
***********************************************************************/
void KeyInit()
{
	
	ADC_InitTypeDef ADC_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;

	//RCC Config
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);   //APB2=16M   ADCClk=8M

	memset(ADC_DMAStorageValue, 32, 0);
	//GPIO Config
	/**********************************************************************/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = ADC_KEY_PORT1_Pin1;     //PC5
	GPIO_Init(ADC_KEY_PORT1, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = ADC_KEY_PORT2_PIN1;     //PB0
	GPIO_Init(ADC_KEY_PORT2, &GPIO_InitStruct);


	//ADC Config
	/**********************************************************************/
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_NbrOfChannel = 2;

	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);	    //PB0	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 2, ADC_SampleTime_55Cycles5);    //PC5
	
	ADC_DMACmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1));

	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1));

	//DMA config
	/**********************************************************************/
	DMA_DeInit(DMA1_Channel1); 
	DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;					/*ADC��ַ*/ 
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)&ADC_DMAStorageValue;			/*�ڴ��ַ*/
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;							//����Ϊ����Դ 
	DMA_InitStruct.DMA_BufferSize = 32; 
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			 /*�����ַ�̶�*/ 
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;					 /*�ڴ��ַ����*/ 
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;	 //���� 
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;							 //ѭ������ 
	DMA_InitStruct.DMA_Priority = DMA_Priority_High; 
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable; 
	DMA_Init(DMA1_Channel1, &DMA_InitStruct); 
	/* Enable DMA channel1 */ 
	DMA_Cmd(DMA1_Channel1, ENABLE);

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/**********************************************************************
** ��������         :Get_ADCAveraValue
** ������           :liupcngcheng
** ��������         :2017��9��11��
** �����޸���       :liupengcheng
** ����޸�����     :2017��9��11��
** ��������         :��ADC_DMAStorageValue[2][16]���������ADCֵȡƽ��ֵ�������
** ��ڲ���         :u32* Return_ADCAvera_ValueΪָ��ȫ�ֱ���ADC_AveraValue[2]��ָ�룬���ػ�ȡ��adcƽ��ֵ
** ���ز���         :none
** ��ע/ע��        :����ָ�����Ϊ���ֵ
** QQ              : 1240612852
***********************************************************************/ 
void Get_ADCAveraValue(u32* Return_ADCAvera_Value)
{
	u8 i;
	u32 adc_sum1=0,adc_sum2=0;
	for (i = 0; i < 16; i++)
	{
		adc_sum1 += ADC_DMAStorageValue[i][0];
		adc_sum2 += ADC_DMAStorageValue[i][1];
	}
	Return_ADCAvera_Value[0] = adc_sum1 >> 4;
	
	Return_ADCAvera_Value[1] = adc_sum2 >> 4;
}


/**********************************************************************
** ��������         :GetKeyValue
** ������           :liupengcheng
** ��������         :2017/9/4 8:46
** �����޸���       :liupengcheng
** ����޸�����      :2017-9-12	
** ��������         :��ADKey_Typedef�Ľṹ���ص�ǰ����
** ��ڲ���         :none
** ���ز���         :ADKey_Typedef����ö�ٰ���
** ��ע/ע��        :��ΪAD_Key.c��ui.c�Ľӿ�
** QQ              : 1240612852
***********************************************************************/
ADKey_Typedef GetKeyValue(void)
{
	Get_ADCAveraValue(ADC_AveraValue);

	if (ADC_AveraValue[0] > (KEY_AD_GND + AD_KEY_TELORATE_VALUE))
	{
		//ADC��һ��ͨ���µİ���
		if (ADC_AveraValue[0] > (KEY_AD1_1 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[0] < (KEY_AD1_1 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD1_1;
		}
		else if (ADC_AveraValue[0] > (KEY_AD1_2 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[0] < (KEY_AD1_2 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD1_2;
		}
		else if (ADC_AveraValue[0] > (KEY_AD1_3 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[0] < (KEY_AD1_3 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD1_3;
		}
		else if (ADC_AveraValue[0] > (KEY_AD1_4 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[0] < (KEY_AD1_4 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD1_4;
		}
		else if (ADC_AveraValue[0] > (KEY_AD1_5 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[0] < (KEY_AD1_5 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD1_5;
		}
		else if (ADC_AveraValue[0] > (KEY_AD1_6 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[0] < (KEY_AD1_6 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD1_6;
		}
		else if (ADC_AveraValue[0] > (KEY_AD1_7 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[0] < (KEY_AD1_7 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD1_7;
		}
		else if (ADC_AveraValue[0] > (KEY_AD1_8 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[0] < (KEY_AD1_8 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD1_8;
		}
	}
	else if (ADC_AveraValue[1] > (KEY_AD_GND + AD_KEY_TELORATE_VALUE))
	{
		//ADC�ڶ���ͨ���µİ���
		if (ADC_AveraValue[1] > (KEY_AD2_1 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[1] < (KEY_AD2_1 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD2_1;
		}
		else if (ADC_AveraValue[1] > (KEY_AD2_2 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[1] < (KEY_AD2_2 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD2_2;
		}
		else if (ADC_AveraValue[1] > (KEY_AD2_3 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[1] < (KEY_AD2_3 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD2_3;
		}
		else if (ADC_AveraValue[1] > (KEY_AD2_4 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[1] < (KEY_AD2_4 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD2_4;
		}
		else if (ADC_AveraValue[1] > (KEY_AD2_5 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[1] < (KEY_AD2_5 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD2_5;
		}
		else if (ADC_AveraValue[1] > (KEY_AD2_6 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[1] < (KEY_AD2_6 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD2_6;
		}
		else if (ADC_AveraValue[1] > (KEY_AD2_7 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[1] < (KEY_AD2_7 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD2_7;
		}
		else if (ADC_AveraValue[1] > (KEY_AD2_8 - AD_KEY_TELORATE_VALUE) && ADC_AveraValue[1] < (KEY_AD2_8 + AD_KEY_TELORATE_VALUE))
		{
			return KEY_AD2_8;
		}
	}
	else if (ADC_AveraValue[0] < (KEY_AD_GND + AD_KEY_TELORATE_VALUE) && ADC_AveraValue[1] < (KEY_AD_GND + AD_KEY_TELORATE_VALUE))
	{
		return KEY_AD_GND;
	}
    return KEY_AD_GND;

	
}




