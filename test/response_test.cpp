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

#include "snapl/response.h"
#include <testpp/test.h>


/**
 * Test constructor for correctly set empty values.
 */
TESTPP( test_response_constructor )
{
	response_c r;

	assertpp( r.code() ) == "";
	assertpp( r.msg() ) == "";
}

/**
 * Test that the ok code is set properly.
 */
TESTPP( test_response_ok )
{
	response_c r;
	r.ok( "Sweet!  This works!" );

	assertpp( r.code() ) == "ok";
	assertpp( r.msg() ) == "Sweet!  This works!";
	assertpp( r.coded_msg() ) == "ok Sweet!  This works!";
}

/**
 * Test that the err code is set properly.
 */
TESTPP( test_response_err )
{
	response_c r;
	r.err( "too bad... didn't work." );

	assertpp( r.code() ) == "err";
	assertpp( r.msg() ) == "too bad... didn't work.";
	assertpp( r.coded_msg() ) == "err too bad... didn't work.";
}

/**
 * Test that the content is set correctly.
 */
TESTPP( test_write_content )
{
	response_c r;

	assertpp( r.has_content() ).f();

	r.write_line( "line 1" );
	r.write_line( "line 2" );

	assertpp( r.has_content() ).t();
	assertpp( r.content() ) == "\tline 1\n\tline 2\n";
}

