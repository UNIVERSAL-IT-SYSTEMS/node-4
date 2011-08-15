 /*
 * �����Ƕ�ʱ���ĳ���
 */

#include "apl_foundation.h"

#include "openwsn/hal/opennode2010/cm3/core/core_cm3.h"
#include "openwsn/hal/hal_timer.h"
#include "openwsn/hal/hal_interrupt.h"
                                   
static TiTimerAdapter g_timer3;
static TiTimerAdapter g_timer2;
static void _timer2_handler(void * object, TiEvent * e);
static void _timer3_handler(void * object, TiEvent * e);

int main( void)
{
    TiTimerAdapter * timer_3;
    TiTimerAdapter * timer_2;
    led_open();
    halUartInit( 9600,0);

    timer_3 = timer_construct( (void *)&g_timer3,sizeof(g_timer3));
    timer_2 = timer_construct( (void *)&g_timer2,sizeof(g_timer2));

    timer_setinterval( timer_3,1000,7999);
    timer_setinterval( timer_2,1000,7999);

    timer_3 = timer_open( timer_3,3,NULL,NULL,0x01);
    timer_2 = timer_open( timer_2,2,NULL,NULL,0x01);
    
    timer_setprior( timer_3,0,0);
    timer_setprior( timer_2,0,0);
    hal_attachhandler( INTNUM_TIMER2, _timer2_handler, timer_2);
    hal_attachhandler( INTNUM_TIMER3,  _timer3_handler, timer_3 );

    timer_start( timer_3);
    timer_start( timer_2);
    __disable_irq();
    __enable_irq();
    while (1)
    {/*
       if ( timer_expired( timer_3))//�����ò�ѯģʽ��timer->option����Ϊ0x00.
       {
           timer_CLR_IT( timer_3);
           led_toggle( LED_RED);
       }*/
    }

}

/*
void TIM3_IRQHandler(void)
{

    //TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    //GPIO_WriteBit(GPIOA, GPIO_Pin_8, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8)));

    //GPIO_ResetBits( GPIOA,GPIO_Pin_8);
   
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        led_toggle( LED_RED);
    }
    
}

void TIM2_IRQHandler( void)
{
    
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        USART_Send( 0xff);
    }
    
}
*/

static void _timer2_handler(void * object, TiEvent * e)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        USART_Send( 0xff);
    }
}
static void _timer3_handler(void * object, TiEvent * e)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        led_toggle( LED_RED);
    }
}
