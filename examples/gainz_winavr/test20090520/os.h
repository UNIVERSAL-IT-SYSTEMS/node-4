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
#ifndef os_h
#define os_h
#include "project.h"

	//ԭ�Ӳ���
	 typedef uint8_t  hal_atomic_t;
	 inline hal_atomic_t  hal_atomic_start(void );
	 inline void  hal_atomic_end(hal_atomic_t oldSreg);
	 inline void hal_atomic_enable_interrupt(void);
	//ϵͳ����
	 inline void HAL_wait(void );
	 inline void HAL_sleep(void );
	 inline void HAL_sched_init(void );
	 inline bool HAL_run_next_task(void);
	 inline void HAL_run_task(void);
	 bool  HAL_post(void (*tp)(void));
	//��������
	typedef struct _HAL_sched_entry_T {
		void (*tp)(void);
	  
	}HAL_sched_entry_T;

	enum HAL_CON{
	  HAL_MAX_TASKS = 8, 
	  HAL_TASK_BITMASK = HAL_MAX_TASKS - 1
	};
	volatile HAL_sched_entry_T HAL_queue[HAL_MAX_TASKS];
	uint8_t HAL_sched_full;
	volatile uint8_t HAL_sched_free;

#endif

