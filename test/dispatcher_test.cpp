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

#include "snapl/dispatcher.h"
#include "snapl/protocol.h"
#include "server_message.h"
#include "connection_test.h"
#include "connection_listener_test.h"
#include "service_test.h"
#include <testpp/test.h>


/**
 * Test that protocols are correctly found after being added.
 */
TESTPP( test_dispatch_find_protocol )
{
	queue_c< server_message_c > request_queue;
	queue_c< server_message_c > response_queue;
	dispatcher_c d( request_queue, response_queue );

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
	queue_c< server_message_c > request_queue;
	queue_c< server_message_c > response_queue;
	dispatcher_c dispatch( request_queue, response_queue );

	protocol_c protocol( 3 );
	mock_service_c service;
	protocol.add( "mock", service );
	dispatch.add( protocol );

	mock_client_server_connection_c cs( 3 );
	std::auto_ptr< server_message_c > msg( new server_message_c(
				"mock dog 15", &cs.server() ) );
	request_queue.push( msg.release() );

	dispatch.iterate();

	assertpp( response_queue.empty() ).f();
	msg.reset( response_queue.pop() );

	// assert on response values
	const message_c &response( msg->response() );
	assertpp( response.arg_string() ) == "ok dog_15";
}

