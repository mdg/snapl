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
#include "snapl/dispatcher.h"
#include "snapl/protocol.h"
#include "snapl/net/inbox.h"
#include "snapl/net/outbox.h"
#include "server_message.h"
#include "connection_test.h"
#include "connection_listener_test.h"
#include "command_test.h"
#include "service_test.h"
#include <testpp/test.h>


/**
 * Test that the mock_client_server_connection class works.
 */
TESTPP( test_mock_client_server_conn )
{
	mock_client_server_connection_c cs;
	connection_i &client( cs.client() );
	connection_i &server( cs.server() );

	std::string line;
	client.write_line( "test 1" );
	assertpp( server.line_ready() );
	server.read_line( line );
	assertpp( line ) == "test 1";
}

/**
 * Test that the mock_connection doesn't crash if it's empty.
 */
TESTPP( test_empty_mock_client_server )
{
	mock_client_server_connection_c cs;

	std::string line;
	cs.client().read_line( line );
	assertpp( line ) == "";
}


/**
 * Integration test of mock client running with mock server
 */
TESTPP( test_client_server )
{
	mock_client_server_connection_c cs( 3 );

	client_c client( cs.client() );
	mock_connection_listener_c listener( cs.server() );
	cs.set_client_line_ready();
	cs.set_server_line_ready();

	queue_c< server_message_c > request;
	queue_c< server_message_c > response;
	queue_c< server_message_c > complete;
	inbox_c inbox( listener, request, complete );
	dispatcher_c dispatch( request, response );
	outbox_c outbox( response, complete );

	protocol_c protocol( 3 );
	protocol.add< mock_service_c >( "mock" );
	dispatch.add( protocol );


	// need to add code and assertions here
	// create client command
	mock_command_c cmd( "id5", 17 );

	// send command to client
	client.send_request( cmd );
	// assert that the server connection has a line ready
	assertpp( cs.server().line_ready() ).t();

	inbox.iterate();
	// execute dispatcher
	dispatch.iterate();
	outbox.iterate();
	// assert that the client connection now has a line ready
	assertpp( cs.client().line_ready() ).t();

	// read a command from the client
	client.wait_for_response( cmd );

	// read client response
	assertpp( cmd.response().code() ) == "ok";
	assertpp( cmd.response().msg() ) == "id5_17";
}

