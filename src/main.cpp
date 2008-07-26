#include <stdio.h>
#include "acceptor.h"


int main( int argc, char **argv )
{
	acceptor_c a;
	a.open( 9000 );

	int connection = 0;
	do {
		printf( "Connecting..." );
		connection = a.connection();
	} while ( connection );

	return 0;
}

