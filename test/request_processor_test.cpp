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

#include "testpp.h"
#include "connected_socket.h"
#include "request.h"
#include "request_processor.h"
#include "shession_store.h"
#include <stdio.h>


/**
 * Test that creating and killing a session works as expected.
 */
TESTPP( test_create_kill )
{
	shession_store_c store( 180 );
	create_request_processor_c create_proc( store );
	kill_request_processor_c kill_proc( store );
	connection_i *conn = NULL;
	int fd( fileno( stdout ) );
	conn = new connected_socket_c( fd, 0 );

	false == actual( store.live_session( "dog" ) );

	request_c create_req( "create dog" );
	create_proc.process( create_req, *conn );
	true == actual( store.live_session( "dog" ) );

	request_c kill_req( "kill dog" );
	kill_proc.process( kill_req, *conn );
	false == actual( store.live_session( "dog" ) );
}

