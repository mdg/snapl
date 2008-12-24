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
#include "connection.h"
#include "connection_listener.h"
#include "server_message.h"


polling_server_queue_c::polling_server_queue_c(
		connection_listener_i &listener )
: m_listener( listener )
{}


polling_server_queue_c::~polling_server_queue_c()
{}


server_message_c * polling_server_queue_c::pop()
{
	server_message_c *msg = NULL;
	if ( ! m_queue.empty() ) {
		msg = m_queue.front();
		m_queue.pop();
		return msg;
	}

	connection_i *conn = m_listener.connection();
	if ( ! conn )
		return NULL;

	int port( conn->port() );
	std::string req_line;

	do {
		conn->read_line( req_line );
		msg = new server_message_c( req_line, *conn );
		m_queue.push( msg );
	} while ( conn->line_ready() );

	if ( m_queue.empty() ) {
		return NULL;
	}

	msg = m_queue.front();
	m_queue.pop();
	return msg;
}

void polling_server_queue_c::push( server_message_c *msg_ptr )
{
	std::auto_ptr< server_message_c > msg( msg_ptr );

	// this should go somewhere else, maybe into response now
	connection_i &conn( msg->connection() );
	const response_c &resp( msg->response() );
	conn.write_line( resp.coded_msg() );
	if ( resp.has_content() ) {
		conn.write_line( resp.content() );
	}
}

