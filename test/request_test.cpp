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


#include "request_test.h"
#include <testpp/test.h>


/**
 * Test that the default constructor with a basic request_type param works
 * and the type is set correctly and can be requested again.
 */
TESTPP( test_request_default_constructor )
{
	request_c req( "renew" );

	assertpp( req.type() ) == "renew";
	assertpp( req.argc() ) == 1;
	assertpp( req.argv( 0 ) ) == "renew";
}


/**
 * Test mock request constructor.
 */
TESTPP( test_mock_request_constructor )
{
	mock_request_c req;
	req.set( "id_34", 23 );

	assertpp( req.id() ) == "id_34";
	assertpp( req.number() ) == 23;
}

