#ifndef _UI_H
#define _UI_H
/****************************1��ͷ�ļ�******************************************/
#include "stddef.h"
#include "AD_key.h"
#include "SPI_lcd.h"
#include "ugui.h"
#include "stdio.h"


/****************************2���궨��******************************************/
#define KEY_SUM 16       //�豸������--16
#define NUM_KEY_SUM 11   //���ְ�������--����С���㰴��
/**********************************************************************
**��11�����ְ����Ĵ����װ��PROCESS_ShortNumKey_Of_Page1������
**��ǰ�����16-11=5�ఴ�����������������£�ʵ����ui.c��
**1���ϼ������� 2���¼������� 3��OK�������� 4��CLR�������� 5�����ּ�������������С�������
**********************************************************************/
#define PROCESS_KEY_FUNCTION_SUM   KEY_SUM-NUM_KEY_SUM+1           

#define PAGE_SUM 19    //�豸������--19
#define LONG_KEY_JUDGE_TIMES  50        //�������жϴ���----����5��ɨ�赽ͬһ������������Ϊ������
//////��LCDUpdateMain��KeyScanMain֮������ͨ��ʹ��
#define LcdUpdateMain_ID      0x99     //LCDUpdateMainģ��ID�� 
#define KeyScanMain_ID		  0x88	   //KeyScanMainģ��ID��		


/******************************3�����Ͷ���****************************************/
//��ǰ����ö��
//��ע��������ö�����͵�˳����Բ����޸ģ�˳��Ӱ�찴����Ӧ������ָ������
typedef enum
{
	KEY_NONE=0,        //-//
	KEY_SET=1,		   //��	 			
	KEY_OK=2,            //��
	KEY_CLR=3,           //��
	KEY_UP=4,            //��
	KEY_DOWN=5,          //-// 



	KEY_0=6,			   //-//	 
	KEY_1=7,			   // 	
	KEY_2=8,			   //
	KEY_3=9,			   //��
	KEY_4=10,			   //��
	KEY_5=11,			   //��
	KEY_6=12,			   //��
	KEY_7=13,             //
	KEY_8=14,             //
	KEY_9=15,             //
	KEY_POINT,         //-//
}AbstractKey_Typedef;


//��ǰ����ö��
//������ö�����͵�˳����Բ����޸ģ�˳��Ӱ�찴����Ӧ������ָ������
typedef enum
{
	PageInit=0,					// �ϵ��ʼ��ҳ��
	PageDefault,				// Ĭ����ʾҳ��
	PageRGZS,					// �˹�����ҳ��
	PageCodeEnt,				// ��������ҳ��
	PageCodeChange,				// �����޸�ҳ��
	PageMainMenu,				// ���˵�ҳ��
	PageDTUSet,
	PageSensorMotherConfig,		// ������ĸ�˵�ҳ��
	PageSensorSonPara,			// �������Ӳ˵�1ҳ��
	PageTestSend,				// ���Ͳ��Ա���ҳ��
	PageParaBak,				// �ָ�����Ĭ��ҳ��
	PageDateTimeSet,			// ���ں�ʱ������
		
	PageDTUServerSet,			// DTU�ƶ������������
	PageDTURunModeSet,			// DTU���в�������
	PageDTUSMSSet,				// DTU SMS���Ų�������
	PageDTUChan1Set,			// DTUͨ��1����
	PageDTUChan2Set,			// DTUͨ��2����
	PageDTUChan3Set,			// DTUͨ��3����
	PageDTUChan4Set,		    // DTUͨ��4����
}
CurrentPageTypedef;

//��ǰ����ö��
typedef enum
{
	COLUME1=0,
	COLUME2,
	COLUME3,
	COLUME4,
	COLUME5,
	COLUME6,
	COLUME7,
	COLUME8,
	COLUME9,
	COLUME10,
}
CurrentColumeTypedef;


typedef struct 
{
	u8 SenderID;       //�ļ�ģ��ID
	u8 RecieverID;     //�ռ�ģ��ID 
	u8 data;           //�ļ�����
}
KeyValueBox_Typedef;

/******************************4����������****************************************/




/*******************************5����������***************************************/
void BoxConfig(void);
void LcdUpdateMain(void);
void KeyScanMain(void);

#endif






