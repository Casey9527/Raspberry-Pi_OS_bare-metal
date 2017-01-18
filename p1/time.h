//
// time.h
//
// information regarding the time library
//

#ifndef _TIME_H_
#define _TIME_H_

#define LS 0x4000001c
#define MS 0x40000020
#define PRESCALE 0x40000008
#define	ONE_SECOND	500		// you define this however you want/need


extern void PUT32( unsigned int, unsigned int );
extern unsigned int GET32( unsigned int );

extern unsigned int gettime( void );
extern unsigned int timediff( unsigned int now, unsigned int then );
extern void wait( unsigned int time );

#endif
