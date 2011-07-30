/********************************************************************
* �� �� ����main.c
* �� �ܣ� ����IEEE 802.15.4��׼���֡�����ͳ�ȥ
* ˵ ���� ��
********************************************************************/
#include "top.h"

uint8_t demo_ieee_address[8];
uint16_t shortaddress;
demo_datapacket * demopacket;//����μ�project.h

/********************************************************************
* �� �ƣ�main ()
* �� �ܣ���ʼ��ϵͳ���������
* ��ڲ�������
* ���ڲ�������	
********************************************************************/

int  main(void)
{
HAL_SET_PIN_DIRECTIONS();
  Leds_greenOn();
  Leds_redOn();
  Leds_yellowOn();
  IoInit();
  cc2420_init();
  hal_atomic_enable_interrupt();//��ȫ���ж�
  cc2420_setchnl(11);//�����ŵ�����
  cc2420_setrxmode();//�򿪽�����
  cc2420_enableAddrDecode();//�����ַ����
  cc2420_setpanid(0x0001);//����PANid
  cc2420_setshortaddress(0x0000);//���ýڵ�Ķ̵�ַ
  cc2420_enablefifop();//�򿪶�fifop���ж�֧��

  des_address=0x01;
  demopacket=malloc(sizeof(demo_datapacket));//�����ڴ�ռ�
  demopacket->length=0x0f;//֡������
  demopacket->fcf=0x8841;//֡������
  demopacket->dsn=0x01;//����֡���к�
  demopacket->address.destination_pan=0x0001;//Ŀ�Ľڵ��PANid
  demopacket->address.destination_address=des_address;//Ŀ�Ľڵ��ַ
  demopacket->address.source_pan=0x0001;//Դ�ڵ��PANid
  demopacket->address.source_address=0x0000;//Դ�ڵ��ַ
  demopacket->payload=0x0000;//֡������
  uint16_t packet_number=0;
  for (uint8_t i=0; i<5000; i++)
 	{
 	  for(uint8_t j=0; j<255; j++)//��ʱ255����
 	  	{
			_delay_loop_2(8*250);
 	  	}
	  packet_number++;
	  printf("��%d����",packet_number);
	  cc2420_writetxfifo(((demopacket->length)-1), (uint8_t *) demopacket);//��ʼ����
	  Leds_redToggle();
	  Leds_greenToggle();
	  printf("�������ڵ� %d\n",demopacket->address.destination_address);
	  printf("------֡���к�Ϊ%d\n\n",demopacket->dsn);
	  demopacket->dsn++;
  	}
}
