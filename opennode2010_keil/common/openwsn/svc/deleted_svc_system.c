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

/* TiSystem is the highest level object in an application. it has the 
 * following functions:
 * - receive messages from other objects and environment and call corresponding 
 *	 message handlers. the message source include other objects, interrupt service
 *	 handler, RTC, Timer, bytes arrived from UART, packets arrived from wireless,
 *   scheduler object.
 * - call the evolve() function of other objects. this will drive the state 
 *   transfer of other objects.
 * - call the extern function/class, which is the entrance of user defined functions.
 *	 (like the main() function which is the entry function of the whole application)
 *
 * the openwsn developer must provide it's own app class. this class is named as 
 * TiApplication, and it should provide three interface functions:
 * - construct();
 * - destroy();
 * - evolve();
 */

typedef struct{
}TiSystem;

TiApplication

TiPFunConstruct
TiPFunDestroy
TiPFunEvolve
TiPFunFilterExecute

TiPFunFilterExecute( state, pointer, input, output, option )

/* g_system: pre-defined global object */
g_tsys.attach( &startobject )


svc_construct()
svc_evolve()
svc_destroy()

typedef struct
}TiObjectInterface;

run()
{
	g_system.construct
	g_system.put(udo);
}

g_system.registerservice( udo_create, udo_construct, udo_evolve, udo_destroy, udo_free );

udo_create
udo_construct
udo_evolve
udo_destroy
udo_free

ϵͳ���Զ�Ѱ��һ����TUserDataObject/UserService�Ķ���
No, �����ӿ�̫����

���������ӣ�ϵͳ�Զ�Ѱ��һ����svc_execute()�ĺ���������������ڲ������û��Լ����create, construct, evolve, destroy, free

svc/user_execute( state, input, output, option ) 
������dllmain
��Filter��һ���ģ���ˣ�user���ֿ�����Ȼ��Ȼ��Ҳ��Ϊfilter����ϵͳ����ȻҲ���Բ�����filter��ϵ
����������Ĳ�ͬ�ǵ��ô˺���ʱ������δ���������Ե�һ��������������state���������ú������Ը���state���ֲ���

�����RTOS��ϣ�
���ǵĶ���������ΪRTOS��һ��thread����


/* @attention
 * in OOP design and implementation, every object shuold be able to contain their 
 * message queue and has message handlers. however, in openwsn project, only the 
 * TiSystem object has message queue. this is intended to simplify the system 
 * design and data route.
 */ 

/* @attention
 * msgsend() is elaborately designed and it can be called inside ISR functions 
 * and any other objects. 
 */ 
tsys_create()
tsys_construct()
tsys_destroy()
tsys_free()
tsys_run()
tsys_trigger(msg)
tsys_msghandler()
tsys_msgsend( id, handler )
tsys_msgrecv( id )
tsys_filters
tsys_objectstore

int main()
{
	g_tsystem.construct();
	g_tapp.construct();
	g_tsystem.run();
	g_tapp.destroy();
	g_tsystem.destroy();
}


ע�⣬system����߲㣬һ���������İ���������Σ������²㲻Ӧ�ð���system
���ǣ��ײ�Ҫ��message��������ô���أ�
����ͨ������svc_foundationʵ�ֵġ�
system������ʱ�򣬻��svc_foundation.msgsend /msgrecv ����ָ�븳ֵ�������Ϳ����ˡ�Ȼ������ģ��Ϳ��Ե���msgsend/msgrecv��

_register_msgsend
_register_msgrecv

msgsend( objfrom, objto, msgid )
msgsend( msgid, handler )

ע
msg����Ӧ����ϵͳ��ʵ�֣���ÿһ��object���������ܵĶ�����ֻҪ���ṩ��msghandler��������ע���

msg.id = ISR, HARDWARE, TIMER, OBJECT....   // system message + user defined message , depending on the value of ID
msg.objectfrom = pointer
msg.objectto = pointer

msg�Ĵ�����ʵ��Ҳ��filterģʽ
��default��msghandler����߲�TiSystem�ṩ�����ĳЩobjectϣ�����ظ���Ϣ��Ҳ�����ṩ�Լ���msghandler��ע���foundation��
Ȼ���������ٵ���g_system.handlerִ��ȱʡ����

TiSystem.msgdispatcher()
{
	check if there're messages;
	if have, peek one, else exit
	check: msg.id, objectfrom, objectto
   if objectto != NULL
	   call msg.handler( objectto, objectfrom, id )
   else
		call this.handler( this, objectfrom, id )
		   
}

this.handler( TiSystem, objectfrom, id )
{
	swtich(id)
	case
	case
}

��Ϊϵͳ���������ṩһ��msgqueue_t
���еĶ��󶼿���ʹ��֮��ֻ����TiSystem���ṩȱʡ��msg���մ���

��ISR�п�������д
msgsend( id, NULL, NULL )
objectto == NULL����ζ�����msg�����TiSystem����

msgsend( queue, id, NULL, NULL )
��msgsend�����ڴ���objectto���Ͳ���ָ��handler��������������C���ԣ����ܾ�Ҫ����handler(owner,...)��ʽ����objectto��handler��Ҫ����

