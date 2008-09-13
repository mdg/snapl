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
#include "configuration.h"


/**
 * Test that preconditions are set properly
 * in the config_option class.
 */
TESTPP( test_config_option_initialization )
{
	config_option_c< std::string > opt( "dog" );

	// assert preconditions
	std::string( "dog" ) == actual( opt.name() );
	false == actual( opt.set() );
	false == actual( opt.error() );
}

/**
 * Test that preconditions are set properly
 * in the config_option constructor with a
 * default value.
 */
TESTPP( test_config_option_default_init )
{
	config_option_c< int > opt( "dog", 58 );

	// assert preconditions
	std::string( "dog" ) == actual( opt.name() );
	58 == actual( opt.value() );
	true == actual( opt.set() );
	false == actual( opt.error() );
}

/**
 * Test that the config option class works for the
 * string type.
 */
TESTPP( test_string_config_option )
{
	config_option_c< std::string > opt( "dog" );
	opt.parse( "cat" );

	// assert postconditions
	std::string( "cat" ) == actual( opt.value() );
	true == actual( opt.set() );
	false == actual( opt.error() );
}

/**
 * Test that the config_option class works for integers.
 */
TESTPP( test_int_config_option )
{
	config_option_c< int > opt( "dog" );
	opt.parse( "89" );

	// assert postconditions
	89 == actual( opt.value() );
	true == actual( opt.set() );
	false == actual( opt.error() );
}


/**
 * Test that the config_option class works for booleans.
 */
TESTPP( test_bool_config_option )
{
	config_option_c< bool > opt( "dog" );
	opt.parse( "1" );

	// assert postconditions
	true == actual( opt.value() );
	true == actual( opt.set() );
	false == actual( opt.error() );
}

/**
 * Test that parsing an invalid string for integers fails properly.
 */
TESTPP( test_invalid_int_option )
{
	config_option_c< int > opt( "dog" );
	opt.parse( "cat" );

	// assert postconditions
	true == actual( opt.error() );
	false == actual( opt.set() );
	0 == actual( opt.value() );
}


/**
 * Test the most basic functionality, 2 string options
 */
TESTPP( test_basic_string_options )
{
	config_option_c< std::string > option1( "option1" );
	config_option_c< std::string > option2( "option2" );

	configuration_c config;
	config.add( option1 );
	config.add( option2 );

	std::istringstream input( "option1=dog\noption2=cat" );

	config.parse( input );

	true == actual( option1.set() );
	true == actual( option2.set() );
	std::string( "dog" ) == actual( option1.value() );
	std::string( "cat" ) == actual( option2.value() );
}

TESTPP( test_int_options )
{
	/*
	config.int_option( "port" );
	config.int_option( "session-timeout" );
	config.bool_option( "t_or_f" );
	*/
}


/**
 * Test the most basic, default case of a config file.
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
 */

/**
 * Test that it still works with windows line endings.
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
 */

/**
 * Test that whitespace doesn't mess up the parsing of a config file.
TESTPP( test_whitespace )
{
	const char str_input[] = "\nsession-timeout = 20  \n";
	std::stringstream input( str_input );

	config_parser_c parser( input );
	parser.parse_input();

	std::string( "20" ) == actual( parser.str_value( "session-timeout" ) );
}
 */


/**
 * Test that a non integer value doesn't freak out when an integer
 * is requested.
TESTPP( test_non_integer )
{
	const char str_input[] = "session-timeout=hh340\n";
	std::stringstream input( str_input );

	config_parser_c parser( input );
	parser.parse_input();

	std::string str_value( parser.str_value( "session-timeout" ) );
	// parser returns 0 right now if it's not an integer
	0 == actual( parser.int_value( "session-timeout" ) );
}
 */

