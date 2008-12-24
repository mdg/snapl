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
#include "server_queue_test.h"
#include "protocol.h"
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

