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
#include "request_type.h"


/**
 * Test that the constructor works and the parameters are
 * set correctly and can be requested again.
 */
TESTPP( test_constructor_1 )
{
	request_c req( "renew dog" );

	assertpp( req.type() ) == RT_RENEW_SESSION;
	assertpp( req.argc() ) == 1;
	assertpp( req.argv( 0 ) ) == "dog";
}

/**
 * Test the constructor and simple getters again, slightly
 * differently.  This test is probably not necessary.
 */
TESTPP( test_constructor_2 )
{
	request_c req( "create cat mouse" );

	assertpp( req.type() ) == RT_CREATE_SESSION;
	assertpp( req.argc() ) == 2;
	assertpp( req.argv( 0 ) ) == "cat";
	assertpp( req.argv( 1 ) ) == "mouse";
}

