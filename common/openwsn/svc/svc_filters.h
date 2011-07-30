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

/* Interface: TiFilter
 * xxx_leftexec(TiFilter * filter, char * inbuf, uint8 input_len, char * outbuf, uint8 outbuf_size )
 * xxx_rightexec(TiFilter * filter, char * inbuf, uint8 input_len, char * outbuf, uint8 outbuf_size )
 */

typedef uint8 (* TiFilterLeftExecute)(void * filter, char * inbuf, uint8 input_len, char * outbuf, uint8 outbuf_size );
typedef uint8 (* TiFilterRightExecute)(void * filter, char * inbuf, uint8 input_len, char * outbuf, uint8 outbuf_size );

typedef struct{
}TiIoFilters;

iofilters_leftexecute(void * filter, char * inbuf, uint8 input_len, char * outbuf, uint8 outbuf_size )
{
	flt;
	leftexec( flt, inbuf, len, outbuf, outbuf );
	for each filter do
		flt = ;
		leftexec = ;
		leftexec( flt, outbuf, len, outbuf, len );
	end
}






lread
lwrite
rread
rwrite


attach
detach

iofilter
iohandler


TiFilters
{
}

flt_lread
flt_lwrite
flt_rread
flt_rwrite

flt_insertfilter

TiFilter 
ͬ����4��R/W����
rprocess


filters_process
filters_
char buf[]

l

����һ���µ��������ͽ�

sysint_t  �Զ�����ϵͳ�ܹ�������С������8bit, 16bit��32bit
sysuint_t 

SYSINT
SYSINTU
SYSUINT
INTX
INTY
INTX
UINTX

INT
UINT


// push mode
flt_lwrite( TiIoFilterchar * buf, uint16 len )
{
	for each filter in the list
		flt = 
		flt_lwrite// flt_setbuf
		flt_rread // flt_getbuf 
	end
	// for the last one is iohandler, there's no rread
	handler_lwrite( buf, )
}

flt_setbuf
flt_getbuf

// pull mode
flt_lread()
{
	flt_rsetbuf
	for each buffer
	process
	return buf
}

��ÿ��filter���ƺ�����Ҫ�ṩ����4��function
���Ƕ�filters
�ƺ�ֻҪ��������
lexec/levolve( object, inbuf, len )  û��output����������Ϊ���һ����iohandler�����output��������filters�п���
rexec/revolve

Ҳ�����ṩoutput buffer����������������Ϊfilter�ṩiohandler����Ϊ������ᴦ��֮
while (1)
	uart_read
	flt_lwrite/lexec( COM_FILTER, 
	process buffer data in the main thread => is actually the iohandler
	flt_rwrite/rexec( RF_FILTER, data )
	wls_write
end while

����
ͨ��notifier����uart��filter





