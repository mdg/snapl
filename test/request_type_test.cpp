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
	RT_NULL == actual( req_type.type() );
	std::string() == actual( req_type.name() );
}

/**
 * Test the constructor that takes a request_type_e
 */
TESTPP( test_req_type_constructor )
{
	request_type_c req_type( RT_CREATE_SESSION );
	RT_CREATE_SESSION == actual( req_type.type() );
	std::string( "create" ) == actual( req_type.name() );
}

/**
 * Test the constructor that takes a string request type name
 */
TESTPP( test_req_name_constructor )
{
	std::string name( "renew" );
	request_type_c req_type( name );
	name = "newer";
	RT_RENEW_SESSION == actual( req_type.type() );
	std::string( "renew" ) == actual( req_type.name() );
}

/**
 * Test unknown type name
 */
TESTPP( test_unknown_typename )
{
	request_type_c req_type( "something weird" );
	RT_NULL == actual( req_type.type() );
	std::string() == actual( req_type.name() );
}
