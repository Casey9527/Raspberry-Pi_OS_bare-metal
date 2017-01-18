//
// timeout queue
//

#include "os.h"
#include "llist.h"
#include <stdio.h>


struct event {
	LL_PTRS;
	int timeout;
	int repeat_interval;
	pfv_t go;
	unsigned int data;
};

#define MAX_EVENTS	8
#define EV_NULL ( struct event * ) (LL_NULL)
struct event queue[ MAX_EVENTS ];
void insert_timeoutq_event( struct event * ep);

// list anchors -- important, but ignore them; they are never used directly
llobject_t TQ;
llobject_t FL;

struct event *timeoutq;
struct event *freelist;

unsigned int then_usec;

unsigned int time_now = 0;
unsigned int now_usec()
{
    time_now += 10;
    printf("time now = %u\n\n",time_now );
    return time_now; 
}

void wait( unsigned int timeout )
{
    printf("waited for %u amount of time\n",timeout);
    time_now += (int) timeout;
    return;
}
//
// sets up concept of local time
// initializes the timeoutq and freelist
// fills the freelist with entries
// timeoutq is empty
//
void
init_timeoutq()
{
	int i;

	//TODO
	//then_usec = now_usec();

	timeoutq = (struct event *)&TQ;
	LL_INIT(timeoutq);
	freelist = (struct event *)&FL;
	LL_INIT(freelist);

	for (i=0; i<MAX_EVENTS; i++) {
		struct event *ep = &queue[i];
		LL_PUSH(freelist, ep);
	}

	return;
}
//
// account for however much time has elapsed since last update
// return timeout or MAX
//
int bring_timeoutq_current()
{
    int wait_time = MAX_SLEEP_INTERVAL;
    struct event * ev = ( struct event * ) LL_TOP( timeoutq );
    if( EV_NULL == ev )
        return wait_time;

    wait_time = ( wait_time > ( ev->timeout ) ) ? ( ev->timeout ) : wait_time ;

	return wait_time;
}

//
// dump timeout queue 
//
void dump_timeoutq()
{
	printf("\n\n\n=================\nenter function\n================\n");
	struct event * it;
	LL_EACH(timeoutq,it,struct event )
	{
		if( it != NULL )
			printf("timeout %d\n",it->timeout);
		else 
			printf("NULL!\n");
	}
	printf("=================\nexit function\n================\n\n\n");
}

//
// get a new event structure from the freelist,
// initialize it, and insert it into the timeoutq
// 
void
create_timeoutq_event(int timeout, int repeat, pfv_t function, unsigned int data)
{
    // Firstly, assert if we have available event
    struct event *ep = ( struct event * ) LL_POP( freelist );
    if( ep == EV_NULL )
        return ;
    // If so, fill the event
    ep->timeout = timeout;
    ep->repeat_interval = repeat;
    ep->go = function;
    ep->data = data;

    insert_timeoutq_event( ep );
/*
	// Try to insert it according to timeout and timeoutq
	struct event * it;
    short is_pushed = 0;
	
    // Judge if we gonna insert it before a current event in timeque
	LL_EACH(timeoutq,it,struct event )
	{
		if( it != EV_NULL )
		{
			if( ( it->timeout ) > ( ep->timeout ) )
			{
                it->timeout -= ep->timeout;
                LL_L_INSERT( it, ep );
                is_pushed = 1;
				printf("left insert \n");
			}
            else
            {
                ep->timeout -= it->timeout;
            }
		}
	}
    
    // If not insert it left to the header
    if( is_pushed == 0 )
    {
        LL_APPEND(timeoutq, ep);
        printf("tail insert\n");
    }
*/
	

}



//
// bring the time current
// check the list to see if anything expired
// if so, do it - and either return it to the freelist 
// or put it back into the timeoutq
//
// return whether or not you handled anything
//
int handle_timeoutq_event( )
{
    struct event * ev = (struct event * )LL_TOP( timeoutq );
    if( EV_NULL == ev )
        return 0;
    unsigned int now = now_usec();
    ev->timeout -= ( now - then_usec );
    then_usec = now;

    if( ev->timeout <= 0 )
    {
        ev->go( ev->data );
        printf("running some function\n");
        LL_POP( timeoutq );
        if( ev->repeat_interval != 0 )
        {
            ev->timeout = ev->repeat_interval ;
            insert_timeoutq_event( ev );
        }
        else
        {
            LL_PUSH( freelist, ev );
        }
        return 1;
    }



    return 0;
}
//
// insert the event to timeque
//
void insert_timeoutq_event( struct event * ep)
{
	// Try to insert it according to timeout and timeoutq
	struct event * it;
    short is_pushed = 0;

    // Judge if we gonna insert it before a current event in timeque
	LL_EACH(timeoutq,it,struct event )
	{
		if( it != EV_NULL )
		{
			if( ( it->timeout ) > ( ep->timeout ) )
			{
                it->timeout -= ep->timeout;
                LL_L_INSERT( it, ep );
                is_pushed = 1;
				printf("left insert \n");
                break;
			}
            else
            {
                ep->timeout -= it->timeout;
            }
		}
	}
    
    // If not insert it left to the header
    if( is_pushed == 0 )
    {
        LL_APPEND(timeoutq, ep);
        printf("tail insert\n");
    }

    dump_timeoutq();

}

