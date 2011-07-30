http://www.avrtool.com/avr/gccavr/200710/751.html

����WinAVR��DS18B20Դ����
����WinAVR��DS18B20Դ����
���ߣ�δ֪    AVR��Ƭ����Դ������    �������1142    ����ʱ�䣺2007-10-1    
* 
******************************************************** 
*   �ļ�:   ds18b20.c 
*   ����:   AVR΢������ VS �¶�оƬDS18B20(TO-92) 
*   ����:   WinAVR20040404(AVR-GCC) 
*   ����:   ��������(qjy_dali) 
*   E-mail: qjy_dali@sohu.com 
*   ����:   6/02/2004 
*   �汾:   1.41 
*   ����:   �������ؿ��������ƻ��޸�������򣬵�����ע������޸ġ������߲����������ĺ�������������� ȷ�ģ�����������(^_^)����������������ܵģ����� ��ȷ��������ܵġ�֧��һ��GCC!!! 
******************************************************** 
*/
#ifndef  _DS18B20_C_ 
#define  _DS18B20_C_


/*      �ҵ�һ���¶�оƬDS18B20�����ӵ�AVR΢������ATmega8 16PI(PDIP28)��PD3(INT1)���ţ�������ֻ������PD3���ܶ� û��ʹ���ж�INT1���ܡ�DS18B20(TO-92)���������£� 
*  +-------------+-------------------------------------+ 
*  | Pin-1(GND)  | GND(ground)                         | 
*  +-------------+-------------------------------------| 
*  | Pin-2(DQ)   | ͨ��240ŷķ�ĵ������ӵ�ATmega8��    | 
*  |             | PD3���ţ�ͬʱ��һ��3K�ĵ���������   | 
*  |             | VCC(5V)��                           | 
*  +-------------+-------------------------------------+ 
*  | Pin-3(VD)   | GND(ground)                         | 
*  +-------------+-------------------------------------+ 
*      ˵��������Ȼ���Ҳ��õ���"�����Ե�"ģʽ������DS18B20�����ֲ��ϿɵĹ���ģʽ֮һ������240ŷķ��������� ��Ϊ�˷�ֹ��ȱ�ݵ��û�������DS18B20�Ŀ����ԡ����磬 ����û�û����ȷ����OC(���缫��·)��OD(©����·)�ṹȥ����DS18B20�����Ǵ����ѡ��������ʽ�ṹ����DS18B20���� ������"��Ű��"һ��ʱ���"������"(^_^)����Ȼ��240ŷķ�� ȡֵδ������ǡ���ģ�����߿��Լ�ȥ�Ż�������Ҫ�������ϸ �Ķ������ֲᡣ 
* 
*      ���⣬�Ҳ�����DS18B20��Ĭ�Ͼ���(12λ)����δ�޸ģ���Ҳû��ʹ�������������ܡ������֮����ֻ��һ���򵥵Ķ�ȡ�¶� ��ʵ�����û������Լ�ȥ�Ľ����Լ�ȥ�о������ֲ�(�Ҳ�δ��ȫ ����ֻ�����뿴��һ��� ^_^ )�������ҿ��Կ϶�һ�㣬����� ������ʵ������!���ҳɹ��ض�ȡ���¶�ֵ! 
* 
*      ��ע�������������DS18B20�ģ�������AVR�ķ���Ĵ�������������˿ڼĴ���! ͬʱԤ��������˿ڼĴ�����д��0�� ��ʵ�����൱��һ����̬�ţ�ֻ�������뱻�ӵأ�ʹ������һ ��OC�ţ�ʹ�ܶ˳������OC�ŵ�ʵ������! 
* 
*      1-wire���ߵĵ���������I2C�������ƣ��������빦�ܣ����ԣ������ϵ���һ�豸�����ں��ʵ�ʱ��ǿ���������ߣ���������Ҫ���ָߵ�ƽ���������ÿһ���豸���ͷ������ߡ������������ ��DQ_TO_1()����ֻ���ͷ������ߣ�������˵����һ����ǿ���������ߵ�ƽ�����ߵĸߵ�ƽ������������ʵ�ֵġ� 
*/ 
#define  DQ_18B20       (1<<3)                // PD3 
#define  DQ_TO_0()      (DDRD |=  DQ_18B20)   // PD3='0' 
#define  DQ_TO_1()      (DDRD &= ~DQ_18B20)   // PD3='float' 
#define  DQ_status()    (PIND & DQ_18B20)     // read PD3 pin

/*     �����������AVR΢��������ʱ��Ƶ��! �ر�ע�⣺Ƶ�ʶ���ĵ�λ��MHz! ������ʹ�ø�����! ������ľ�����12MHz��  ��Ӧ��д��12.0000��12.0֮�ࡣ 
*     �ҵ�ʵ���·�ľ����ǣ�11.0592MHz 
*/ 
#ifndef  CPU_CRYSTAL 
#define  CPU_CRYSTAL    (11.0592) 
#endif

/*     �����WinAVRϵͳ�ṩ����ʱͷ�ļ�"delay.h"�����и���������ʱģ�飬����16λ���Ǹ�(16-bit count, 4 cycles/l- oop.)��ϸ���뿴���ͷ�ļ��� 
*/ 
#define  wait_us(us)\ 
    _delay_loop_2((INT16U)((us)*CPU_CRYSTAL/4))

/*---------------- ����ԭ������ ------------------*/ 
// 1����ʼ��ģ�� 
void   ds18b20_config(void);       // ���ö˿�

// 3������ģ�� 
BOOL   ds18b20_reset(void);        // ��λDS18B20 
void   ds18b20_write(INT8U dat);   // д�ֽڵ�DS18B20 
INT8U  ds18b20_read(void);         // ���ֽڴ�DS18B20

// 2��Ӧ��ģ�� 
void   convert_T(void);            // �����¶�ת�� 
INT16U read_T(void);               // ��ȡת��ֵ


/*------------------------------------------------------- 
*  ����(ʹ��)AVR��DS18B20�Ľӿ� 
*/ 
void ds18b20_config(void) 
{ 
    DDRD  &= ~DQ_18B20;   // ����ģʽ(�ϵ�ʱΪ�ߵ�ƽ) 
    PORTD &= ~DQ_18B20;   // ���������д0���Ժ��ٸ��� 
}

/*------------------------------------------------------- 
*    ��λ1-wire���ߣ���̽���Ƿ����¶�оƬDS18B20(TO-92 
*  ��װ)���������ϣ��з���SUCC��û�з���FAIL 
*/ 
BOOL ds18b20_reset(void) 
{ 
    BOOL bus_flag;

    DQ_TO_0();      // ����1-wire����Ϊ�͵�ƽ(ռ������)...

    /* �����ӳ�480us~960us, ��Ӳ��������أ���Ӧ������ѡСֵ(480us)�� �Ѷ�������ϵͳ(�������ӳ��ڼ䷢���жϵ����ӳٱ䳤)�� 
     */ 
    wait_us(490);   // 490us

    cli();          // �������ʱ��Ҫ��Ƚ��ϸ�Ϊ������������ж� 
    DQ_TO_1();      // ����1-wire����Ϊ�ߵ�ƽ(�ͷ�����) 
     
    /* ������������ɱ���������õģ������������MCU������ʱ��ʱ����ģ�  ���Բ���ռ���û�MCU��ʱ�䣬���ص���(����ǰ��ĺ���Ϳ���ȷ����) 
     */ 
    wait_us(67.5);  // ���ʱ��: 60us+7.5us!(æ��ʱ��ֻ��һ�ֲ���) 
     
    // ̽���������Ƿ�������     
    if(DQ_status()) bus_flag=FAIL;   // ��λ�����ߵ�û�з������������� 
    else bus_flag=SUCC;              // ��λ�����߲��������������� 
     
    sei();          // �˳��ٽ������(���ж�)

    /* ��֤Master�ͷ����ߵ�ʱ��(����˵���ߴ��ڸߵ�ƽ��ʱ��)��С�� 480us���ɣ���һʱ��Ӷ�����״̬֮ǰ�Ϳ�ʼ�ˣ������������� ʱ��������ڡ���Master�ͷ����ߵ�ǰ��Σ�Ҳ�Ǳ�������������������֮ʱ�� 
     */ 
    wait_us(490-67.5);   // 490-67.5us

    return(bus_flag); 
}

/*-------------------------------------------------------- 
*  д��������ݵ��¶�оƬDS18B20(����һ���ֽ�) 
*/ 
void ds18b20_write(INT8U dat) 
{ 
    INT8U count;

    // ÿ���ֽڹ�8λ��һ�η�һλ 
    for(count=0; count<8; count++) { 
        cli();                   // ��֤���Բ��ᷢ���ж�! 
        DQ_TO_0();               // ����1-wire����Ϊ�͵�ƽ 
        wait_us(2);              // about 2us 
         
        if(dat&0x01) DQ_TO_1();  // ����ת�����ȵ�λ���λ 
        else DQ_TO_0(); 
        dat >>= 1;               // ��һλ����׼�� 
         
        // 60us~120us(ʵ�ʲ��ܵ�120us, ��Ϊ�������Ҳ��ʱ����!) 
        wait_us(62);             // 62us 
         
        DQ_TO_1(); 
        sei();                   // �ָ�ϵͳ�ж� 
        wait_us(2);              // 2us 
    } 
}

/*--------------------------------------------------------- 
*  ���¶�оƬDS18B20�����û�����(����һ���ֽ�) 
*/ 
INT8U ds18b20_read(void) 
{ 
    INT8U count,dat;

    dat = 0x00;       // ���ݽ���׼�� 
     
    // ÿ���ֽڹ�8λ��һ����һλ 
    for(count=0; count<8; count++) { 
        cli();        // ��֤���Բ��ᷢ���ж�! 
         
        // ���������͵�������״̬�����ܴ���15us! 
        DQ_TO_0();    // ����1-wire����Ϊ�͵�ƽ(����������ͬ��) 
        wait_us(2);   // 2us 
        DQ_TO_1();    // ����1-wire����Ϊ�ߵ�ƽ(�ͷ�����) 
        wait_us(4);   // 4us         
        dat >>= 1; 
        if(DQ_status()) dat|=0x80;   // ��ȡ���ߵ�ƽ�����յ�λ���ո�λ 
         
        sei();        // �ָ�ϵͳ�ж� 
        wait_us(62);  // �������60us 
    } 
    return(dat); 
}

/*------------------------------------------------------- 
*     �ҵĵ�·��ֻ��һ������DS18B20�����Բ���Ҫ���������ID ʶ������֮�������¶�ת���������������û�Ӧ�ȴ����ٸ� ���룬���ܶ�����ε�ת��ֵ������DS18B20�������ֲ�涨�ġ���Ϊ�¶�ת������Ҫʱ�����!(^_^) 
*/ 
void convert_T(void) 
{ 
    if(ds18b20_reset()==SUCC) {  // �����λ�ɹ� 
        ds18b20_write(0xcc);     // ����������ʶ�� 
        ds18b20_write(0x44);     // �����¶�ת�� 
    } 
}

/*------------------------------------------------------- 
*  ��ȡת������¶�ֵ 
*  �Ҽٶ�DS18B20һ������ȷ�ģ�����û�з����й�״̬����������DS18B20�ӵ�·�а��¶����ó�����������ʱ��������Լ��� ����δ���! 
*/ 
INT16U read_T(void) 
{ 
    INT16U value=0; 
     
    if(ds18b20_reset()==SUCC) {  // �����λ�ɹ� 
        ds18b20_write(0xcc);     // ����������ʶ�� 
        ds18b20_write(0xbe);     // ���ݴ��� 
        value  = (INT16U)ds18b20_read();       // ���ֽ� 
        value += (INT16U)(ds18b20_read())<<8;  // ���ֽ� 
    } 
    return(value); 
}


#endif 
/* �ļ�ds18b20.c���� */

 

VRFREAKS ���и���ȫ����� 

PROJECT_59

UPDATED 9/Mar/2003 version 4.67 
The I2C driver is improved a bit.

1) HD44780 LCD with MULTIPLE LCD units 
2) UART, SINGLE OR DUAL 
3) SOFTWARE UART TTL & RS232 CAPABLE 
4) ANALOG TO DIGITAL CONVERTER 
5) HEXADECIMAL MATRIX KEYBOARD WITH EDITOR 
6) I2C MASTER and LM75 i2c temperature sensor driver 
7) 1 WIRE and DS18X20 with search rom function 
8) SRF08 & SRF04 ULTRASONIC RANGING MODULE 
9) DELAY FUNCTIONS IN ASM

 

 

 

 Asnake ������ 2004-6-20 10:31 AVR ��Ƭ�� �����ذ���    

�Ұ���������!��C�ļ����֣������Ŀ���ȥ���� 


/********************************************************************************************************* 
Title  :   C include file for the DS1820 library (ds1820.c) 
Author:    Chris efstathiou   
E-mail:    hendrix@otenet.gr 
Homepage:  ........................ 
Date:      2/Dec/2002 
Compiler:  AVR-GCC with AVR-AS 
MCU type:  any AVR MCU device 
Comments:  This software is FREE but without any warranty of any kind. 
*********************************************************************************************************/

/*  
    Although i could had written it in the new style, i prefer the old one for compatibility sake. 
*/

/********************************************************************************************************/ 
/*                                   PREPROCESSOR DIRECTIVES                                            */ 
/********************************************************************************************************/

#ifndef _IO_REG_MACRO_MODE_ 
#define _IO_REG_MACRO_MODE_  1       /* In case you have the new assignment mode io headers */ 
#endif

#ifndef  _SFR_ASM_COMPAT 
#define  _SFR_ASM_COMPAT     1       /* This is for GCC 3.2 */ 
#endif

 

#if AVRGCC_VERSION == 330

#include <avr/io.h> 
#include <avr/eeprom.h> 
#include <avr/pgmspace.h>

#else

#include <io.h> 
#include <eeprom.h> 
#include <pgmspace.h>

#endif

#include "one_wire.h" 
#include "ds18x20.h"  
#include "lcd_io.h"

 

/********************************************************************************************************/ 
/*                                   TYPE DEFINITIONS                                                   */ 
/********************************************************************************************************/

 

 

/********************************************************************************************************/ 
/*                                   LOCAL FUNCTION PROTOTYPES                                          */ 
/********************************************************************************************************/ 
static void send_selected_rom(void);

 

 

/********************************************************************************************************/ 
/*                                   GLOBAL VARIABLES                                                   */ 
/********************************************************************************************************/ 
unsigned char conversion_in_progress=0; 
unsigned char power_status=0; 
unsigned char ds18x20_rom_code[8]; 
signed int    temperature=0;


/********************************************************************************************************/ 
/*                                   LOCAL FUNCTIONS                                                    */ 
/********************************************************************************************************/ 
static void send_selected_rom(void) 
{ 
#if ONLY_1_DEVICE_ON_THE_BUS == 1 
  ow_read_rom(ds18x20_rom_code); 
  ow_command(OW_SKIP_ROM); 
#elif ONLY_1_DEVICE_ON_THE_BUS == 0 
unsigned char x=0;

  ow_command(OW_MATCH_ROM);   
  for(x=0; x<8; x++) { ow_put_byte(ds18x20_rom_code[x]); } 
#endif

return; 
}

/********************************************************************************************************/ 
/*                                   PUBLIC FUNCTIONS                                                   */ 
/********************************************************************************************************/


/*######################################################################################################*/ 
/*                                 DS1820 - DS18S20 FUNCTIONS                                           */ 
/*######################################################################################################*/

#if ONLY_1_DEVICE_ON_THE_BUS == 0 
void ds18x20_select_device(unsigned char *mem_array, unsigned char mem_type) 
{

unsigned char x=0;

if(mem_type == LOCATION_IS_RAM) 
{  
    for(x=0; x<8; x++) { *(ds18x20_rom_code+x)=(*(mem_array+x)); }  
} 
else if(mem_type == LOCATION_IS_FLASH) 
      {  
         for(x=0; x<8; x++) { *(ds18x20_rom_code+x)=PRG_RDB((const unsigned char*)(mem_array+x)); } 
      } 
else if(mem_type == LOCATION_IS_EEPROM) 
      { 
         for(x=0; x<8; x++) { ds18x20_rom_code[x]=eeprom_rb((unsigned int)(mem_array+x)); } 
      }

return; 
} 
#endif 
/*######################################################################################################*/

unsigned char ds18x20_get_power_status(void) 
{ 
    ow_reset(); 
    send_selected_rom(); 
    ow_put_byte(READ_POWER_SUPPLY); 
    power_status=ow_get_bit(); 
    ow_reset();


return(power_status); 
} 
/*######################################################################################################*/

signed int ds18x20_get_temp(unsigned char wait) 
{ 
signed char       bit=0; 
unsigned char     t_resolution=0, skip_convert_command=0;

 

/* First we must see if the DS18X20 is busy converting and if yes return the previus value. */ 
ow_reset(); 
send_selected_rom(); 
if(ow_get_bit()==0) { return(temperature); }

/* Now we need to know the DS18B20 resolution if there is one of course */ 
if(ds18x20_rom_code[0]==DS18B20) 
{ 
    t_resolution=ds18x20_get_reg(DS18X20_CONFIG); 
    t_resolution &= DS18X20_12_BIT; 
    if(t_resolution==DS18X20_12_BIT) { t_resolution=12; } 
    else if(t_resolution==DS18X20_11_BIT) { t_resolution=11; } 
    else if(t_resolution==DS18X20_10_BIT) { t_resolution=10; } 
    else{ t_resolution=9; } 
}

if(ds18x20_get_power_status() == 0 || wait)  
{ 
    ow_reset(); 
    send_selected_rom(); 
    ow_put_byte(CONVERT_T); 
    ow_pull_hard_dq(1); 
    if(t_resolution) { DELAY_MS( (DS18X20_CONVERSION_TIME_MS/(1<<(12-t_resolution))) ); } 
    else{DELAY_MS(DS18X20_CONVERSION_TIME_MS); } 
    ow_pull_hard_dq(0); 
    skip_convert_command=1; 
}

/* If we reached here conversion is complete so lets update the temperature value. */ 
temperature=0; 
ow_reset(); 
send_selected_rom(); 
ow_put_byte(READ_SCRATCHPAD);

/* read the Temperature registers, LSBit of LSByte first */ 
for(bit=0; bit<16; bit++) 
  { 
     if(ow_get_bit()) { temperature |= (1<<bit); } 
  }

if(ds18x20_rom_code[0]==DS18B20)  
{ 
     bit=(temperature&0x0F); 
     if(temperature < 0) { bit|=0xF0; } 
     bit=(bit*10)/16; 
     temperature=(((temperature/16)*10)+bit); 
} 
else{   
        bit=(temperature&0x01); 
        if(temperature < 0) { bit|=0xFE; } 
        bit=(bit*10)/2; 
        temperature=(((temperature/2)*10)+bit); 
    }

/* Send a new CONVERT_T command */ 
if(skip_convert_command==0) 
{ 
    ow_reset(); 
    send_selected_rom(); 
    ow_put_byte(CONVERT_T); 
} 
ow_reset();

 

return(temperature); 
} 
/*######################################################################################################*/

void ds18x20_get_scratchpad(unsigned char *mem_array) 
{ 
unsigned char x=0;

    ow_reset(); 
    send_selected_rom(); 
    ow_put_byte(READ_SCRATCHPAD); 
    for(x=0; x<9; x++) {*(mem_array+x)=ow_get_byte(); } 
    ow_reset();

return; 
} 
/*######################################################################################################*/

void ds18x20_set_reg(unsigned char reg, signed int value) 
{ 
unsigned char scratchpad[9]; 
unsigned char x=0, write_end_pos=3;

if(ds18x20_rom_code[0]==DS18B20) { write_end_pos=4; } 

   ds18x20_get_scratchpad(scratchpad); 
   scratchpad[reg]=value; 
   ow_reset(); 
   send_selected_rom(); 
   ow_put_byte(WRITE_SCRATCHPAD);

   /* write the byte, lsb first */ 
   for(x=2; x<=write_end_pos; x++) 
     { 
        ow_put_byte(scratchpad[x]); 
     }

   ow_reset();


return; 
} 
/*######################################################################################################*/ 
signed int ds18x20_get_reg(unsigned char reg) 
{ 
unsigned char scratchpad[9];

    ds18x20_get_scratchpad(scratchpad);


return(scratchpad[reg]); 
}

/*######################################################################################################*/ 
/*                                         T H E   E N D                                                */ 
/*######################################################################################################*/

 
 
 http://www.dzsc.com/dzbbs/20051117/200765193711703960.html
 
 http://www.dzsc.com/dzbbs/20051117/200765193711703960.html
 
����WinAVR��DS18B20Դ���򣬹��ο�
���ߣ�qjy_dali����Ŀ����Ƭ��

 ����WinAVR��DS18B20Դ���򣬹��ο�
/*
********************************************************
*   �ļ�:   ds18b20.c
*   ����:   AVR΢������ VS �¶�оƬDS18B20(TO-92)
*   ����:   WinAVR20040404(AVR-GCC)
*   ����:   ��������(qjy_dali)
*   E-mail: qjy_dali@sohu.com
*   ����:   6/02/2004
*   �汾:   1.41
*   ����:   �������ؿ��������ƻ��޸�������򣬵�����ע��
*          ����޸ġ������߲����������ĺ��������������
*          ȷ�ģ�����������(^_^)����������������ܵģ�����
*          ��ȷ��������ܵġ�֧��һ��GCC!!!
********************************************************
*/

#ifndef  _DS18B20_C_
#define  _DS18B20_C_


/*      �ҵ�һ���¶�оƬDS18B20�����ӵ�AVR΢������ATMEGA8
*  -16PI(PDIP28)��PD3(INT1)���ţ�������ֻ������PD3���ܶ�
*  û��ʹ���ж�INT1���ܡ�DS18B20(TO-92)���������£�
*  +-------------+-------------------------------------+
*  | Pin-1(GND)  | GND(ground)                         |
*  +-------------+-------------------------------------|
*  | Pin-2(DQ)   | ͨ��240ŷķ�ĵ������ӵ�ATMEGA8��    |
*  |             | PD3���ţ�ͬʱ��һ��3K�ĵ���������   |
*  |             | VCC(5V)��                           |
*  +-------------+-------------------------------------+
*  | Pin-3(VD)   | GND(ground)                         |
*  +-------------+-------------------------------------+
*      ˵��������Ȼ���Ҳ��õ���"�����Ե�"ģʽ������DS-
*  18B20�����ֲ��ϿɵĹ���ģʽ֮һ������240ŷķ���������
*  ��Ϊ�˷�ֹ��ȱ�ݵ��û�������DS18B20�Ŀ����ԡ����磬
*  ����û�û����ȷ����OC(���缫��·)��OD(©����·)�ṹȥ
*  ����DS18B20�����Ǵ����ѡ��������ʽ�ṹ����DS18B20����
*  ������"��Ű��"һ��ʱ���"������"(^_^)����Ȼ��240ŷķ��
*  ȡֵδ������ǡ���ģ�����߿��Լ�ȥ�Ż�������Ҫ�������ϸ
*  �Ķ������ֲᡣ
*
*      ���⣬�Ҳ�����DS18B20��Ĭ�Ͼ���(12λ)����δ�޸ģ���
*  Ҳû��ʹ�������������ܡ������֮����ֻ��һ���򵥵Ķ�ȡ�¶�
*  ��ʵ�����û������Լ�ȥ�Ľ����Լ�ȥ�о������ֲ�(�Ҳ�δ��ȫ
*  ����ֻ�����뿴��һ��� ^_^ )�������ҿ��Կ϶�һ�㣬�����
*  ������ʵ������!���ҳɹ��ض�ȡ���¶�ֵ!
*
*      ��ע�������������DS18B20�ģ�������AVR�ķ���Ĵ���
*  ����������˿ڼĴ���! ͬʱԤ��������˿ڼĴ�����д��0��
*  ��ʵ�����൱��һ����̬�ţ�ֻ�������뱻�ӵأ�ʹ������һ
*  ��OC�ţ�ʹ�ܶ˳������OC�ŵ�ʵ������!
*
*      1-wire���ߵĵ���������I2C�������ƣ��������빦�ܣ���
*  �ԣ������ϵ���һ�豸�����ں��ʵ�ʱ��ǿ���������ߣ���������
*  Ҫ���ָߵ�ƽ���������ÿһ���豸���ͷ������ߡ������������
*  ��DQ_TO_1()����ֻ���ͷ������ߣ�������˵����һ����ǿ������
*  ���ߵ�ƽ�����ߵĸߵ�ƽ������������ʵ�ֵġ�
*/
#define  DQ_18B20       (1<<3)                // PD3
#define  DQ_TO_0()      (DDRD |=  DQ_18B20)   // PD3='0'
#define  DQ_TO_1()      (DDRD &= ~DQ_18B20)   // PD3='float'
#define  DQ_status()    (PIND & DQ_18B20)     // read PD3 pin

/*     �����������AVR΢��������ʱ��Ƶ��! �ر�ע�⣺Ƶ��
* ����ĵ�λ��MHz! ������ʹ�ø�����! ������ľ�����12MHZ��
* ��Ӧ��д��12.0000��12.0֮�ࡣ
*     �ҵ�ʵ���·�ľ����ǣ�11.0592MHZ.html">11.0592MHZ
*/
#ifndef  CPU_CRYSTAL
#define  CPU_CRYSTAL    (11.0592)
#endif

/*     �����WinAVRϵͳ�ṩ����ʱͷ�ļ�"delay.h"�����и���
*  ������ʱģ�飬����16λ���Ǹ�(16-bit count, 4 cycles/l-
*  oop.)��ϸ���뿴���ͷ�ļ���
*/
#define  wait_us(us)\
    _delay_loop_2((INT16U)((us)*CPU_CRYSTAL/4))

/*---------------- ����ԭ������ ------------------*/
// 1����ʼ��ģ��
void   ds18b20_config(void);       // ���ö˿�

// 3������ģ��
BOOL   ds18b20_reset(void);        // ��λDS18B20
void   ds18b20_write(INT8U dat);   // д�ֽڵ�DS18B20
INT8U  ds18b20_read(void);         // ���ֽڴ�DS18B20

// 2��Ӧ��ģ��
void   convert_T(void);            // �����¶�ת��
INT16U read_T(void);               // ��ȡת��ֵ


/*-------------------------------------------------------
*  ����(ʹ��)AVR��DS18B20�Ľӿ�
*/
void ds18b20_config(void)
{
    DDRD  &= ~DQ_18B20;   // ����ģʽ(�ϵ�ʱΪ�ߵ�ƽ)
    PORTD &= ~DQ_18B20;   // ���������д0���Ժ��ٸ���
}

/*-------------------------------------------------------
*    ��λ1-wire���ߣ���̽���Ƿ����¶�оƬDS18B20(TO-92
*  ��װ)���������ϣ��з���SUCC��û�з���FAIL
*/
BOOL ds18b20_reset(void)
{
    BOOL bus_flag;

    DQ_TO_0();      // ����1-wire����Ϊ�͵�ƽ(ռ������)...

    /* �����ӳ�480us~960us, ��Ӳ��������أ���Ӧ������ѡСֵ(480us)��
       �Ѷ�������ϵͳ(�������ӳ��ڼ䷢���жϵ����ӳٱ䳤)��
     */
    wait_us(490);   // 490us

    cli();          // �������ʱ��Ҫ��Ƚ��ϸ�Ϊ������������ж�
    DQ_TO_1();      // ����1-wire����Ϊ�ߵ�ƽ(�ͷ�����)
    
    /* ������������ɱ���������õģ������������MCU������ʱ��ʱ����ģ�
       ���Բ���ռ���û�MCU��ʱ�䣬���ص���(����ǰ��ĺ���Ϳ���ȷ����)
     */
    wait_us(67.5);  // ���ʱ��: 60us+7.5us!(æ��ʱ��ֻ��һ�ֲ���)
    
   