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

#include "snapl/client.h"
#include "snapl/command.h"
#include "snapl/message.h"
#include "snapl/net/connection.h"

using namespace snapl;


client_c::client_c()
: m_connection( NULL )
{}

client_c::client_c( connection_i &conn )
: m_connection( &conn )
{}


void client_c::send_request( command_c &cmd )
{
	// send_message( cmd.command_request() );
	// message_queue_i &queue( m_factory.message() );
	// queue.
	if ( ! m_connection )
		return;

	message_c msg;
	cmd.get_request( msg );
	m_connection->write_line( msg.arg_string() );
	// writing content in a request will come in a later iteration
}

void client_c::wait_for_response( command_c &cmd )
{
	std::string response_line;
	m_connection->read_line( response_line );
	message_c msg( response_line );
	// reading body from a response will come in a later iteration
	cmd.set_response(msg);
}

