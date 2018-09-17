#ifndef __DELAY_H__
#define __DELAY_H__

#endif //#ifndef __DELAY_H__

#ifdef __DELAY_C__
#define __DELAY_EXTERN__
#else
#define __DELAY_EXTERN__ extern
#endif

__DELAY_EXTERN__ void delay(unsigned int time);
