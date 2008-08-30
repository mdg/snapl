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
#include <sstream>
#include <fstream>
#include "config_parser.h"


TESTPP( test_easy_format )
{
	const char str_input[] =
		"session_timeout=30\n"
		"split=dog";
	std::stringstream input( str_input );

	config_parser_c parser( input );
	parser.parse_input();

	true == actual( parser.configured( "session_timeout" ) );
	true == actual( parser.configured( "split" ) );

	std::string( "30" ) == actual( parser.str_value( "session_timeout" ) );
	30 == actual( parser.int_value( "session_timeout" ) );
	std::string( "dog" ) == actual( parser.str_value( "split" ) );
}

TESTPP( test_crlf )
{
	const char str_input[] =
		"session_timeout=30\r\n"
		"split=dog";
	std::stringstream input( str_input );

	config_parser_c parser( input );
	parser.parse_input();

	true == actual( parser.configured( "session_timeout" ) );
	true == actual( parser.configured( "split" ) );

	30 == actual( parser.int_value( "session_timeout" ) );
	std::string( "dog" ) == actual( parser.str_value( "split" ) );
}

/**
 * Test that whitespace doesn't mess up the parsing of a config file.
 */
TESTPP( test_whitespace )
{
	const char str_input[] = "\nsession-timeout = 20  \n";
	std::stringstream input( str_input );

	config_parser_c parser( input );
	parser.parse_input();

	std::string( "20" ) == actual( parser.str_value( "session-timeout" ) );
}


/**
 * Test that a non integer value doesn't freak out when an integer
 * is requested.
 */
TESTPP( test_non_integer )
{
	const char str_input[] = "session-timeout=hh340\n";
	std::stringstream input( str_input );

	config_parser_c parser( input );
	parser.parse_input();

	20 == actual( parser.int_value( "session-timeout" ) );
}

