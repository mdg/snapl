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

#include "client_server_test.h"
#include "blocking_client_queue.h"
#include "polling_server_queue.h"
#include "dispatcher.h"
#include "connection_listener_test.h"
#include "command_test.h"
#include <testpp/test.h>


mock_connection_c::mock_connection_c( std::queue< std::string > &read_queue,
			std::queue< std::string > &write_queue )
: m_read_queue( read_queue )
, m_write_queue( write_queue )
{}

void mock_connection_c::read_line( std::string &line )
{
	line = m_read_queue.front();
	m_read_queue.pop();
}

void mock_connection_c::write_line( const std::string &line )
{
	m_write_queue.push( line );
}

bool mock_connection_c::line_ready() const
{
	return ! m_read_queue.empty();
}


mock_client_server_connection_c::mock_client_server_connection_c()
: m_client_read_queue()
, m_server_read_queue()
, m_client( m_client_read_queue, m_server_read_queue )
, m_server( m_server_read_queue, m_client_read_queue )
{}


TESTPP( test_client_server )
{
	mock_client_server_connection_c cs;

	blocking_client_queue_c client( cs.client() );
	mock_connection_listener_c listener( cs.server() );
	polling_server_queue_c server( listener );
	dispatcher_c dispatch( server );

	not_implemented();

	// need to add code and assertions here
	// create client command
	mock_command_c cmd( "id5", 17 );

	// send command to client
	client.send( cmd );

	// execute dispatcher
	dispatch.iterate();

	// read client response
	assertpp( cmd.response().code() ) == "ok";
	assertpp( cmd.response().message() ) == "id5_17";
}

