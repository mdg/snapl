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


TESTPP( test_message_export_string )
{
	message_c msg;

	msg.add_arg( "dog" );
	msg.add_arg( "cat" );
	msg.add_arg( "mouse" );

	message_export_c exp( msg );
	std::string dog, cat, mouse;
	exp + dog + cat + mouse;

	assertpp( dog ) == "dog";
	assertpp( cat ) == "cat";
	assertpp( mouse ) == "mouse";
}

TESTPP( test_message_import_mixed )
{
	std::string dog( "dog" );
	int five( 5 );
	bool t( true );

	message_c msg;
	message_import_c import( msg );
	import + dog + five + t;

	assertpp( msg.argc() ) == 3;
	assertpp( msg.argv( 0 ) ) == "dog";
	assertpp( msg.argv( 1 ) ) == "5";
	assertpp( msg.argv( 2 ) ) == "1";
}

