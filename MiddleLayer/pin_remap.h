#ifndef _PIN_REMAP_H
#define _PIN_REMAP_H

//���÷�Χ��AD_key.c
////////*********************************************************/ 
//������ԭ����ADC����������ʹ��������ADC���������룬
//ÿ��ADC�����������8��������һ��16������
//һ����PC5 ,һ����PB0
#define ADC_KEY_PORT1		 GPIOC               
#define ADC_KEY_PORT1_Pin1   GPIO_Pin_5

#define ADC_KEY_PORT2		  GPIOB
#define ADC_KEY_PORT2_PIN1    GPIO_Pin_0
/*******************************************************//////////

//���÷�Χ
////////////*******************************************************/
// 0�������⣬1���ر���
#define LCD_BL_PORT		GPIOE 	 
#define LCD_BL_PIN		GPIO_Pin_5   
// 1�����ݣ�0������
#define LCD_RS_PORT		GPIOB 	 
#define LCD_RS_PIN		GPIO_Pin_12   
// LCD����ѡ�񣬵͵�ƽʹ��
#define LCD_CS_PORT		GPIOB    
#define LCD_CS_PIN      GPIO_Pin_14    
// LCD��λ�� �͵�ƽ��λ 
#define LCD_RST_PORT	GPIOB    
#define LCD_RST_PIN    GPIO_Pin_5     
/*********************************************************///////////


#endif





