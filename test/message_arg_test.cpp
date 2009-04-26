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

#include "snapl/message_arg.h"
#include "snapl/arg.h"
#include <testpp/test.h>

using namespace snapl;


/**
 * Test that a message argument is constructed properly.
 */
TESTPP( test_message_arg_constructor )
{
	message_arg_c arg( "dog" );

	assertpp( arg.get() ) == "dog";
}

/**
 * Test that the message_arg correctly parses an empty quoted string
 */
TESTPP( test_message_arg_parse_empty_string )
{
	std::istringstream in( "\"\"" );
	message_arg_c arg;

	in >> arg;

	assertpp( arg.get() ) == "";
}

/**
 * Test that the message_arg correctly parses quoted words separated by spaces.
 */
TESTPP( test_message_arg_parse_quoted_words )
{
	std::istringstream in( "dog \"cat mouse\"" );
	message_arg_c arg;

	in >> arg;
	assertpp( arg.get() ) == "dog";

	in >> arg;
	assertpp( arg.get() ) == "cat mouse";

	in >> arg;
}

/**
 * Test that multiple words correctly write the string into a stream.
 */
TESTPP( test_message_arg_write_multiple_words )
{
	std::ostringstream out;
	message_arg_c arg( "one value" );

	out << arg;

	assertpp( out.str() ) == "\"one value\"";
}


/**
 * Test that the message arg list constructor works.
 */
TESTPP( test_message_arg_list_constructor )
{
	message_arg_list_c arg_list;

	assertpp( arg_list.argc() ) == 0;
}

/**
 * Test that the message_arg_list correctly parses quoted strings
 */
TESTPP( test_message_arg_list_parse_quoted_args )
{
	message_arg_list_c args;
	args.parse( "dog \"cat mouse\"" );

	assertpp( args.argc() ) == 2;
	assertpp( args.argv( 0 ) ) == "dog";
	assertpp( args.argv( 1 ) ) == "cat mouse";
}

/**
 * Test copying values from an arg_list into a message_arg_list.
 */
TESTPP( test_copy_arg_list )
{
	int num( 5 );
	std::string text( "dog" );
	arg_list_c arg;

	arg << num << text;

	message_arg_list_c msg_list;
	msg_list = arg;

	assertpp( msg_list.argv(0) ) == "5";
	// assertpp( msg_list.argv(1) ) == "dog";
}

