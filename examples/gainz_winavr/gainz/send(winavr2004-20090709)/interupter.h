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
#ifndef interupter_h
#define interupter_h

#include "timer3.h"
#include "uart0.h"
 
	void __attribute((signal))   __vector_7(void);
 
       void __attribute((interrupt))   __vector_26(void);
 
#endif 