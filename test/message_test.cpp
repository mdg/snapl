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

#include "message.h"
#include <testpp/test.h>


TESTPP( test_message_arg_constructor )
{
	int value( 5 );
	message_arg_c< int > arg( value );

	assertpp( arg.value() ) == 5;
}

TESTPP( test_message_arg_get_string )
{
	int value( 5 );
	message_arg_c< int > arg( value );

	std::string text;
	arg.get_string( text );
	assertpp( text ) == "5";
}

TESTPP( test_message_arg_set_string )
{
	int value( 5 );
	message_arg_c< int > arg( value );

	arg.set_string( "8" );
	assertpp( arg.value() ) == 8;
}


TESTPP( test_message_constructor )
{
	message_c msg;

	assertpp( msg.argc() ) == 0;
}

TESTPP( test_message_add_arg )
{
	message_c msg;

	msg.add_arg( "hello" );
	msg.add_arg( "world!" );
	msg.add_arg( "hello world!" );

	assertpp( msg.argc() ) == 3;
	assertpp( msg.argv( 0 ) ) == "hello";
	assertpp( msg.argv( 1 ) ) == "world!";
	assertpp( msg.argv( 2 ) ) == "hello world!";
}


TESTPP( test_message_parse_basic_args )
{
	message_c msg( "dog 5 purple" );

	assertpp( msg.argc() ) == 3;
	assertpp( msg.argv( 0 ) ) == "dog";
	assertpp( msg.argv( 1 ) ) == "5";
	assertpp( msg.argv( 2 ) ) == "purple";
}

TESTPP( test_message_parse_quoted_args )
{
	not_implemented( 2009, 2, 1 );

	message_c msg( "dog \"cat mouse\"" );

	assertpp( msg.argc() ) == 2;
	assertpp( msg.argv( 0 ) ) == "dog";
	assertpp( msg.argv( 1 ) ) == "cat mouse";
}

