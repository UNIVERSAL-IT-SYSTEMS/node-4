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

#include "os.h"

//-----------------ԭ�Ӳ���-����---------------------------------------

  inline void hal_atomic_enable_interrupt(void)

{
   __asm volatile ("sei");
   
 }

  inline void  hal_atomic_end(hal_atomic_t oldSreg)
{
  * (volatile unsigned char *)(unsigned int )& * (volatile unsigned char *)(0x3F + 0x20) = oldSreg;
}


 inline hal_atomic_t  hal_atomic_start(void )
{
  hal_atomic_t  result = * (volatile unsigned char *)(unsigned int )& * (volatile unsigned char *)(0x3F + 0x20);
   __asm volatile ("cli");
  return result;
}


//-----------------ϵͳ���ߺ���--------------------------------------
 inline void HAL_wait(void)
{
   __asm volatile ("nop");
   __asm volatile ("nop");}

 inline void HAL_sleep(void)
{

  * (volatile unsigned char *)(unsigned int )& * (volatile unsigned char *)(0x35 + 0x20) |= 1 << 5;
   __asm volatile ("sleep");}
   
//-----------------������ȳ�ʼ��----------------------------------------

 inline void HAL_sched_init(void )
{
  HAL_sched_free = 0;
  HAL_sched_full = 0;
}

//-----------------�����ύ����----------------------------------------

bool  HAL_post(void (*tp)(void))
{
  hal_atomic_t fInterruptFlags;
  uint8_t tmp;
  fInterruptFlags = hal_atomic_start();
  tmp = HAL_sched_free;
  if (HAL_queue[tmp].tp == (void *)0) {
      HAL_sched_free = (tmp + 1) & HAL_TASK_BITMASK;
      HAL_queue[tmp].tp = tp;
      hal_atomic_end(fInterruptFlags);

      return TRUE;
    }
  else {
      hal_atomic_end(fInterruptFlags);

      return FALSE;
    }
}
//---------------�������к���1------------------------------------------

 inline bool HAL_run_next_task(void)
{
  hal_atomic_t fInterruptFlags;
  uint8_t old_full;
  void (*func)(void );

  fInterruptFlags = hal_atomic_start();
  old_full = HAL_sched_full;
  func = HAL_queue[old_full].tp;
  if (func == (void *)0) 
    {
      hal_atomic_end(fInterruptFlags);
      return 0;
    }

  HAL_queue[old_full].tp = (void *)0;
  HAL_sched_full = (old_full + 1) & HAL_TASK_BITMASK;
  hal_atomic_end(fInterruptFlags);
  func();
  return 1;
}

//--------------�������к���2-------------------------------------------
 inline void HAL_run_task(void)
{
  while (HAL_run_next_task()) 
    ;
  HAL_sleep();
  HAL_wait();
}