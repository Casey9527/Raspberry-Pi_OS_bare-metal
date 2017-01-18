//
// hello, world!!!
//

#include "os.h"


extern void init_timeoutq( void );
extern int bring_timeoutq_current( void );
extern void create_timeoutq_event(int timeout, int repeat, pfv_t function, unsigned int data);
extern int handle_timeoutq_event( void );

/*
    if( ep->go == blink_led )
    {
        pfv_t foo = blink_led;
        while(1)
        {
            (*foo)(data);
        }
    }

*/


void
notmain()
{
	int timeout;

	flash_led(1, RED|GRN, 4);

	init_timeoutq();
    pfv_t faddr;
    faddr = &blink_led;

	create_timeoutq_event( ONE_SEC, 5 * ONE_SEC, blink_led, RED );
	create_timeoutq_event( 4 * ONE_SEC, 5 * ONE_SEC, blink_led, GRN );
	create_timeoutq_event( 7 * ONE_SEC , 5 * ONE_SEC, blink_led, GRN | RED);

	while (1) 
	{
		if (handle_timeoutq_event()) {
            //blink_led( RED );
			continue;
		}
		timeout = bring_timeoutq_current();
		wait(timeout);
	}

}
