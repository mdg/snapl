#include "shession_control.h"


shession_control_c::shession_control_c()
{
}

shession_control_c::~shession_control_c()
{
}

void shession_control_c::execute()
{
	for ( ; ; ) {
		accept_connections();
		process_requests();
	}
}

void shession_control_c::accept_connections()
{
	int new_connection( m_acceptor.connection() );
	if ( new_connection == 0 ) {
		// no new connection.  return having done nothing.
		return;
	}

	m_reader.append( new request_reader_c( new_connection ) );
}

void shession_control_c::process_requests()
{
}

