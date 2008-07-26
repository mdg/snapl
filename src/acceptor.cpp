#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include "acceptor.h"


acceptor_c::acceptor_c()
: m_port( 0 )
, m_listener( 0 )
{
}

acceptor_c::~acceptor_c()
{
	close();
}

void acceptor_c::open( int port, int backlog )
{
	m_listener = socket( PF_INET, SOCK_STREAM, 0 );
	if ( m_listener < 0 ) {
		// error.  do something.
		perror( "Unable to create socket." );
		return;
	}
	printf( "Socket connected at: %u\n", m_listener );

	struct sockaddr_in addr;
	memset( &addr, 0, sizeof(addr) );
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = INADDR_ANY;
	int bind_error = bind( m_listener, (struct sockaddr *) &addr
			, sizeof(addr) );
	if ( bind_error ) {
		// error.  do something.
		perror( "Unable to bind socket." );
		return;
	}

	int listen_error = listen( m_listener, backlog );
	if ( listen_error < 0 ) {
		// error.  do something.
		perror( "Socket won't listen." );
		return;
	}
	printf( "Listening on port %u...\n", port );
}

void acceptor_c::close()
{
	m_port = 0;
	if ( m_listener ) {
		shutdown( m_listener, SHUT_RDWR );
		m_listener = 0;
	}
}

int acceptor_c::connection()
{
	sockaddr addr;
	socklen_t addr_len( 0 );
	printf( "Waiting for connection..." );
	int sock = accept( m_listener, &addr, &addr_len );
	if ( sock < 0 ) {
		perror( "No connection." );
		return -1;
	}
	printf( "Connected at %u\n", sock );
	return sock;
}

