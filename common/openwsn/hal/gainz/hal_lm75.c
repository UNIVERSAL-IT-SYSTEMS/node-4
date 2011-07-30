http://www.eefocus.com/billbot501/blog/11-03/206432_30946.html
source code can be downloaded

LM75A��һ������I2C�ӿڵ��¶ȴ�������������-55��+125���¶ȷ�Χ�ڽ��¶�ֱ��ת��Ϊ�����źţ���ʵ��0.125�ľ��ȡ�PIC32����ͨ��I2C����ֱ�Ӷ�ȡ���ڲ��Ĵ����е����ݣ�����ͨ��I2C��4�����ݼĴ������в��������ò�ͬ�Ĺ���ģʽ��LM75A��3����ѡ���߼���ַ�ܽţ�ʹ��ͬһ�����Ͽ�ͬʱ����8����������������ַ��ͻ��
LM75A��PIC32����������I2C���ߵ���ʽ����ͼ3-11��ʾ����������Ҫ���������裬��Ϊͨ�ſ�ʼ֮ǰ��I2C���߱�����л��߲�æ������ζ�������ϵ����������������ͷ�SCL��SDA�ߣ�SCL��SDA�߱����ߵ������������ߣ���������ȡ10K����.


http://www.eefocus.com/x10031987/blog/11-04/207868_05130.html

LM75�¶ȴ����������� 2011-04-01 22:23
 �����ղ�
 ת������
 ������
 ������
 ����΢��
 �Ѻ�����
 �ٶ��ղ�
 �ȸ��ղ�
 qq��ǩ
 ����
 �Խ���
 Facebook
 Twitter
 Digg
 Yahoo!Bookmarks
/***********************************************************/
LM75�¶ȴ�������ʹ��IIC�ӿڣ���д��ת��ʱ��̣��¶ȼ����
����Ҫ�ȴ�ͳ��DS18B20�ߣ��ʺ����¿ع����Ȳ���������ϵͳ
�����ʹ��AVR��Ƭ���������¶ȴ�����DS75��LM75ϵ��Դ���룬
ʱ��7M��32��Ƶ���¶ȴ�������F�˿ڣ�9λ�¶�ת�����ȡ�
BY Johnny,2011.3.23
************************************************************/
#define LM75_SDA 3
#define LM75_SDL 2
/***********************************************************
��������delayus
��  �ã���
��  ������
����ֵ����
��  ������ʱ
��  ע��
/***********************************************************/
void delayus(unsigned char del)
{
         while(del--);
}
/***********************************************************
��������init_lm75
��  �ã���
��  ������
����ֵ����
��  ������ʼ��
��  ע��
/***********************************************************/
void init_lm75(void)
{
         SETBIT(DDRF,LM75_SDA);              //only output
         SETBIE(DDRF,LM75_SDL);
 
         SETBIT(PORTF,LM75_SDA);
         delayus(10);
         SETBIT(PORTF,LM75_SDL);
         delayus(10);
         CLEARBIT(PORTF,LM75_SDA);
         delayus(20);
         CLEARBIT(PORTF,LM75_SDL);
         delayus(20);
}
 
/***********************************************************
��������sendbyte_lm75
��  �ã���
��  ����buf
����ֵ���ֽڳ���
��  ��������һ���ֽڣ��ɹ�����0x91�����򷵻�0
��  ע��
/***********************************************************/
unsigned char sendbyte_lm75 (unsigned char buf)
{
         unsigned char i=0;
         SETBIT(DDRF,LM75_SDA); //only output
         SETBIE(DDRF,LM75_SDL);
         for(i=8;i>0;i--)
         {
                   CLEARBIT(PORTF,LM75_SDL);               //sdl low
                   delayus(20);
                   if(buf&0x80)                                                  //bit7==1
                             SETBIT(PORTF,LM75_SDA);
                   else  CLEARBIT(PORTF,LM75_SDA);    //bit7==0
                   buf<<=1;
                   SETBIT(PORTF,LM75_SDL);
                   delayus(20);
         }
         CLEARBIT(PORTF,LM75_SDL);                //put sdl low
         delayus(20);                                                    //wait for ack
         SETBIT(PORTF,LM75_SDA);
         delayus(5);
         CLEARBIT(DDRF,LM75_SDA);     //sdl input
         SETBIT(PORTF,LM75_SDL);
                   delayus(20);
         if(GETBIT(PINF,LM75_SDA))         //fail
         {
                   SETBIT(DDRF,LM75_SDL);
                   CLEARBIT(PORTF,LM75_SDL);
                   return 0;
         }
         else
         {
                   SETBIT(DDRF,LM75_SDL);
                   CLEARBIT(PORTF,LM75_SDL);
                   return 0x91;
         }
}
/***********************************************************
��������getbyte_lm75
��  �ã���
��  ������
����ֵ�������ֽ�
��  ��������һ���ֽ�
��  ע��
/***********************************************************/
unsigned char getbyte_lm75(void)
{
         unsigned char i=0,buf=0;
         CLEARBIT(DDRF,LM75_SDA);
         SETBIE(DDRF,LM75_SDL);
         for(i=0;i<8;i++)
         {
                   CLEARBIT(PORTF,LM75_SDL);
                   delayus(20);
                   SETBIT(PORTF,LM75_SDL);
                   delayus(10);
                   buf<<=1;
                   if(GETBIT(PINF,LM75_SDA))
                   {
                            buf+=1;
                            delayus(10);
                   }
                   CLEARBIT(PORTF,LM75_SDL);
         }
         return buf;
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
/***********************************************************
��������stop_lm75
��  �ã���
��  ������
����ֵ����
��  ����ֹͣ
��  ע��
/***********************************************************/
void stop_lm75(void)
{
         SETBIT(DDRF,LM75_SDA);
         SETBIE(DDRF,LM75_SDL);
         CLEARBIT(PORTF,LM75_SDA);
         delayus(20);
         SETBIT(PORTF,LM75_SDL);
         delayus(20);
         SETBIT(PORTF,LM75_SDA);
         delayus(20);
}
/***********************************************************
��������ack_lm75
��  �ã���
��  ����ack
����ֵ����
��  ����Ӧ��
��  ע��
/***********************************************************/
void ack_lm75(unsigned char ack)
{
         SETBIT(DDRF,LM75_SDA);
         SETBIE(DDRF,LM75_SDL);
 
         if(ack)      CLEARBIT(PORTF,LM75_SDA);
         else  SETBIT(PORTF,LM75_SDA);
 
         delayus(8);
         SETBIT(PORTF,LM75_SDL);
         delayus(20);
         CLEARBIT(PORTF,LM75_SDL);
         delayus(10);
}
 
 
 
/***********************************************************
��������temperature_lm75
��  �ã���
��  ������
����ֵ���ֽڳ���
��  �����¶�ֵ
��  ע��
/***********************************************************/
unsigned char temperature_lm75(void)
{
         unsigned char temp[2];
         unsigned char i;
 
         init_lm75();
         sendbyte_lm75(0x91);
         temp[1]=getbyte_lm75();
         ack_lm75(1);
         temp[0]=getbyte_lm75();
         ack_lm75(0);
         stop_lm75();
 
         if(temp[1]&0x80)                        //temperature was minus
                   temp[1]=~temp[1]+0x80;
         return temp[1];
}
 