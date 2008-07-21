#include <stdio.h>
#include "session_tree.h"


int main( void )
{
	if ( session_exists( "hello world" ) ) {
		printf( "session exists\n" );
	} else {
		printf( "no session\n" );
	}
	return 0;
}

