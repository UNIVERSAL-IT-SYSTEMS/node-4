/*
* @history
* @modified by Lu Weihui(luweihui163@163.com) and He Yaxi(yaxihe@163.com), TongJi 
*  University on 2010.07.15
*  - compiled passed. tested ok.
*/

#include  "rtl_signal_fft.h"

// ����ú꽫�Խ�����й�һ���������򲻽��й�һ���������ǽ�����ܻ����
#define CONFIG_UNITARY


#define PI 3.1415926535897932384626433832795


// ���������õı��Ŵ���1024����256��FFTʱ�ã�
const short int m_cos_table[LENGTH/2]=
{
    1024,1024,1023,1021,1019,1016,1013,1009,1004,999,

    993,987,980,972,964,955,946,936,926,915,

    903,891,878,865,851,837,822,807,792,775,

    759,742,724,706,688,669,650,630,610,590,

    569,548,526,505,483,460,438,415,392,369,

    345,321,297,273,249,224,200,175,150,125,

    100,75,50,25,0,-25,-50,-75,-100,-125,

    -150,-175,-200,-224,-249,-273,-297,-321,-345,-369,

    -392,-415,-438,-460,-483,-505,-526,-548,-569,-590,

    -610,-630,-650,-669,-688,-706,-724,-742,-759,-775,

    -792,-807,-822,-837,-851,-865,-878,-891,-903,-915,

    -926,-936,-946,-955,-964,-972,-980,-987,-993,-999,

    -1004,-1009,-1013,-1016,-1019,-1021,-1023,-1024
};

// ���������õı��Ŵ���1024����256��FFTʱ�ã�
const short int m_sin_table[LENGTH/2]=
{
    0,25,50,75,100,125,150,175,200,224,

    249,273,297,321,345,369,392,415,438,460,

    483,505,526,548,569,590,610,630,650,669,

    688,706,724,742,759,775,792,807,822,837,

    851,865,878,891,903,915,926,936,946,955,

    964,972,980,987,993,999,1004,1009,1013,1016,

    1019,1021,1023,1024,1024,1024,1023,1021,1019,1016,

    1013,1009,1004,999,993,987,980,972,964,955,

    946,936,926,915,903,891,878,865,851,837,

    822,807,792,775,759,742,724,706,688,669,

    650,630,610,590,569,548,526,505,483,460,

    438,415,392,369,345,321,297,273,249,224,

    200,175,150,125,100,75,50,25
};

// ����λ���õ�ֵ
LEN_TYPE m_bit_reverse[LENGTH];  



/********************************************************************
�������ܣ���ָ�����ȵĶ����������Ӧ��λ����ֵ��
��ڲ�����N��Ҫ�����ֵ��L��bit����
��    �أ�N��λ����ֵ��
��    ע���ޡ�
********************************************************************/
LEN_TYPE _do_bit_reverse(LEN_TYPE N, LEN_TYPE L)
{
    LEN_TYPE Temp1,Temp2;
    LEN_TYPE i;
    for(i=0;i<L/2;i++)
    {
        Temp1=0;
        Temp2=0;
        if(N&(1<<i))
            Temp1=1;
        if(N&(1<<(L-1-i)))
            Temp2=1;
        N&=~(1<<i);
        N&=~(1<<(L-1-i));
        N|=(Temp2<<i);
        N|=(Temp1<<(L-1-i));
    }
    return N;
}
/////////////////////////End of function/////////////////////////////

/********************************************************************
�������ܣ���ʼ��λ����ֵ���飬��FFT����ʱ����á�
��ڲ������ޡ�
��    �أ��ޡ�
��    ע�����������ȫ�ֱ���m_bit_reverse�����С�
********************************************************************/
void InitBitRev(void)
{
    LEN_TYPE i;
    for(i=0;i<LENGTH;i++) //��λ��ת
    {
        m_bit_reverse[i]=_do_bit_reverse(i,bL);
    }
}
/////////////////////////End of function/////////////////////////////

/********************************************************************
�������ܣ����������ݽ��е�����
��ڲ�����pIn��Ҫ��������ݻ�������ַ��
��    �أ��ޡ�
��    ע���ڵ���FftExe֮ǰӦ�õ��øú��������ݽ��е�����
********************************************************************/
void FftInput(IN_TYPE *pIn)
{
    LEN_TYPE i;
    IN_TYPE Temp;
    for(i=0;i<LENGTH;i++)
    {
        if(m_bit_reverse[i]>i)  //�����λ���ԭ����򽻻�
        {
            Temp=pIn[i];
            pIn[i]=pIn[m_bit_reverse[i]];
            pIn[m_bit_reverse[i]]=Temp;
        }
    }
}
/////////////////////////End of function/////////////////////////////

/********************************************************************
�������ܣ�����FFT���㡣
��ڲ�����pIn���������ݵĻ�������pRe������ʵ���Ļ�������pIm�������鲿�Ļ�������
��    �أ��ޡ�
��    ע���ڵ��øú���֮ǰӦ�õ���FftInput���������ݽ��е�����
********************************************************************/
void FftExe(IN_TYPE *pIn, OUT_TYPE *pRe, OUT_TYPE *pIm)
{
    LEN_TYPE i,j;
    LEN_TYPE BlockSize;
    OUT_TYPE tr,ti;
    LEN_TYPE OffSet1,OffSet2;


    LEN_TYPE OffSet0;


    long c,s;

    //�ȼ���2���
    for(j=0;j<LENGTH;j+=2)
    {
        tr=pIn[j+1];
        pRe[j+1]=(pIn[j]-tr);
        pIm[j+1]=0;
        pRe[j]=(pIn[j]+tr);
        pIm[j]=0;
    }

    for(BlockSize=4;BlockSize<=LENGTH;BlockSize<<=1) //��һ������
    {
        for(j=0;j<LENGTH;j+=BlockSize)
        {
            for(i=0;i<BlockSize/2;i++)
            {

                OffSet0=LENGTH/BlockSize*i;
                c=m_cos_table[OffSet0];
                s=m_sin_table[OffSet0];

                OffSet1=i+j;
                OffSet2=OffSet1+BlockSize/2;
                tr=(OUT_TYPE)((c*pRe[OffSet2]+s*pIm[OffSet2])/1024);
                ti=(OUT_TYPE)((c*pIm[OffSet2]-s*pRe[OffSet2])/1024);
#ifdef CONFIG_UNITARY  //���Ҫ�Խ����һ��������ÿ������Ҫ����2
                pRe[OffSet2]=(pRe[OffSet1]-tr)/2;
                pIm[OffSet2]=(pIm[OffSet1]-ti)/2;
                pRe[OffSet1]=(pRe[OffSet1]+tr)/2;
                pIm[OffSet1]=(pIm[OffSet1]+ti)/2;
#else
                pRe[OffSet2]=(pRe[OffSet1]-tr);
                pIm[OffSet2]=(pIm[OffSet1]-ti);
                pRe[OffSet1]=(pRe[OffSet1]+tr);
                pIm[OffSet1]=(pIm[OffSet1]+ti);
#endif
            }
        }
    }
#ifdef CONFIG_UNITARY
    pRe[0]/=2;
    pIm[0]/=2;
#endif
}

/////////////////////////End of function/////////////////////////////

/********************************************************************
�������ܣ�������ģ��
��ڲ�����x������ʵ����y������ʵ����wamp��ģ��
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/

void getamp(OUT_TYPE x[],OUT_TYPE y[],OUT_TYPE wamp[],short int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        wamp[i]=(OUT_TYPE)sqrt(x[i]*x[i]+y[i]*y[i]);//<<2;//������Ŵ�
    }

}

/////////////////////////End of function/////////////////////////////


/********************************************************************
�������ܣ������������Ԫ���±ꡣ
��ڲ�����x�����飻len��������Ԫ�ظ�����
��    �أ����������Ԫ���±ꡣ
��    ע���ޡ�
********************************************************************/

short int getimax(OUT_TYPE x[],short int len)
{
    short int imax=0,len2=len/2,i;
    for(i=0;i<len2;i++)  if(x[i]>x[imax]) imax=i;

    return imax;
}

/////////////////////////End of function/////////////////////////////

/********************************************************************
�������ܣ��˲�����
��ڲ�����in��Ҫ�˲������飻np��������Ԫ�ظ�����cutoff����ֹƵ�ʣ�
timebase������Ƶ�ʡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/

void RCFilter(IN_TYPE * in, short int np,float cutoff,float timebase)
{	
    //in[] contains the data to be filtered
    //np is number of data points(=dimension of in[])
    //cutoff is cut-off frequency in Hz
    //timebase is sample interval in seconds


    short i;
    float a,b,y;

    a=2-cos(2*PI*cutoff*timebase);

    if(a!=1)
    {
        a=a-sqrt(a*a-1);
        b=1-a;
        y=b*in[0];
        for(i=0;i<np;i++) in[i]=y=b*in[i]+a*y;
        y*=b;
        for(i=np-1;i>=0;i--) in[i]=y=b*in[i]+a*y;
    }

}

/////////////////////////End of function/////////////////////////////

/********************************************************************
�������ܣ��õ�FFT��Ƶ����Ŷ�Ӧ��Ƶ�ʡ�
��ڲ�����t������Ƶ�ʣ�n������������i��Ƶ����š�
��    �أ�Ƶ����Ŷ�Ӧ��Ƶ�ʡ�
��    ע���ޡ�
********************************************************************/

float getfre(float t,short int n,short int i)
{
    return i/(t*n);
}

/////////////////////////End of function/////////////////////////////

/********************************************************************
�������ܣ��������򣩲���FFT����
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
/*
#define T 0.05 //��������


void main(void)
{

int i=0,k=0;

IN_TYPE InBuffer1[LENGTH];

OUT_TYPE Re[LENGTH];
OUT_TYPE Im[LENGTH];

short int imax;

for(i=0;i<LENGTH;i++)
{
InBuffer1[i]=(IN_TYPE)(900*sin(i));
}

//RCFilter(InBuffer1,LENGTH,1,T);

InitBitRev();  //��ʼ��FFT�õ�λ��ת�õı��
FftInput(InBuffer1);       //λ����
FftExe(InBuffer1,Re,Im);   //��FFT����


getamp(Re,Im,Re,LENGTH);

for(i=0;i<LENGTH;i++) cout<<Re[i]<<setw(10);//���FFT��Ƶ��
imax=getimax(Re,LENGTH);

float fre;
fre=getfre(T,LENGTH,imax);

cout<<endl<<imax<<endl;//������ֵ���
cout<<fre<<endl; //���FFT�����ֵ��ӦƵ��
}

*/
