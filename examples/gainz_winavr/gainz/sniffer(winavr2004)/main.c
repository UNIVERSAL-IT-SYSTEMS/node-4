//----------------------------------------------------//
//-------Institute Of  Computing Technology-----------//
//------------Chinese Academic  Science---------------//
//-----�й���ѧԺ���㼼���о����Ƚ����Լ���ʵ����-----//
//----------------------------------------------------//

/**
 * www.wsn.net.cn
 * @copyright:nbicc_lpp
 * @data:2006.11.22
 * @version:0.0.1
 * @updata:$
 *
 */
#include "top.h"
#include "led.h"

//--------------------------------------------------------

demo_datapacket * demopacket;
//--------------------------------------------------------


//---------------------------------------------------------------
inline uint8_t hardwareInit(void)

{
HAL_SET_PIN_DIRECTIONS(S();
  return SUCCESS;
}

uint8_t demo_ieee_address[8];
uint16_t shortaddress;
//---------------------------------------------------------
int   main(void)
{

  hardwareInit();
  Leds_greenOn();
  Leds_redOn();
  Leds_yellowOn();
  IoInit();
  
  HAL_sched_init();  //������ȳ�ʼ��
  cc2420_init();
  hal_atomic_enable_interrupt();  //ʹ��ȫ���ж�

  cc2420_setchnl(3);  //�����ŵ�
  cc2420_setrxmode();  //�򿪽�����

  cc2420_enablefifop();  //�򿪶�FIFOP���ж�֧��

 printf("sniffer is start........\n");
  while(1) {
	HAL_run_task();
  	}
  
}
