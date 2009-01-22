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

#include "client.h"
#include "snapl/command.h"
#include "snapl/message.h"
#include "snapl/request.h"
#include "snapl/response.h"

#include "connection.h"


client_c::client_c()
: m_connection( NULL )
{}

client_c::client_c( connection_i &conn )
: m_connection( &conn )
{}


void client_c::send_request( command_i &cmd )
{
	// send_message( cmd.command_request() );
	// message_queue_i &queue( m_factory.message() );
	// queue.
	if ( ! m_connection )
		return;

	std::ostringstream out;
	const request_c &req( cmd.command_request() );
	m_connection->write_line( req.arg_string() );
}

void client_c::wait_for_response( command_i &cmd )
{
	std::string response_line;
	m_connection->read_line( response_line );
	cmd.command_response().parse_args( response_line );
}

