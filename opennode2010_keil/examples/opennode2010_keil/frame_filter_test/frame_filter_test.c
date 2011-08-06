

#include "apl_foundation.h"
#include "../../../common/openwsn/hal/opennode2010/hal_configall.h"
#include <stdlib.h>
#include <string.h>
#include "../../../common/openwsn/hal/opennode2010/hal_foundation.h"
#include "../../../common/openwsn/hal/opennode2010/hal_cpu.h"
#include "../../../common/openwsn/hal/opennode2010/hal_led.h"
#include "../../../common/openwsn/hal/opennode2010/hal_assert.h"
#include "../../../common/openwsn/hal/opennode2010/hal_cc2520.h"
#include "../../../common/openwsn/rtl/rtl_frame.h"
#include "../../../common/openwsn/hal/opennode2010/hal_debugio.h"
#include "../../../common/openwsn/rtl/rtl_slipfilter.h"
#include "../../../common/openwsn/svc/svc_sio_acceptor.h"

#ifdef CONFIG_DEBUG
#define GDEBUG
#endif
//#define TEST_ACK_REQUEST

#define MAX_IEEE802FRAME154_SIZE                128


#define PANID				0x0001
#define LOCAL_ADDRESS		0x01  
#define REMOTE_ADDRESS		0x02
#define BUF_SIZE			128
#define DEFAULT_CHANNEL     11

static char                 m_txbuf[FRAME_HOPESIZE(MAX_IEEE802FRAME154_SIZE)];
TiIEEE802Frame154Descriptor m_desc;
TiUartAdapter               m_uart;
TiSioAcceptor               m_sac;
TiSlipFilter                m_slip;

void sendnode1(void);
//void sendnode2(void);

int main(void)
{
    sendnode1();
}

void sendnode1(void)
{
    TiCc2520Adapter * cc;
    TiFrame * txbuf;
    TiIEEE802Frame154Descriptor * desc;
    TiUartAdapter      * uart;
    TiSioAcceptor      * sac;
    TiSlipFilter       * slip;

    uint8 i, first, seqid, option, len;
    char * ptr;

    seqid = 0;

    led_open();

    led_on( LED_ALL);
    hal_delay( 500 );
    led_off( LED_ALL );
    /*
    halUartInit( 9600,0);
    cc = cc2520_construct( (void *)(&m_cc), sizeof(TiCc2520Adapter) );
    cc2520_open( cc, 0, NULL, NULL, 0x00 );
    cc2520_setchannel( cc, DEFAULT_CHANNEL );
    cc2520_rxon( cc );							//Enable RX
    cc2520_enable_addrdecode( cc );					//ʹ�ܵ�ַ����
    cc2520_setpanid( cc, PANID );					//�����ʶ
    cc2520_setshortaddress( cc, LOCAL_ADDRESS );	//���ڱ�ʶ
    cc2520_enable_autoack( cc );
     */

    uart = uart_construct( ( void*)(&m_uart),sizeof(m_uart));
    uart = uart_open(uart,2,9600,8,1,0);

    slip = slip_filter_construct( (void *)(&m_slip),sizeof( m_slip));


    sac = sac_open( (void *)(&m_sac),slip,uart);

    desc = ieee802frame154_open( &m_desc );
    txbuf = frame_open( (char*)(&m_txbuf), FRAME_HOPESIZE(MAX_IEEE802FRAME154_SIZE), 3, 20, 0 );

    option = 0x00;

    while(1)  
    {
        frame_reset( txbuf,3,20,0);
        ptr = frame_startptr( txbuf);

        for ( i = 0;i< 6;i++)
            ptr[i] = i;
        frame_skipouter( txbuf,12,2);
        desc = ieee802frame154_format( desc, frame_startptr( txbuf), frame_capacity( txbuf ), 
            FRAME154_DEF_FRAMECONTROL_DATA ); 
        rtl_assert( desc != NULL );
        ieee802frame154_set_sequence( desc, seqid); 
        ieee802frame154_set_panto( desc,  PANID );
        ieee802frame154_set_shortaddrto( desc, REMOTE_ADDRESS );
        ieee802frame154_set_panfrom( desc,  PANID );
        ieee802frame154_set_shortaddrfrom( desc, LOCAL_ADDRESS );
        frame_setlength( txbuf,20);
        first = frame_firstlayer( txbuf);

        //len = cc2420_write(cc, frame_layerstartptr(txbuf,first), frame_layercapacity(txbuf,first), option);
       // len = cc2520_write(cc, frame_layerstartptr(txbuf,first), frame_length( txbuf), option);
/*
        if( len)
        {
            led_toggle( LED_RED);
            seqid++;
        }
        */

        //uart_write(uart,frame_layerstartptr(txbuf,first),frame_length( txbuf),0);

        sac_write( sac,txbuf,frame_length( txbuf),0);
        sac_evolve(sac);
        hal_delay( 1000);


    }
}