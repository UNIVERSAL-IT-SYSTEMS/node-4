#ifndef _RTL_SIGNAL_FFT_4324_
#define _RTL_SIGNAL_FFT_4324_

/*
 * @history
 * @modified by Lu Weihui(luweihui163@163.com) and He Yaxi(yaxihe@163.com), TongJi 
 *  University on 2010.07.15
 *  - compiled passed. tested ok.
 */

#include <math.h>


//������FFT�ĵ���
#define LENGTH 256
//������ô����FFT��Ҫ���ٸ�������λ
//bL=log2(LENGTH)
#define bL 8



#define IN_TYPE  short int
#define OUT_TYPE int
#define LEN_TYPE long int



// todo: new interface
// void fft( IN_TYPE *pIn, OUT_TYPE *pRe, OUT_TYPE *pIm );
// void ifft
// void rcfilter(IN_TYPE * in, short int np,float cutoff,float timebase);


void InitBitRev(void);
void FftInput(IN_TYPE *pIn);
void FftExe(IN_TYPE *pIn, OUT_TYPE *pRe, OUT_TYPE *pIm);
void getamp(OUT_TYPE x[],OUT_TYPE y[],OUT_TYPE wamp[],short int len);
short int getimax(OUT_TYPE x[],short int len);
float getfre(float t,short int n,short int i);

void RCFilter(IN_TYPE * in, short int np,float cutoff,float timebase);

#endif
