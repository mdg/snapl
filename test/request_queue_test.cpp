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


#include "request_queue.h"
#include "server_message.h"
#include <testpp/test.h>

class connection_i;


/**
 * Test the basic construction of the request queue.
 */
TESTPP( test_request_queue_constructor )
{
	request_queue_c queue;
	assertpp( queue.pop() ).f();
}

/**
 * Test pushing and popping works as expected.
 */
TESTPP( test_request_queue_push_pop )
{
	ignore_until( 2009, 1, 18 );
	return;

	connection_i *conn = 0;
	request_queue_c queue;

	queue.push( new server_message_c( "create dog", *conn ) );
	queue.push( new server_message_c( "create cat", *conn ) );

	std::auto_ptr< server_message_c > msg;

	msg.reset( queue.pop() );
	assertpp( msg->request_type() ) == "create";
	assertpp( msg->request().argc() ) == 1;
	assertpp( msg->request().argv( 0 ) ) == "dog";

	msg.reset( queue.pop() );
	assertpp( msg->request_type() ) == "create";
	assertpp( msg->request().argc() ) == 1;
	assertpp( msg->request().argv( 0 ) ) == "cat";
}

