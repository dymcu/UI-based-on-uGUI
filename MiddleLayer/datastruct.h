#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
/**********************************1��ͷ�ļ�************************************/
#include "AD_Key.h"
#include "ui.h"
#include "ugui.h"

/**********************************2���궨��***********************************/
#define KEY_SUM   16             //��������=16

/**********************************3�����Ͷ���***********************************/
////AD_Key.c��ui.c֮��Ľӿڱ�ṹ������
typedef struct
{
	AbstractKey_Typedef Abstracrt_Key_Enum;
	ADKey_Typedef		AD_Key_Enum;
}KeyValueTable_Typedef;


/**********************************4����������**********************************/
extern UG_GUI GUI_Struct;
extern KeyValueTable_Typedef KeyValueTable_Struct[];
/**********************************5����������*********************************/
AbstractKey_Typedef ADKey_2_AdstractKey(ADKey_Typedef ADKey_Value);


#endif





