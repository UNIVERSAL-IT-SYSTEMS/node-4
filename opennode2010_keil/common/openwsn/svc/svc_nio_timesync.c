#include "svc_configall.h"
#include "svc_foundation.h"
#include "../rtl/rtl_time.h"
#include "../rtl/rtl_frame.h"
#include "../osx/osx_timer.h"
#include "svc_nio_aloha.h"
#include "svc_nio_timesync.h"

TiNioTimeSync *timesync_construct( char * buf,uintx size)//todo
{
	memset(buf,0x00,size);
	hal_assert( sizeof(TiNioTimeSync)<=size);
	return ( TiNioTimeSync *)buf;
}

void timesync_destroy(TiNioTimeSync * sync)//todo
{
	return;
}



TiNioTimeSync * timesync_open( TiNioTimeSync * sync, TiOsxTimer * timer,TiAloha * mac,uint16 period)//todo
{
	sync->systimer = timer;
	sync->period = period;
    sync->seqid =0;
	//��֪��������������Ӧ�ø�ʲôֵ��
	//����ֻ�Ǽ򵥵ذ������ڵ�㲥������ʱ�丳������ʱ��
	/*
	sync->scale_factor = 
	sync->shift_factor = 
	*/
	sync->mac = mac;
	sync->txbuf = frame_open( (char *)( &sync->txbuf_mem), FRAME_HOPESIZE(SYN_MAX_FRAME_SIZE), 3, 20, 0);

	return sync;
}

//����ʱ��ͬ��������㲥ʱ��ͬ��֡
uintx timesync_start( TiNioTimeSync * sync)//todo
{
	TiSystemTime time;
	TiSystemTime temp;
	char * ptr;
	int i;
	dbc_putchar( 0xfe);//todo for testing
	if ( frame_empty( sync->txbuf))
	{
		dbc_putchar( 0xfd);//todo for testing
		frame_reset( sync->txbuf,3,20,0);
		time = timesync_current(  sync);
		ptr = frame_startptr( sync->txbuf);
		ptr[0] = CONFIG_NIOSYNC_IDENTIFIER;
		ptr[1] = NIOSYNC_CMD_REQUEST;
		ptr[2] = sync->seqid;
		for ( i=0;i<8;i++)
		{
			temp = time;
			ptr[3+i] = ( uint8)( temp>> (8*i));
		}
		frame_setlength( sync->txbuf,13);
	}
	 timesync_evolve( sync, NULL );
	 return frame_length( sync->txbuf);

}
//???????????????������������������
void  timesync_close( TiNioTimeSync * sync )
{
	
}


void timesync_stop( TiNioTimeSync * sync)//todo
{
	
}

//���ر���ʱ��
TiSystemTime timesync_current( TiNioTimeSync * sync)//todo 
{
	return sync->systimer->time;
}

void timesync_set( TiNioTimeSync * sync,TiSystemTime ms)
{
	sync->systimer->time = ms;
}
//��ʱ��ͬ��֡�л��ͬ��ʱ��
//ptr[0] = identifier;
//ptr[1] = cmd_type;
//ptr[2] = seqid;

//ptr[3] ~ptr[10] = time;��λ��ǰ��λ�ں�
TiSystemTime timesync_get( TiFrame * frame)
{
	TiSystemTime time;
	char * ptr;
	ptr = frame_startptr( frame);
	time = (uint64)( ptr[3])|((uint64)( ptr[4])<< 8)|((uint64)( ptr[5])<< 16)|((uint64)( ptr[6])<< 24)|((uint64)( ptr[7])<< 32)|
		((uint64)( ptr[8])<< 40)|((uint64)( ptr[9])<< 48)|((uint64)( ptr[10])<< 56);
	return time;
}
void timesync_forward( TiNioTimeSync * sync,TiSystemTime step )// ��ǰ����
{
	clock_forward(sync->systimer->time,step);
}

void timesync_backward( TiNioTimeSync * sync,TiSystemTime step )// ������
{
	clock_backward( sync->systimer->time,step);
}


void timesync_initiate(  TiNioTimeSync * sync,TiAloha *mac,TiFrame * rxbuf)//todo initialize the time
{
	TiSystemTime time;
	uint16 i;
	uint8 count = 0;
	char * ptr;
	i = 0;
	//����������ʱ��ͬ������֡���ı䱾��ʱ��
	while ( i<0x1ff)
	{
		frame_reset( rxbuf,3,20,0);
		count = aloha_recv( mac,rxbuf,0x00);
		i++;
        if ( count)
        {
			ptr = frame_startptr( rxbuf);
			//����ֻ�Ǽ򵥵�ʱ��ͬ�������յ���ʱ��ֱ�Ӹ�������ʱ�ӡ�
			if ( ptr[0]==CONFIG_NIOSYNC_IDENTIFIER&&ptr[1]==NIOSYNC_CMD_REQUEST&&ptr[2]> sync->seqid)
			{
				time = timesync_get( rxbuf);
                timesync_set( sync,time);
				sync->seqid = ptr[2];
				break;
			} 
			else
			{
				count = 0;
			}
        }
	}
//��������㲥ʱ��ͬ������֡�������㲥����
	if ( count)
	{
		for ( i=0;i<3;i++)
		{
			timesync_start( sync);
		}
	}
}


void timesync_evolve( void * macptr, TiEvent * e )//todo
{
	TiNioTimeSync * sync = (TiNioTimeSync *)macptr;
	uintx count = 0;
	dbc_putchar( 0xfc);//todo for testing
	if ( !frame_empty( sync->txbuf))
	{
		dbc_putchar( 0xfb);//todo for testing
        count = aloha_broadcast( sync->mac,sync->txbuf,0x00);
		if ( count)
		{
			dbc_putchar( 0xfa);//todo for testing
			frame_totalclear( sync->txbuf);
		}
	}
}


