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

#include "message_reader.h"
#include "server_message.h"
#include "connection_test.h"
#include <testpp/test.h>


/**
 * Test that the message constructor works as expected.
 */
TESTPP( test_message_reader_constructor )
{
	mock_client_server_connection_c conn;
	message_reader_c reader( &conn.server() );

	assertpp( reader.complete() ).f();
	std::auto_ptr< server_message_c > msg( reader.message() );
	assertpp( msg.get() ).f();
}

/**
 * Test that the message constructor correctly reads a one line message.
 */
TESTPP( test_message_reader_one_line )
{
	mock_client_server_connection_c conn;
	message_reader_c reader( &conn.server() );

	conn.client().write_line( "get this" );

	bool success( reader.read() );
	assertpp( success ).t();

	assertpp( reader.complete() );
	std::auto_ptr< server_message_c > msg( reader.message() );
	assertpp( msg.get() ).t();
	if ( msg.get() ) {
		assertpp( msg->request().argc() ) == 2;
	}
}

