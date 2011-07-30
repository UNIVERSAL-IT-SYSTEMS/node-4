/*******************************************************************************
 * This file is part of OpenWSN, the Open Wireless Sensor Network Platform.
 *
 * Copyright (C) 2005-2010 zhangwei(TongJi University)
 *
 * OpenWSN is a free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 or (at your option) any later version.
 *
 * OpenWSN is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * For non-opensource or commercial applications, please choose commercial license.
 * Refer to OpenWSN site http://code.google.com/p/openwsn/ for more detail.
 *
 * For other questions, you can contact the author through email openwsn#gmail.com
 * or the mailing address: Dr. Wei Zhang, Dept. of Control, Dianxin Hall, TongJi
 * University, 4800 Caoan Road, Shanghai, China. Zip: 201804
 *
 ******************************************************************************/
 
 /** THIS MODULE WILL BE ELIMINATED FROM PROJECT
  * USE TiLightQueue svc_lightqueue intead
  */

#ifndef _RTL_SYSQUEUE_H_9032_
#define _RTL_SYSQUEUE_H_9032_

/* TiLightQueue Data Structure
 * this is a C language based queue data structure. it's actaully an ring queue.
 * different to TiDynaQueue, the TiLightQueue has fixed number of items/elements.
 * It will not increase memory when it's full. It's mainly used in kernel developing
 * or embedded developing without dynamic memory allocator support.
 *
 * another advantage of TiLightQueue is that it can be moved to another place
 * inside the address space and can still work.
 *
 * portability
 *	- ansi c language
 *  - linux, windows, and embedded platforms with c compiler only
 *
 * @state
 *	finished but not tested yet
 *
 * @author zhangwei in 200503
 * @modified by zhangwei in 200803
 *	- eliminate the call of malloc() and free().
 * @modified by zhangwei in 200905
 *	- change the name as TiLightQueue. the original name is TiRingQueue
 *    the new predix "lwque_" means "light weight queue"
 */

#include "osx_configall.h"
#include "osx_foundation.h"
#include "../hal/hal_interrupt.h"
#include "../hal/hal_cpu.h"
#include "../rtl/rtl_lightqueue.h"


/* RingQueue Data Structure
 * This ring queue has fixed number of items/elements. It will not increase memory
 * when it's full. It's mainly used in kernel developing or embedded developing
 * without dynamic memory allocator support
 *
 */


/* TiSysQueue ���� TiLightQueueʵ�֣����TiLightQueue�������˻��Ᵽ��������
 * ʹ���������multi-thread��interrupt service����
 */

#define SYSQUEUE_HOPESIZE(itemsize,capacity) LIGHTQUEUE_HOPESIZE(itemsize,capacity)

#ifdef __cplusplus
extern "C" {
#endif

/* @attention
 * @warning
 * you must declare the TiSysQueue variables with prefix "volatile", or else you 
 * still encounter multi-thread problems in developing.
 */

#define TiSysQueue TiLightQueue


inline TiLightQueue * sysque_construct( void * buf, uintx size, uintx itemsize );
inline void sysque_destroy( TiLightQueue * que );

inline uintx sysque_count( TiLightQueue * que );
inline uintx sysque_capacity( TiLightQueue * que );
inline void * sysque_getbuf( TiLightQueue * que, uintx idx );

inline bool sysque_empty( TiLightQueue * que );
inline bool sysque_full( TiLightQueue * que );
inline void * sysque_front( TiLightQueue * que );
inline void * sysque_rear( TiLightQueue * que );
inline bool sysque_pushback( TiLightQueue * que, void * item );
inline bool sysque_pushfront( TiLightQueue * que, void * item );
inline bool sysque_popfront( TiLightQueue * que );
inline bool sysque_poprear( TiLightQueue * que );
	
inline TiLightQueue * sysque_construct( void * buf, uintx size, uintx itemsize )
{
	return lwque_construct( buf, size, itemsize );
}

inline void sysque_destroy( TiLightQueue * que )
{
	return lwque_destroy( que );
}

inline uintx sysque_count( TiLightQueue * que )
{
	return lwque_count( que );
}

inline uintx sysque_capacity( TiLightQueue * que )
{
	return lwque_capacity( que );
}

inline void * sysque_getbuf( TiLightQueue * que, uintx idx )
{
	return lwque_getbuf( que, idx );
}

inline bool sysque_empty( TiLightQueue * que )
{
	bool ret;
	hal_atomic_begin();
	ret = lwque_empty(que);
	hal_atomic_end();
	return ret;
}

inline bool sysque_full( TiLightQueue * que )
{
	bool ret;
	hal_atomic_begin();
	ret = lwque_full(que);
	hal_atomic_end();
	return ret;
}

inline void * sysque_front( TiLightQueue * que )
{
	void * item;
	hal_atomic_begin();
	item = lwque_front( que );
	hal_atomic_end();
	return item;
}

inline void * sysque_rear( TiLightQueue * que )
{
	void * item;
	hal_atomic_begin();
	item = lwque_rear( que );
	hal_atomic_end();
	return item;
}

inline bool sysque_pushback( TiLightQueue * que, void * item )  
{
	bool ret;
	hal_atomic_begin();
	ret = lwque_pushback( que, item );
	hal_atomic_end();
	return ret;
}

inline bool sysque_pushfront( TiLightQueue * que, void * item )
{
	bool ret;
	hal_atomic_begin();
	ret = lwque_pushfront( que, item );
	hal_atomic_end();
	return ret;
}

inline bool sysque_popfront( TiLightQueue * que )
{
	bool ret;
	hal_atomic_begin();
	ret = lwque_popfront( que );
	hal_atomic_end();
	return ret;
}

inline bool sysque_poprear( TiLightQueue * que )
{
	bool ret;
	hal_atomic_begin();
	ret = lwque_poprear( que );
	hal_atomic_end();
	return ret;
}

#ifdef __cplusplus
}
#endif

#endif
