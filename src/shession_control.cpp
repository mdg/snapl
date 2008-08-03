#include "shession_control.h"
#include "acceptor.h"
#include "request.h"
#include "request_reader.h"


shession_control_c::shession_control_c()
{
	m_acceptor = new acceptor_c();
}

shession_control_c::~shession_control_c()
{
	delete m_acceptor;
	m_acceptor = 0;
}

bool shession_control_c::execute( short port )
{
	bool accept_err( m_acceptor->open( port ) );
	if ( ! accept_err ) {
		return false;
	}

	for (;;) {
		accept_connections();
		process_requests();
	}

	return true;
}

void shession_control_c::accept_connections()
{
	int new_connection( m_acceptor->connection() );
	while ( new_connection ) {
		request_reader_c *reader;
		reader = new request_reader_c( new_connection );
		m_reader.push_back( reader );

		new_connection = m_acceptor->connection();
	}
}

void shession_control_c::process_requests()
{
	std::list< request_reader_c * >::iterator it( m_reader.begin() );
	for ( ; it!=m_reader.end(); ++it ) {
		request_reader_c &reader( **it );
		request_c *req = reader.create_request();
		delete req;
		req = 0;
	}
}

