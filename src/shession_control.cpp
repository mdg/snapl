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
#include "request.h"
#include "request_processor.h"
#include "request_reader.h"


shession_control_c::shession_control_c( connection_listener_i &conn_fact
	       , request_reader_c &reader, request_processor_c &processor )
: m_connection_factory( conn_fact )
, m_reader( reader )
, m_processor( processor )
{
}

shession_control_c::~shession_control_c()
{
}

bool shession_control_c::main_loop()
{
	bool success( false );
	for (;;) {
		success = iterate();
	}

	return success;
}

bool shession_control_c::iterate()
{
	bool success( false );
	for (;;) {
		request_c *req = 0;

		connection_i *conn = m_connection_factory.connection();
		if ( ! conn ) {
			continue;
		}
		do {
			req = m_reader.create_request( *conn );
			if ( req ) {
				m_processor.process( *req, *conn );
			}
			// continue reading from this connection
			// while it has input
		} while ( conn->line_ready() );
	}
	return success;
}

