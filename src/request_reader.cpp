#include "request_reader.h"
#include <iostream>
#include <sys/socket.h>
#include "request.h"


request_reader_c::request_reader_c( int connection )
{
	m_connection = connection;
}

request_reader_c::~request_reader_c()
{
	if ( m_connection ) {
		shutdown( m_connection, SHUT_RDWR );
		m_connection = 0;
	}
}

request_c * request_reader_c::create_request()
{
	char buffer[256];
	read( m_connection, buffer, sizeof( buffer ) );
	char * nl = strchr( buffer, '\n' );
	if ( nl ) {
		*nl = '\0';
	}
	std::cerr << "request = " << buffer << std::endl;
	return new request_c( buffer );
}

