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


#include "dispatcher.h"
#include "snapl/protocol.h"
#include "polling_server_queue.h"
#include "server_queue_test.h"
#include "connection_test.h"
#include "connection_listener_test.h"
#include "service_test.h"
#include <testpp/test.h>


/**
 * Test that protocols are correctly found after being added.
 */
TESTPP( test_dispatch_find_protocol )
{
	mock_server_queue_c queue;
	dispatcher_c d( queue );

	protocol_c p1( 1 );
	protocol_c p2( 2 );
	protocol_c p3( 3 );

	d.add( p1 );
	d.add( p2 );
	d.add( p3 );

	protocol_c *found = d.find_protocol( 2 );
	assertpp( found ).t();
	assertpp( found->port() ) == 2;
}


/**
 * Test that the dispatcher write's the expected info back to
 * the server_queue.
 */
TESTPP( test_dispatcher_success )
{
	mock_client_server_connection_c cs( 3 );

	mock_connection_listener_c listener( cs.server() );
	polling_server_queue_c server( listener );
	dispatcher_c dispatch( server );

	protocol_c protocol( 3 );
	protocol.add< mock_service_c >( "mock" );
	dispatch.add( protocol );

	cs.client().write_line( "mock dog 12" );

	dispatch.iterate();

	assertpp( cs.client().line_ready() );

	std::string line;
	cs.client().read_line( line );
	assertpp( line ) == "ok dog_12";
}

