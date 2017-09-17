#include "SPI_lcd.h"

/**********************************************************************
**LCDӲ��������LCDΪspi�ӿڣ����Ŷ���������ʾ
**LCD_BL		GPIOE, GPIO_Pin_5	 // 0���رգ�1����
**LCD_RS		GPIOB, GPIO_Pin_12	 // 1�����ݣ�0������
**LCD_CS		GPIOB, GPIO_Pin_14   // LCD����ѡ�񣬵͵�ƽʹ��
**LCD_RST		GPIOB, GPIO_Pin_5    // LCD��λ��	�͵�ƽ��λ
**LCD_MOSI      GPIOB, GPIO_Pin_15    
**LCD_SCLK      GPIOB, GPIO_Pin_13
**LCD����Ϊ64���У�*132���У�
**
**
**�Դ�Ϊ132*8�ֽڣ�
**********************************************************************/
u8 g_Display_Buffer[8][132] = {0x00};
/**********************************************************************
**0��--------------------------------------------------------------132��
**0000000000000000000000000000000000000000000000000000000000000000000000
**xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
**1010101010101010101010101010101010101010101010101010101010101010101010
**0101010101010101010101010101010101010101010101010101010101010101010101
**
**
**
**
**********************************************************************/

void Delay(unsigned int tDly)
{
	while (tDly > 0)
	{
		tDly--;
	}
}



/**********************************************************************
**��������   ��   SdCmd
**������     ��   guoyu
**��������   ��   2013/05/28
**��������   ��   ����д�뺯��
**��ڲ���   ��   None
**���ز���   ��   None
**��ע/ע��  ��   None
**********************************************************************/
void SdCmd(uint8_t Command)
{
	GPIO_ResetBits(LCD_RS_PORT,LCD_RS_PIN);
	GPIO_ResetBits(LCD_CS_PORT,LCD_CS_PIN);
	Delay(1);

	SPI_I2S_SendData(SPI2, (uint16_t)Command);

	Delay(5);
	GPIO_SetBits(LCD_CS_PORT,LCD_CS_PIN);
}

/**********************************************************************
**��������   ��   SdData
**������     ��   guoyu
**��������   ��   2013/05/28
**��������   ��   ��ʾ����д�뺯��
**��ڲ���   ��   None
**���ز���   ��   None
**��ע/ע��  ��   None
**********************************************************************/
void SdData(uint8_t DData)
{
	GPIO_SetBits(LCD_RS_PORT, LCD_RS_PIN);
	GPIO_ResetBits(LCD_CS_PORT, LCD_CS_PIN);
	Delay(1);

	SPI_I2S_SendData(SPI2, (uint16_t)DData);

	Delay(5);
	GPIO_SetBits(LCD_CS_PORT, LCD_CS_PIN);
}

void initLCDM(void)
{
	SdCmd(0xaf); // ����ʾ
	SdCmd(0x40); // ������ʾ��ʼ��=0
	SdCmd(0xa0); // RAM�е�ַ��������ͬ˳��
				 //SdCmd(0xa1);                                      // RAM�е�ַ����������˳��  LM6063C
	SdCmd(0xa6); // ������ʾ
	SdCmd(0xa4); // ��ʾȫ�����ܹر�
	SdCmd(0xa2); // LCDƫѹ��Ϊ1/9
				 //SdCmd(0xc0);                                      // ����������Ϊ���� LM6063C
	SdCmd(0xc8); // ����������Ϊ����
	SdCmd(0x2f); // �����ڲ�LCD������Դ
	SdCmd(0x25); // �����
	SdCmd(0xf8);
	SdCmd(0x00); // ��ѹ����Ϊ4X
				 //SdCmd(0xf8);
				 //SdCmd(0x01);                                             // ��ѹ����Ϊ5X     LM6060C
	SdCmd(0x81);
	SdCmd(DEFAULT_CONTRAS); // ���öԱȶ�
}

/**********************************************************************
**��������   :   ClearRAM
**������     :   guoyu
**��������   :   2013/05/28
**��������   :   ��������
**��ڲ���   :   None
**���ز���   :   None
**��ע/ע��  :   None
**********************************************************************/
void ClearRAM(void)
{
	unsigned char i, j;

	for (i = 0; i < 8; i++) // ѭ��д8ҳ
	{
		SdCmd(i | 0xb0);		  // ҳ��ַ����
		SdCmd(0x10);			  // �е�ַ��4λ
		SdCmd(0x00);			  // �е�ַ��4λ
		for (j = 0; j < 132; j++) // ѭ��д132��Ԫ
		{
			SdData(0x00);			  // ��������Ϊ0
		}
	}
}



/**********************************************************************
**��������   ��   Lcd_Init
**������     ��   guoyu
**��������   ��   2013/05/28
**��������   ��   Lcdģ���ʼ��������Ӳ��SPI
**��ڲ���   ��   None
**���ز���   ��   None
**��ע/ע��  ��   None
**********************************************************************/
void LcdInit(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_SetBits(LCD_RST_PORT,LCD_RST_PIN);
	GPIO_ResetBits(LCD_RST_PORT, LCD_RST_PIN);

	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;         //SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;        //SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;  // SPI_FirstBit_LSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;		    //CRCPolynomial;
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);

	GPIO_SetBits(LCD_RST_PORT, LCD_RST_PIN);
	GPIO_SetBits(LCD_CS_PORT,LCD_CS_PIN);

	initLCDM();
	ClearRAM();
}

/**********************************************************************
** ��������         :FLUSHScreenRAM
** ������           :liupcngcheng
** ��������         :2017-9-8
** �����޸���       :liupengcheng
** ����޸�����      :2017-9-8
** ��������         : ���Դ��ϵ��������͵�LCD����ʾ
** ��ڲ���         : none
** ���ز���         : none
** ��ע/ע��        : ���ж�
** QQ              : 1240612852
***********************************************************************/
void UPDATE_ScreenRAM()
{
	unsigned char i, j;

	for (i = 0; i < 8; i++) // ѭ��д8ҳ
	{
		SdCmd(i | 0xb0);		  // ҳ��ַ����
		SdCmd(0x10);			  // �е�ַ��4λ
		SdCmd(0x00);			  // �е�ַ��4λ
		for (j = 0; j < 132; j++) // ѭ��д132��Ԫ
		{
			SdData(g_Display_Buffer[i][j]);			  
		}
	}
}

/**********************************************************************
** ��������         :LCDDrawDot
** ������           :liupcngcheng
** ��������         :2017-9-8
** �����޸���       :liupengcheng
** ����޸�����     :2017-9-8
** ��������         :��132���У�*64���У���LCD��ֵ��������
** ��ڲ���         :
						--x��X�����꣬ԭ��Ϊ0
						--y��y�����꣬ԭ��Ϊ0
						--color����ɫ  ��0xffffffffΪ��ɫ
** ���ز���         :none
** ��ע/ע��        :��Ϊ�ӿ��ν�uguiͼ���
** QQ              : 1240612852
***********************************************************************/ 
void LCDDrawDot(s16 x, s16 y, u32 color)
{
	u8 row_byte,row_bit;
	row_byte = y / 8;
	row_bit = y % 8;
	if (color == 0x00FFFFFF)   //��ɫ
	{
		g_Display_Buffer[row_byte][x] &= (~(0x01 << row_bit));
	}
	else if(color == 0x00000000)                       //��ɫ
	{
		g_Display_Buffer[row_byte][x] |= (0x01 << row_bit);
	}
}

