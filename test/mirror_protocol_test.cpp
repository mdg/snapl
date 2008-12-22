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
#include "response.h"
#include <testpp/test.h>


/**
 * Test that the mirror session
 */
TESTPP( test_mirror_request )
{
	shession_store_c store( 50 );
	mirror_action_c proc( store );
	request_c req( "mirror dog cat" );
	response_c resp;

	proc.process( req, resp );
	assertpp( store.live( "dog" ) ).t();
}

/**
 * Test that the mirror dump request works.
 */
TESTPP( test_export_request )
{
	shession_store_c store( 50 );
	// this store object needs to use the mock timer to avoid
	// weird problems where the second count turns over during
	// the test.

	store.create( "dog", "user1" );
	store.create( "cat", "user2" );
	store.create( "mouse", "" );

	export_action_c proc( store );
	request_c req( "export" );
	response_c resp;

	proc.process( req, resp );
	// assert contents of response

	assertpp( resp.content() ) == "\tcat 50 user2\n" \
				    "\tdog 50 user1\n" \
				    "\tmouse 50\n";
}

