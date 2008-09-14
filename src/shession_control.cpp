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
#include "connection.h"
#include "connection_listener.h"
#include "protocol.h"
#include "request.h"
#include "request_processor.h"


shession_control_c::shession_control_c( connection_listener_i &conn_fact )
: m_connection_factory( conn_fact )
, m_protocol()
{}

shession_control_c::~shession_control_c() {}


void shession_control_c::add_protocol( short port, protocol_c &protocol )
{
	m_protocol[ port ] = &protocol;
}


bool shession_control_c::main_loop()
{
	bool success( false );
	for (;;) {
		iterate();
	}

	return success;
}

void shession_control_c::iterate()
{
	bool success( false );
	request_c *req = 0;

	connection_i *conn = m_connection_factory.connection();
	if ( ! conn ) {
		return;
	}

	// find the request_reader
	int port( conn->port() );
	std::string req_line;

	do {
		conn->read_line( req_line );
		request_c req( req_line );

		protocol_iterator it( m_protocol.find( port ) );
		if ( it == m_protocol.end() ) {
			std::cerr << "port " << port << " has no protocol\n";
			// maybe should close this connection also?
			continue;
		}

		protocol_c &protocol( *it->second );
		request_processor_i *proc = protocol.processor(
					req.type() );
		if ( proc ) {
			proc->process( req, *conn );
		}
		// continue reading from this connection
		// while it has input
	} while ( conn->line_ready() );
}

