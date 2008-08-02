#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <iostream>
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

bool acceptor_c::open( int port, int backlog )
{
	// create the socket
	m_listener = socket( PF_INET, SOCK_STREAM, 0 );
	if ( m_listener < 0 ) {
		// error.  do something.
		perror( "Unable to create socket." );
		return false;
	} else if ( m_listener == 0 ) {
		perror( "wtf happened?" );
		return false;
	}
	// printf( "Socket connected at: %u\n", m_listener );

	// std::string input;
	// std::cin >> input;

	// bind the socket
	struct sockaddr_in addr;
	memset( &addr, 0, sizeof(addr) );
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );
	addr.sin_addr.s_addr = INADDR_ANY;
	int bind_error = bind( m_listener, (struct sockaddr *) &addr
			, sizeof(addr) );
	if ( bind_error ) {
		// error.  do something.
		perror( "Unable to bind socket." );
		return false;
	}
	// std::cout << "Socket is bound.\n";

	// std::cin >> input;

	// make the socket listen
	int listen_error = listen( m_listener, backlog );
	if ( listen_error < 0 ) {
		// error.  do something.
		perror( "Socket won't listen." );
		return false;
	}
	// printf( "Listening on port %u...\n", port );

	struct sockaddr_in name;
	socklen_t name_len = sizeof( name );
	int sockname_err = getsockname( m_listener, (struct sockaddr *) &name, &name_len );
	if ( sockname_err ) {
		perror( "getsockname error" );
		return false;
	}

	return true;
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
	// std::cerr << "Waiting for connection...\n";
	// std::string input;
	// std::cin >> input;

	// sockaddr addr;
	// socklen_t addr_len( sizeof(addr) );
	// int sock = accept( m_listener, &addr, &addr_len );
	int sock = accept( m_listener, NULL, 0 );
	// std::cerr << "accept() completed\n";
	if ( sock < 0 ) {
		perror( "No connection." );
		return -1;
	}
	// std::cerr << "Connected at " << sock << std::endl;
	return sock;
}

