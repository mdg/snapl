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

#include "server_message.h"
#include "connection_test.h"
#include <testpp/test.h>


/**
 * Test that the constructor for the server message sets fields
 * into the correct state.
 */
TESTPP( test_server_message_constructor )
{
	mock_client_server_connection_c cs( 3 );
	server_message_c msg( "create dog cat", cs.server() );

	assertpp( msg.request_type() ) == "create";
	// assertpp( msg.request().extra_argc() ) == 3;
	assertpp( msg.port() ) == 3;
}

