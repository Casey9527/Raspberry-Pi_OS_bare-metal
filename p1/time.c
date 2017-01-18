//
// time library
//

#include "time.h"



unsigned int gettime( )
{
    unsigned int lo = GET32( LS );
    unsigned int hi = GET32( MS );
    unsigned int re = ( lo>>16 ) | ( hi<<16 );
    return re;
}

unsigned int timediff( unsigned int now, unsigned int then )
{
    return ( now - then );
}

void wait( unsigned int time )
{
    PUT32(PRESCALE,0x80000000);
    unsigned int then = gettime();
    unsigned int now;
    do
    {
        now = gettime();
    }while( timediff( now , then ) < time );
    //}while( timediff( now, then ) < time );
}

