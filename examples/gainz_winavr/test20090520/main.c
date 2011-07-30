//----------------------------------------------------//
//-------Institute Of  Computing Technology-----------//
//------------Chinese Academic  Science---------------//
//-----�й���ѧԺ���㼼���о����Ƚ����Լ���ʵ����-----//
//----------------------------------------------------//

/**
 * www.wsn.net.cn
 * @copyright:nbicc_lpp
 * @data:2005.11.22
 * @version:0.0.1
 * @updata:$
 *
 */


 /********************************************************************
* �� �� ����main.c
* �� �ܣ� ���շ���IEEE 802.15.4��׼��֡
* ˵ ���� ��
********************************************************************/

#include "top.h"
#include "generic.h"


/*
demo_datapacket * demopacket;
uint8_t demo_ieee_address[8];
uint16_t address;
uint16_t shortaddress;
*/

/********************************************************************
* �� �ƣ�receive_packet ()
* �� �ܣ������յ���֡��RXFIFO�ж�ȡ������������
			������洢���յ���֡
* ��ڲ�������
* ���ڲ�������	
********************************************************************/
/*
void  receive_packet(void)
{
  uint8_t status;
  uint8_t i;
  uint8_t flag;
	
 // printf("***��ʼһ����fifo����***\n");
  { hal_atomic_t _nesc_atomic = hal_atomic_start();
    {
      cc2420fifo_bspi = FALSE;
      HAL_CLR_CC_CS_PIN();
	  //void	HAL_CLR_##name##_PIN()		{PORT##port &= (~(1<<(bit)));}
	  //HAL_ASSIGN_PIN(CC_CS, B, 0);	  // chipcon enable
	  //=>HAL_CLR_CC_CS_PIN()	==	PORT B &= (~(1<<(bit)))	==	PORT B &= 11111110
      SPDR = 0x3F | 0x40;
	  //#define	SPDR	_SFR_IO8(0x0F)
	  //SPI���ݼĴ���Ϊ��/д�Ĵ����������ڼĴ����ļ���SPI��λ�Ĵ���֮�䴫�����ݡ�
	  //д�Ĵ������������ݴ��䣬���Ĵ�������ȡ�Ĵ����Ľ��ջ�������
	  //00111111 | 01000000 = 01111111
	  //
      while (!(SPSR & 0x80));
	  //0x80=10000000	
	  //Bit 7 �C SPIF: SPI �жϱ�־=>�����ж����̺�SPIF �Զ����㡣���߿���ͨ���ȶ�SPSR�������ŷ���SPDR ����SPIF ���㡣
      status = SPDR;
      SPDR = 0;
      while (!(SPSR & 0x80));
      cc2420_rxlength = SPDR;//���ȶ�ȡ��֡�ĳ���
      cc2420_rxbuf[cc2420_rxflag] =malloc(cc2420_rxlength +1);//�����ڴ�ռ�
     // printf("the length of the receive pack is %x\n",cc2420_rxlength);  
	  
      if (cc2420_rxlength > 0) 
	{
            cc2420_rxbuf[cc2420_rxflag] [0] = cc2420_rxlength ;//�洢֡�����ֽ�
            cc2420_rxlength ++;
  
            for (i = 1; i < cc2420_rxlength ; i++)
	     {
                SPDR = 0;
                while (!(SPSR & 0x80));
                cc2420_rxbuf[cc2420_rxflag] [i] = SPDR;//����MAC֡
		  usart_putbyte(cc2420_rxbuf[cc2420_rxflag] [i]);//��MAC֡���������
            }
        }

      cc2420fifo_bspi = TRUE;
      rfpackernum--;
      cc2420_rxflag++;  
      cc2420_rxflag&=0x01; 
    }
    hal_atomic_end(_nesc_atomic); }
  HAL_SET_CC_CS_PIN();
  
  flag=(cc2420_rxflag+cc2420_rxbufuse)&0x01;
  cc2420_rxbuf_now=cc2420_rxbuf[flag];
		
  free(cc2420_rxbuf[flag]);//�ͷſռ�
  cc2420_rxbufuse--;
	
	if  ((cc2420_rxbufuse==0) && (rfpackernum!=0))
		{
		   cc2420_rxbufuse++;
		}
	
	cc2420_rxbuf[flag]=NULL;
}
*/

/********************************************************************
* �� �ƣ�main ()
* �� �ܣ� ��ʼ���ڵ㣬ʹ�ܵ�ַ����ģʽ����ʼ����
* ��ڲ�������
* ���ڲ�������	
********************************************************************/

/***************************main_original***************************
void  main(void)
{
  HAL_SET_PIN_DIRECTIONS();
  Leds_greenOn();
  Leds_redOn();
  Leds_yellowOn();
  IoInit();
  
  HAL_sched_init();
  cc2420_init();
  hal_atomic_enable_interrupt();
  address=my_short_address;
  
  cc2420_setchnl(11);
  
  cc2420_setrxmode();				//Enable RX
  cc2420_enableAddrDecode();		//ʹ�ܵ�ַ����
  cc2420_setpanid(0x0001);			//�����ʶ
  cc2420_setshortaddress(address);	//���ڱ�ʶ
  cc2420_enablefifop();				//����fifop�ж�
  while(1) 
  {
  	HAL_sleep();
  }

}
********************************************************************/

/****************************main2*****************************/
void main(void)
{
  HAL_SET_PIN_DIRECTIONS();
  Leds_greenOn();
  Leds_redOn();
  Leds_yellowOn();
  IoInit();
  
  //HAL_sched_init();
  cc2420_init();
  hal_atomic_enable_interrupt();
  //address=my_short_address;
  
  cc2420_setchnl(11);
  
  cc2420_setrxmode();				//Enable RX
  cc2420_enableAddrDecode();		//ʹ�ܵ�ַ����
  //cc2420_setpanid(0x0001);			//�����ʶ
  //cc2420_setshortaddress(address);	//���ڱ�ʶ
  cc2420_enablefifop();				//����fifop�ж�
  
  uint8_t buf[127];
  uint16_t source_addr;
  uint8_t len;
  
  while(1) 
  {
  	//HAL_sleep();
	len = cc2420_receiveframe( &buf );
	if (len > 30)
	{
	  change(buf[3],buf[7]);
	  change(buf[4],buf[8]);
	  change(buf[5],buf[9]);
	  change(buf[6],buf[10]);
	  //source_addr = ((uint16_t)buf[10] << 8) | (uint16_t)buf[11];
	  
	  //buf[29] = 56;// read data from sensor
	  //buf[7] = destination;
	  cc2420_sendframe( &buf, len );
	}
  }
}

/********************************************************************/

//gateway
/*********************************************************************
void  main(void)
{
  HAL_SET_PIN_DIRECTIONS();
  Leds_greenOn();
  Leds_redOn();
  Leds_yellowOn();
  IoInit();
  
  //HAL_sched_init();
  cc2420_init();
  hal_atomic_enable_interrupt();
  //address=my_short_address;
  
  cc2420_setchnl(11);
  
  cc2420_setrxmode();				//Enable RX
  cc2420_enableAddrDecode();		//ʹ�ܵ�ַ����
  //cc2420_setpanid(0x0001);			//�����ʶ
  //cc2420_setshortaddress(address);	//���ڱ�ʶ
  cc2420_enablefifop();				//����fifop�ж�
  
  char buf[127];
  //uint16 source_addr;
  
  while(1) 
  {
  	//HAL_sleep();
	uint8_t j;
	uint8_t packet[127];
	packet[0]=0x88;
	packet[1]=0x41;
	packet[2]=0x01;
	packet[3]=0x00;
	packet[4]=0x01;
	packet[5]=0x00;
	packet[6]=0x01;
	packet[7]=0x00;
	packet[8]=0x01;
	packet[9]=0x00;
	packet[10]=0x01;
	for(j=11;j<128;j++)
	{
		packet[j]=0x00;
	}
	cc2420_sendframe(uint8_t len, uint8_t *packet);
	/*
	len = cc2420_receiveframe(uint8_t *msg);
	if (len > 0)
	{
	   //uart_write( g_uart0, &buf, len );
	}
	/*
	len = uart_read( g_uart0, &buf, 127 );
	if len > 0
	{
	   if buf[0] == 0
	     cc2420_write( &buf, len );
	   else
	     execute( &buf, len );
	}
}
*******************************************************************/