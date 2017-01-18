//
// time library
//

#include "time.h"

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

#define LS	0x4000001C
#define MS	0x40000020
#define PRESCALER	0x40000008

unsigned int
gettime( )
{
	// your code goes here
	unsigned int lo = GET32( LS );
	unsigned int hi = GET32( MS );
	unsigned int re = ( lo >> 16) | ( hi << 16);
	return re;
}

unsigned int
timediff( unsigned int now, unsigned int then )
{
	// your code goes here
	return (now - then);
}

void
wait( unsigned int time )
{
	// your code goes here
	PUT32(PRESCALER, 0x80000000);
	unsigned int then, now;

	then = gettime();
	while (1) {
		now = gettime();
		if (timediff(now, then) >= time)	break;
	}
}

