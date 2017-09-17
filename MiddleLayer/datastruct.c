#include "datastruct.h"

//main.c��ʹ��
/********************************************************************************************************************************************************************/
UG_GUI GUI_Struct;


//AD_Key.c��ui.c֮��Ľӿڱ�
/********************************************************************************************************************************************************************/
/**********************************************************************
**AD_Keyģ��--����ΪADKey_Typedef
**uiģ��--����ΪAbstractKey_Typedef 
**�ñ�Ϊuiģ����ADKeyģ�鰴����ֵ�Ľӿ�
**********************************************************************/
KeyValueTable_Typedef KeyValueTable_Struct[] =
{
	{ KEY_NONE, KEY_AD_GND},    
	{ KEY_SET,  KEY_AD2_8},    
	{ KEY_OK,   KEY_AD2_5},	   
	{ KEY_CLR,  KEY_AD2_4},	   
	{ KEY_UP,   KEY_AD2_7},	   
	{ KEY_DOWN, KEY_AD2_6},	   
	{ KEY_0,    KEY_AD1_5},	   
	{ KEY_1,    KEY_AD1_1},	   
	{ KEY_2,    KEY_AD1_8},	   
	{ KEY_3,    KEY_AD2_1},	   
	{ KEY_4,    KEY_AD1_2},	   
	{ KEY_5,    KEY_AD1_7},	   
	{ KEY_6,    KEY_AD2_2},	   
	{ KEY_7,    KEY_AD1_3},	   
	{ KEY_8,    KEY_AD1_6},	   
	{ KEY_9,    KEY_AD2_3},	   
	{ KEY_POINT,KEY_AD1_4},	   
};


/**********************************************************************
** ��������         :ADKey_2_AdstractKey   
** ������           :liupengcheng
** ��������         :2017/9/12 16:51
** �����޸���       :liupengcheng
** ����޸�����      :2017/9/12 16:51
** ��������         :ͨ�����ķ�ʽ���BSP��ADCKey��ӦӦ�ò�AbstractKey
** ��ڲ���         :
					--ADKey_Value:AD������ֵ
** ���ز���         :
					--AbstractKey_Value
** ��ע/ע��        :�ú������ν�ADKey.c��UI.c��ֵ�Ľӿ�
** QQ              : 1240612852
***********************************************************************/
AbstractKey_Typedef ADKey_2_AdstractKey(ADKey_Typedef ADKey_Value)
{
	u8 i;
	for (i = 0; i < KEY_SUM; i++)
	{
		if (KeyValueTable_Struct[i].AD_Key_Enum == ADKey_Value)
		{
			return KeyValueTable_Struct[i].Abstracrt_Key_Enum;
		}
	}
	return KEY_NONE;
}

