/**
 * Copyright 2008 Matthew Graham
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "shession_control.h"
#include <iostream>
#include "connection_factory.h"
#include "request.h"
#include "request_processor.h"
#include "request_reader.h"


shession_control_c::shession_control_c( connection_factory_i &conn_fact
	       , request_processor_c &processor )
: m_connection_factory( conn_fact )
, m_processor( processor )
{
}

shession_control_c::~shession_control_c()
{
}

bool shession_control_c::main_loop()
{
	std::string line;
	request_c *req = 0;
	for (;;) {
		connection_i &conn( get_ready_connection() );
		conn.read( line );
		req = m_reader.create_request( line );
		if ( req ) {
			process_request( *req, conn );
		}
	}

	return true;
}

void shession_control_c::accept_connections()
{
	// std::cerr << "begin accept_connections()\n";

	connection_i *new_connection( m_connection_factory.connection() );
	while ( new_connection ) {
		request_reader_c *reader;
		reader = new request_reader_c( new_connection );
		m_reader.push_back( reader );

		new_connection = m_connection_factory.connection();
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
			if ( req ) {
				m_processor.process( *reader, *req );
				delete req;
			}
			req = 0;
		}
	}

	// std::cerr << "end process_requests()\n";
}

