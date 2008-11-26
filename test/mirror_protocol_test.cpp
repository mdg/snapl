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

#include "mirror_protocol.h"
#include "shession_store.h"
#include "request.h"
#include "connected_socket.h"
#include <testpp.h>


/**
 * Test that the mirror session
 */
TESTPP( test_mirror_request )
{
	shession_store_c store( 50 );
	request_c req( "mirror dog cat" );
	mirror_request_processor_c proc( store );
	connection_i *conn = new connected_socket_c( fileno( stdout ), 0 );

	proc.process( req, *conn );
	assertpp( store.live( "dog" ) ).t();
}

/**
 * Test that the mirror dump request works.
 */
TESTPP( test_export_request )
{
	shession_store_c store( 50 );

	store.create( "dog", "user1" );
	store.create( "cat", "user2" );
	store.create( "mouse", "user3" );

	request_c req( "export" );
	export_request_processor_c proc( store );
	connection_i *conn = new connected_socket_c( fileno( stdout ), 0 );

	proc.process( req, *conn );
}

