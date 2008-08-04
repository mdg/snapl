#include "shession_control.h"
#include <iostream>
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
	// std::cerr << "begin accept_connections()\n";

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
	// std::cerr << "begin process_requests()\n";

	std::list< request_reader_c * >::iterator it( m_reader.begin() );
	request_reader_c *reader = 0;
	for ( ; it!=m_reader.end(); ++it ) {
		reader = *it;
		// delete any readers that are no longer connected
		while ( reader && ! reader->connected() ) {
			it = m_reader.erase( it );
			if ( it == m_reader.end() ) {
				reader = 0;
			} else {
				reader = *it;
			}
		}

		if ( reader ) {
			request_c *req = reader->create_request();
			process_request( *req );
			delete req;
			req = 0;
		}
	}

	// std::cerr << "end process_requests()\n";
}

void shession_control_c::process_request( const request_c &req )
{
}

