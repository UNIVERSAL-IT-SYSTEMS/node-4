
#include "apl_foundation.h"
#include "../../common/openwsn/hal/opennode2010/hal_led.h"

void RCC_Configuration(void);

int  main (void)
{ 
  
  int i;
  RCC_Configuration();//�������õ���48M����������øú���ϵͳӦ����8M�����С�

  led_open();
 
  while( 1) 
  {
	  led_toggle( LED_RED);
	  hal_delay(1000);//���������ʱ�Ӳ���Ĭ��ʱ�ӣ�led����Ƶ��Ӧ����1S������ʱ�ӱ����õ�48M������led����Ƶ��Ҫ����1S��
  
   
  }
  return 0;
}




void RCC_Configuration(void)
{
	/* system clocks configuration -----------------ϵͳʱ������-------------------*/
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();                                    //������RCC�Ĵ�������Ϊȱʡֵ
	/* Enable HSE */
	//RCC_HSEConfig(RCC_HSE_ON);                    //�����ⲿ���پ���HSE��
	/* Wait till HSE is ready */ 
	//HSEStartUpStatus = RCC_WaitForHSEStartUp();    //�ȴ�HSE����
	//if(HSEStartUpStatus == SUCCESS)               //���ɹ����񣬣�����Ϊϵͳ����ʱ�����ã�
	//{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //ʹ��FLASHԤȡָ����
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);   //����FLASH�洢����ʱʱ��������(���ݲ�ͬ��ϵͳʱ��ѡȡ��ͬ��ֵ)

		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);   //����AHBʱ��=72 MHz
		/* PCLK2 = HCLK/2 */
		RCC_PCLK2Config(RCC_HCLK_Div2);   //����APB1ʱ��=36 MHz(APB1ʱ�����ֵ)
		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div8);   //����APB2ʱ��=72 MHz
		/* Configure ADCCLK such as ADCCLK = PCLK2/2 */
		RCC_ADCCLKConfig(RCC_PCLK2_Div2); //RCC_PCLK2_Div2,4,6,8
		/* PLLCLK = 8MHz * 9 = 72 MHz */
		//RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12); //PLL�������伤��ǰ������ã�����PLLʱ��Դ����Ƶϵ����
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);
		/* Enable PLL */
		RCC_PLLCmd(ENABLE);
		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}
		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}   
	//}
}

 
 