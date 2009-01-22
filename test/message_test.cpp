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

#include "snapl/message.h"
#include <testpp/test.h>


/**
 * Test that a message argument is constructed properly.
 */
TESTPP( test_message_arg_constructor )
{
	int value( 5 );
	message_arg_c< int > arg( value );

	assertpp( arg.value() ) == 5;
}

/**
 * Test that the message_arg's get_string function works properly for an int.
 */
TESTPP( test_message_arg_get_string_int )
{
	int value( 5 );
	message_arg_c< int > arg( value );

	std::string text;
	arg.get_string( text );
	assertpp( text ) == "5";
}

/**
 * Test that the message_arg's set_string works correctly for an integer.
 */
TESTPP( test_message_arg_set_string )
{
	int value( 5 );
	message_arg_c< int > arg( value );

	arg.set_string( "8" );
	assertpp( arg.value() ) == 8;
}


/**
 * Test that the message arg list constructor works.
 */
TESTPP( test_message_arg_list_constructor )
{
	message_arg_list_c arg_list;

	assertpp( arg_list.size() ) == 0;
}

/**
 * Test that arguments are correctly added to a message_arg_list
 */
TESTPP( test_message_arg_list_append )
{
	message_arg_list_c arg;
	int val1( 5 );
	std::string val2( "txt2" );

	arg << val1 << val2;

	assertpp( arg.size() ) == 2;
	assertpp( arg.argv( 0 ) ) == "5";
	assertpp( arg.argv( 1 ) ) == "txt2";

	std::string s[ 2 ];
	arg.argv( 0, s[ 0 ] );
	arg.argv( 1, s[ 1 ] );
	assertpp( s[ 0 ] ) == "5";
	assertpp( s[ 1 ] ) == "txt2";
}

/**
 * Test that the assignment operator works for the message arg list
 */
TESTPP( test_message_arg_list_assign )
{
	message_arg_list_c arg1, arg2;
	int val1( 0 ), val2( 7 );
	std::string str1, str2( "txt2" );

	arg1 << val1 << str1;
	arg2 << val2 << str2;

	arg1 = arg2;
	assertpp( val1 ) == 7;
	assertpp( str1 ) == "txt2";
}

/**
 * Test that the message_arg_list's str() function works as expected.
 */
TESTPP( test_message_arg_list_str )
{
	message_arg_list_c arg;
	int val1( 5 );
	std::string val2( "txt2" );

	arg << val1 << val2;

	assertpp( arg.str() ) == "5 txt2";
}

/**
 * Test that the message_arg_list's parse() function works for a normal case.
 */
TESTPP( test_message_arg_list_parse )
{
	message_arg_list_c arg;
	int val1( 5 );
	std::string val2( "txt2" );

	arg << val1 << val2;
	arg.parse( "8 spatula" );

	assertpp( val1 ) == 8;
	assertpp( val2 ) == "spatula";
}

/**
 * Test that the message_arg_list correctly parses quoted strings
 */
TESTPP( test_message_arg_list_parse_quoted_args )
{
	not_implemented( 2009, 2, 1 );
	return;

	message_c msg( "dog \"cat mouse\"" );

	assertpp( msg.argc() ) == 2;
	assertpp( msg.argv( 0 ) ) == "dog";
	assertpp( msg.argv( 1 ) ) == "cat mouse";
}

/**
 * Test that the message_arg_list parses correctly when there aren't
 * enough values.
 */
TESTPP( test_message_arg_list_parse_extra_values )
{
	message_arg_list_c arg;
	int val1( 5 );
	std::string val2( "txt2" );

	arg << val1 << val2;
	arg.parse( "8 spatula 55 dog cat" );

	assertpp( arg.size() ) == 5;
	assertpp( val1 ) == 8;
	assertpp( val2 ) == "spatula";

	assertpp( arg.extra_argc() ) == 3;
	assertpp( arg.extra_argv( 0 ) ) == "55";
	assertpp( arg.extra_argv( 1 ) ) == "dog";
	assertpp( arg.extra_argv( 2 ) ) == "cat";
}


/**
 * Test that the message constructor works as expected.
 */
TESTPP( test_message_constructor )
{
	message_c msg;

	assertpp( msg.argc() ) == 0;
}

