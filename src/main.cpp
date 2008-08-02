#include <stdio.h>
#include <iostream>
#include "acceptor.h"
#include "request_reader.h"


int main( int argc, char **argv )
{
	acceptor_c a;
	if ( ! a.open( 9000 ) ) {
		return 1;
	}
	printf( "Listening...\n" );
	// std::vector< request_reader_c * > rr;

	int new_conn = 0;
	std::cerr << "Connecting...\n";
	new_conn = a.connection();
	std::cerr << "Now connected at " << new_conn << std::endl;
	// rr.append( new request_reader_c( new_conn ) );
	request_reader_c rr( new_conn );
	request_c *req;
	do {
		req = rr.create_request();
	} while ( req );

	return 0;
}

