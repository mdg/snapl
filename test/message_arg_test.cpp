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
#include <testpp/test.h>


/**
 * Test that a message argument is constructed properly.
 */
TESTPP( test_message_arg_constructor )
{
	message_arg_c arg( "dog" );

	assertpp( arg.get() ) == "dog";
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
	not_implemented( 2009, 2, 1 );
	return;

	message_arg_list_c args;
	args.parse( "dog \"cat mouse\"" );

	assertpp( args.argc() ) == 2;
	assertpp( args.argv( 0 ) ) == "dog";
	assertpp( args.argv( 1 ) ) == "cat mouse";
}

