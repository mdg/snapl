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

#include "command_test.h"
#include <testpp/test.h>
#include "snapl/message.h"

using namespace snapl;


/**
 * Test that the default constructor with a basic service param works
 * and the type is set correctly and can be requested again.
 */
TESTPP( test_command_default_constructor )
{
	command_c cmd( "renew" );

	assertpp( cmd.service() ) == "renew";
	assertpp( cmd.input().argc() ) == 1;
	assertpp( cmd.response_code() ) == "";
	assertpp( cmd.response_msg() ) == "";
}


/**
 * Test mock command constructor.
 */
TESTPP( test_mock_command_constructor )
{
	mock_command_c cmd( "id_34", 23 );

	assertpp( cmd.id ) == "id_34";
	assertpp( cmd.number ) == 23;
}


/**
 * Test if the derived command class correctly converts to a message and
 * a message args string.
 */
TESTPP( test_mock_command_to_message )
{
	mock_command_c cmd( "id_34", 23 );

	message_c msg;
	cmd.get_input( msg );

	assertpp( msg.argc() ) == 3;
	assertpp( msg.argv( 0 ) ) == "mock";
	assertpp( msg.argv( 1 ) ) == "id_34";
	assertpp( msg.argv( 2 ) ) == "23";
	assertpp( msg.arg_string() ) == "mock id_34 23";
}

/**
 * Test that the ok code is set properly.
 */
TESTPP( test_command_ok )
{
	command_c cmd;
	cmd.ok();

	assertpp( r.response_code() ) == "ok";
	assertpp( r.msg() ) == "";
}

/**
 * Test that the err code is set properly.
 */
TESTPP( test_command_err )
{
	command_c cmd;
	cmd.err( "too bad... didn't work." );

	assertpp( r.response_code() ) == "err";
	assertpp( r.response_msg() ) == "too bad... didn't work.";
}

