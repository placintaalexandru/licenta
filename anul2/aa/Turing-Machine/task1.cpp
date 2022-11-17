/* PLACINTA ALEXANDRU, 324CB */

#include "structuri.h"


int main( void )
{
	extern void start( char const *numeFisierIntrare, char const *numeFisierIesire, char const *numeFisierIntrareBanda );
	start( "tm.in", "tape.out", "tape.in" );
	return 0;
}
