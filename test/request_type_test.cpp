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
#include "request_type.h"


/**
 * Test that the default constructor works and the
 * parameters are set correctly and can be requested again.
 */
TESTPP( test_default_constructor )
{
	request_type_c req_type;
	assertpp( req_type.type() ) == RT_NULL;
	assertpp( req_type.name() ) == "";
}

/**
 * Test request type to name mapping.
 */
TESTPP( test_request_type_to_name_map )
{
	assertpp( request_type_c::type_to_name( RT_CREATE_SESSION ) )
		== "create";
	assertpp( request_type_c::type_to_name( RT_RENEW_SESSION ) )
		== "renew";
	assertpp( request_type_c::type_to_name( RT_KILL_SESSION ) )
		== "kill";
	assertpp( request_type_c::type_to_name( RT_EXPORT ) )
		== "export";
	assertpp( request_type_c::type_to_name( RT_CLOSE ) )
		== "close";
}

/**
 * Test request name to type mapping.
 */
TESTPP( test_request_name_to_type_map )
{
	assertpp( request_type_c::name_to_type( "create" ) )
		== RT_CREATE_SESSION;
	assertpp( request_type_c::name_to_type( "renew" ) )
		== RT_RENEW_SESSION;
	assertpp( request_type_c::name_to_type( "kill" ) )
		== RT_KILL_SESSION;
	assertpp( request_type_c::name_to_type( "export" ) )
		== RT_EXPORT;
	assertpp( request_type_c::name_to_type( "close" ) )
		== RT_CLOSE;
}


/**
 * Test the constructor that takes a request_type_e
 */
TESTPP( test_req_type_constructor )
{
	request_type_c req_type( RT_CREATE_SESSION );
	assertpp( req_type.type() ) == RT_CREATE_SESSION;
	assertpp( req_type.name() ) == "create";
}

/**
 * Test the constructor that takes a string request type name
 */
TESTPP( test_req_name_constructor )
{
	std::string name( "renew" );
	request_type_c req_type( name );
	// this line changes the source string to verify it doesn't
	// affect the req_type's data
	name = "newer";
	assertpp( req_type.type() ) == RT_RENEW_SESSION;
	assertpp( req_type.name() ) == "renew";
}

/**
 * Test unknown type name
 */
TESTPP( test_unknown_typename )
{
	request_type_c req_type( "something weird" );
	assertpp( req_type.type() ) == RT_NULL;
	assertpp( req_type.name() ) == "";
}

