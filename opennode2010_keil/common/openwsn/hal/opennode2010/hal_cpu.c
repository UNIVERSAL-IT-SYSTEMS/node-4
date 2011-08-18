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

#include "../hal_configall.h"
#include "../hal_foundation.h"
#include "../hal_cpu.h"

uint8 g_atomic_level = 0;
#ifdef (CONFIG_CRITICAL_METHOD == 03) 
uint8 g_atomic_flag = 0;
#endif

/**
 * A very short delay for only 250ns. This one is used to adjust hardware timing 
 * in some special cases. 
 * 
 * @attention At least Keil compiler can recognize #pragma O0
 * @attention 
 */
#pragma O0 
void cpu_delay250ns(void)
{
#if defined(CONFIG_CPU_FREQUENCY_8MHZ)
    cpu_nop();
    cpu_nop();
#elif defined(CONFIG_CPU_FREQUENCY_48MHZ)
    cpu_nop();
    cpu_nop();
    cpu_nop();
    cpu_nop();
    cpu_nop();
    cpu_nop();
    cpu_nop();
    cpu_nop();
    cpu_nop();
    cpu_nop();
    cpu_nop();
    cpu_nop();
#elif defined(CONFIG_CPU_FREQUENCY_72MHZ)
    int counter = 9; // = 18/2
    while (count > 0)
    {
        cpu_nop();
        count --;
    }
#else
  #error "You must choose your CPU frequency and implement this function again."
#endif  
}

/**
 * A very short delay for only 1us. This one is used to adjust hardware timing 
 * in some special cases. 
 * 
 * @attention Not tested yet.
 */
#pragma O0 
inline void cpu_delay1us()
{
#if defined(CONFIG_CPU_FREQUENCY_8MHZ)
    int counter = 2;//6; // 8-2
#elif defined(CONFIG_CPU_FREQUENCY_48MHZ)
    int counter = 46 // 48-2
#elif defined(CONFIG_CPU_FREQUENCY_72MHZ)
    int counter = 70 // 72-2
#else
  #error "You must choose your CPU frequency and implement this function again."
#endif  
   
    while (counter > 0)
    {
        cpu_nop();
        counter --;
    }
}

/* hardware dependent function.
 * on GAINZ platform, the main clock frequency is 8MHz. so 8 nop instruction
 * occupies approximately 1 u-second (usec)
 * 
 * @attention
 * - the input parameter value should not large than the maximum value of uint16 type
 */
#pragma O0 
void cpu_delayus(uint16 usec)
{
	while (usec > 0) 
	{
        cpu_delay1us();
        usec --;
    }
}

/* attention: 
 * the input msec value should not exceed the maximum value of uint16 type 
 */
#pragma O0 
void cpu_delayms(uint16 msec) 
{
    while (msec > 0)
    {
        cpu_delayus( 500 );
        msec --;
    }
}

