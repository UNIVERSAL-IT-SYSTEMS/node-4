


TiTimeDescriptor


typedef struct{
  
}TiCalendarTime;



�����ں�ʱ����ص����ݽṹ 
�ڱ�׼C/C++�У����ǿ�ͨ��tm�ṹ��������ں�ʱ�䣬tm�ṹ��time.h�еĶ������£� 
#ifndef _TM_DEFINED  
struct tm {  
int tm_sec; /* �� �C ȡֵ����Ϊ[0,59] */  
int tm_min; /* �� - ȡֵ����Ϊ[0,59] */  
int tm_hour; /* ʱ - ȡֵ����Ϊ[0,23] */  
int tm_mday; /* һ�����е����� - ȡֵ����Ϊ[1,31] */  
int tm_mon; /* �·ݣ���һ�¿�ʼ��0����һ�£� - ȡֵ����Ϊ[0,11] */  
int tm_year; /* ��ݣ���ֵ����ʵ����ݼ�ȥ1900 */  
int tm_wday; /* ���� �C ȡֵ����Ϊ[0,6]������0���������죬1��������һ���Դ����� */  
int tm_yday; /* ��ÿ���1��1�տ�ʼ������ �C ȡֵ����Ϊ[0,365]������0����1��1�գ�1����1��2�գ��Դ����� */  
int tm_isdst; /* ����ʱ��ʶ����ʵ������ʱ��ʱ��tm_isdstΪ������ʵ������ʱ�Ľ���tm_isdstΪ0�����˽����ʱ��tm_isdst()Ϊ����*/  
};  
#define _TM_DEFINED  
#endif 
ANSI C��׼��ʹ��tm�ṹ������ʱ���ʾΪ�ֽ�ʱ��(broken-down time)�� 
������ʱ�䣨Calendar Time����ͨ��time_t������������ʾ�ģ���time_t��ʾ��ʱ�䣨����ʱ�䣩�Ǵ�һ��ʱ��㣨���磺1970��1��1��0ʱ0��0�룩����ʱ����������time.h�У�����Ҳ���Կ���time_t��һ������������ 
#ifndef _TIME_T_DEFINED  
typedef long time_t; /* ʱ��ֵ */  
#define _TIME_T_DEFINED /* �����ظ����� time_t */  
#endif 
��ҿ��ܻ�������ʣ���Ȼtime_tʵ�����ǳ����ͣ���δ����ĳһ�죬��һ��ʱ��㣨һ����1970��1��1��0ʱ0��0�룩����ʱ��������������ʱ�䣩�����˳��������ܱ�ʾ�����ķ�Χ��ô�죿��time_t�������͵�ֵ��˵��������ʾ��ʱ�䲻������2038��1��18��19ʱ14��07�롣Ϊ���ܹ���ʾ����Զ��ʱ�䣬һЩ����������������64λ��������������������������ʱ�䡣����΢����Visual C++�в�����__time64_t������������������ʱ�䣬��ͨ��_time64()�������������ʱ�䣨������ͨ��ʹ��32λ�ֵ�time()�������������Ϳ���ͨ�����������ͱ���3001��1��1��0ʱ0��0�루��������ʱ��㣩֮ǰ��ʱ�䡣 
��time.hͷ�ļ��У����ǻ����Կ���һЩ���������Ƕ�����time_tΪ�������ͻ򷵻�ֵ���͵ĺ����� 
double difftime(time_t time1, time_t time0);  
time_t mktime(struct tm * timeptr);  
time_t time(time_t * timer);  
char * asctime(const struct tm * timeptr);  
char * ctime(const time_t *timer); 
���⣬time.h���ṩ�����ֲ�ͬ�ĺ���������ʱ�䣨һ����time_t��ʾ��������ת��Ϊ����ƽʱ�����İ�������ʱ����ֿ���ʾ��ʱ���ʽtm�� 
struct tm * gmtime(const time_t *timer);  
struct tm * localtime(const time_t * timer); 
ͨ������MSDN�����ǿ���֪��Microsoft C/C++ 7.0��ʱ����ֵ��time_t�����ֵ���Ǵ�1899��12��31��0ʱ0��0�뵽��ʱ��������������������������ְ汾��Microsoft C/C++�����в�ͬ�汾��Visual C++���Ǽ���Ĵ�1970��1��1��0ʱ0��0�뵽��ʱ����������������� 



���뵽rtl_timeģ���


TiCalendarTime

typedef struct{
}TiCalendarTime;

����ѹ��BCD��洢
[B0..B9]

B0: ����
B1-B2 Year
B3 M
B4 D
B5 HH
B6 MM
B7 SS
B8 ms
B9 ms
��ע�⣬���ִ洢����ֻ��֧�ֵ�ms
Ϊ���ڴ��ڴ���ʱ���㣬�����ַ�ʽ�У�Ҫ������byte���ǿɼ��ַ�������������ʾ������������
���byte����Ҫ�跨��Ϊ�����ֽ�����
