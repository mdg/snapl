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
#include "connection_test.h"
#include "command_test.h"
#include <testpp/test.h>


/**
 * Verify that the client is actually sending the request through to the
 * server.
 */
TESTPP( test_client_send_request )
{
	mock_client_server_connection_c cs;
	cs.set_server_line_ready();
	client_c client( cs.client() );
	connection_i &server( cs.server() );

	// need to add code and assertions here
	// create client command
	mock_command_c cmd( "id5", 17 );

	// send command to client
	client.send_request( cmd );

	assertpp( server.line_ready() ).t();

	std::string server_line;
	server.read_line( server_line );
	assertpp( server_line ) == "mock id5 17";
}

