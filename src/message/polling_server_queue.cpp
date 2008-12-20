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

#include "polling_server_queue.h"


polling_server_queue_c::polling_server_queue_c(
		connection_listener_i &listener )
: m_listener( listener )
{}


polling_server_queue_c::~polling_server_queue_c()
{}


request_message_i * polling_server_queue_c::pop()
{
	request_message_i *msg = NULL;
	if ( ! m_queue.empty() ) {
		msg = m_queue.front();
		m_queue.pop();
		return msg;
	}

	connection_i *conn = m_connection_factory.connection();
	if ( ! conn )
		return NULL;

	int port( conn->port() );
	std::string req_line;

	do {
		conn->read_line( req_line );
		request_c req( req_line );
		msg = new request_message_c( req, conn );
		m_queue.push_back( msg );
	} while ( conn->line_ready() );

	if ( m_queue.empty() ) {
		return NULL;
	}

	msg = m_queue.front();
	m_queue.pop();
	return msg;
}

void polling_server_queue_c::push( response_message_i *msg )
{
}

