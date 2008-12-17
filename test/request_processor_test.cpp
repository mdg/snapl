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
#include "request.h"
#include "response.h"
#include "request_processor.h"
#include "shession_store.h"
#include "shession_generator.h"
#include <stdio.h>


/**
 * Test that creating and killing a session works as expected.
 */
TESTPP( test_create_kill )
{
	shession_store_c store( 180 );
	shession_generator_c gen;
	create_action_c create_proc( store, gen );
	kill_action_c kill_proc( store );

	assertpp( store.live( "dog1714636915" ) ).f();

	request_c create_req( "create dog" );
	response_c create_resp;
	create_proc.process( create_req, create_resp );
	assertpp( store.live( "dog1714636915" ) ).t();

	request_c kill_req( "kill dog1714636915" );
	response_c kill_resp;
	kill_proc.process( kill_req, kill_resp );
	assertpp( store.live( "dog1714636915" ) ).f();
}

/**
 * Test that the renew_request works as expected.
 */
TESTPP( test_renew_success )
{
	shession_store_c store( 5 );
	renew_action_c renew_proc( store );

	store.create( "dog", "cat" );
	assertpp( store.live( "dog" ) ) == true;

	request_c req( "renew dog" );
	response_c resp;
	renew_proc.process( req, resp );

	assertpp( store.live( "dog" ) ).t();
	assertpp( resp.code() ) == "ok";
}

