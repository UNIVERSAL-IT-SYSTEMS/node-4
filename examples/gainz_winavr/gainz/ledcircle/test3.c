/**************************************************
�ļ���: test3.c
���ܣ�ʹ�ö�ʱ��0ʵ�ֶ�ʱ0.5��������ʵ��
˵����ʱ�ӣ�7.3728MHz
***************************************************/

#include <avr/io.h>

#define SET_YEL_LED PORTA&=~_BV(PA0)//PA0������͵�ƽ���Ƶ���
#define CLR_YEL_LED PORTA|=_BV(PA0)//PA0������ߵ�ƽ���Ƶ���

#define SET_GEN_LED PORTA&=~_BV(PA1)//PA1������͵�ƽ���̵���
#define CLR_GEN_LED PORTA|=_BV(PA1)//PA1������ߵ�ƽ���̵���

#define SET_RED_LED PORTA&=~_BV(PA2)//PA2������͵�ƽ�������
#define CLR_RED_LED PORTA|=_BV(PA2)//PA2������ߵ�ƽ�������

#define uchar unsigned char 

void Delay(void);
void FlashLedYel(void);
void FlashLedRed(void);
void FlashLedGen(void);

/***************************************************
*���ƣ�main()
*���ܣ�����Ƴ�����������������˸
*��ڲ�������
*���ڲ�������
*****************************************************/
int main( void )
{
	PORTA=_BV(PA0)|_BV(PA1)|_BV(PA2);        
	DDRA=_BV(PA0)|_BV(PA1)|_BV(PA2);   //����PA0,PA1,PA2Ϊ�����
	while(1)
	{
		FlashLedRed();
		FlashLedYel();
		FlashLedGen();
	};

}

/***************************************************
*���ƣ�Delay()
*���ܣ���ʼ��I/O����ʱ��0,��ʱʱ��Ϊ0.5s
*��ڲ�������
*���ڲ�������
*****************************************************/
void Delay()
{
	uchar i=0;
	TCNT0=0; // T/C0 ��ʼֵ
	TCCR0=_BV(CS02); // Ԥ��Ƶ ck/64 ,��������
 
	//��ѯ��ʱ����ʽ�ȴ�0.5��
	//7372800 /64 /256 /225 = 2Hz
	for(i=0;i<225;i++)
	{
		loop_until_bit_is_set(TIFR,TOV0);
		//д���߼�1 ����TOV0 λ
		TIFR|=_BV(TOV0);
	}
}

/***************************************************
*���ƣ� FlashLedYel()
*���ܣ����ƻƵ���˸
*��ڲ�������
*���ڲ�������
*****************************************************/
void FlashLedYel(void)
{
	SET_YEL_LED;
	Delay();
	CLR_YEL_LED;
	Delay();
}

/***************************************************
*���ƣ� FlashLedRed()
*���ܣ����ƺ����˸
*��ڲ�������
*���ڲ�������
*****************************************************/
void FlashLedRed(void)
{
	SET_RED_LED;
	Delay();
	CLR_RED_LED;
	Delay();
}

/***************************************************
*���ƣ� FlashLedGen()
*���ܣ������̵���˸
*��ڲ�������
*���ڲ�������
*****************************************************/
void FlashLedGen(void)
{
	SET_GEN_LED;
	Delay();
	CLR_GEN_LED;
	Delay();
}
