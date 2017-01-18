//
// hello, world!!!
//

#include "time.h"
#include "led.h"

void
notmain()
{
	init_led();
	wait( ONE_SECOND * 10 );
	unsigned int flag = 0;
	while (1) {
		wait( ONE_SECOND );
		switch_led(flag++);
		wait( ONE_SECOND );
		switch_led(flag++);
	}
}