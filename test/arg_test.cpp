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

#include "snapl/arg.h"
#include <testpp/test.h>

using namespace snapl;


/**
 * Test that an argument is constructed properly.
 */
TESTPP( test_arg_constructor )
{
	int value( 5 );
	arg_c< int > arg( value );

	assertpp( arg.value() ) == 5;
}

/**
 * Test that the arg's get_string function works properly for an int.
 */
TESTPP( test_arg_get_string_int )
{
	int value( 5 );
	arg_c< int > arg( value );

	std::string text;
	arg >> text;
	assertpp( text ) == "5";
}

/**
 * Test that the arg's set_string works correctly for an integer.
 */
TESTPP( test_arg_set_string )
{
	int value( 5 );
	arg_c< int > arg( value );

	arg << "8";
	assertpp( arg.value() ) == 8;
}

/**
 * Test that an empty string is parsed correctly.
 */
TESTPP( test_arg_parse_empty )
{
	int value( 8 );
	arg_c< int > arg( value );

	arg << "";
	assertpp( value ) == 8;
}


/**
 * Test that the message arg list constructor works.
 */
TESTPP( test_arg_list_constructor )
{
	arg_list_c arg_list;

	assertpp( arg_list.size() ) == 0;
}

/**
 * Test that arguments are correctly added to a arg_list
 */
TESTPP( test_arg_list_append )
{
	arg_list_c arg;
	int val1( 5 );
	std::string val2( "txt2" );

	arg << val1 << val2;

	std::string value[2];
	assertpp( arg.size() ) == 2;
	arg_list_c::iterator it( arg.begin() );
	assertpp( *(it++) >> value[0] ) == "5";
	assertpp( *(it++) >> value[1] ) == "txt2";
	assertpp( it == arg.end() ).t();
}

