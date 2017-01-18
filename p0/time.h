//
// time.h
//
// information regarding the time library
//

#define	ONE_SECOND	(500)		// you define this however you want/need


extern unsigned int gettime( void );
extern unsigned int timediff( unsigned int now, unsigned int then );
extern void wait( unsigned int time );

