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


/// Tests for the config_option_c class first

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


/// Tests for the configuration_c class

/**
 * Test the most basic functionality, 2 string options
 */
TESTPP( test_basic_string_options )
{
	config_option_c< std::string > option1( "option1" );
	config_option_c< std::string > option2( "option2" );
	config_option_c< std::string > option3( "option3" );

	configuration_c config;
	config.add( option1 );
	config.add( option2 );

	std::istringstream input( "option1=dog\noption2=cat" );

	config.parse( input );

	true == actual( option1.set() );
	true == actual( option2.set() );
	false == actual( option3.set() );
	std::string( "dog" ) == actual( option1.value() );
	std::string( "cat" ) == actual( option2.value() );
}

/**
 * Test the integer and boolean options
 */
TESTPP( test_int_options )
{
	config_option_c< int > port( "port" );
	config_option_c< int > timeout( "timeout" );
	config_option_c< bool > debug( "debug" );
	std::istringstream input( "port=4000\ntimeout=20\ndebug=1" );

	configuration_c config;
	config.add( port );
	config.add( timeout );
	config.add( debug );
	config.parse( input );

	true == actual( port.set() );
	true == actual( timeout.set() );
	true == actual( debug.set() );

	4000 == actual( port.value() );
	20 == actual( timeout.value() );
	true == actual( debug.value() );
}


/**
 * Test that it still works with windows line endings.
 */
TESTPP( test_crlf )
{
	config_option_c< int > timeout( "session-timeout" );
	config_option_c< std::string > split( "split" );

	const char str_input[] =
		"session-timeout=30\r\n"
		"split=dog";
	std::stringstream input( str_input );

	configuration_c config;
	config.add( split );
	config.add( timeout );
	config.parse( input );

	true == actual( timeout.set() );
	true == actual( split.set() );

	30 == actual( timeout.value() );
	std::string( "dog" ) == actual( split.value() );
}

/**
 * Test that whitespace doesn't mess up the parsing of a config file.
 */
TESTPP( test_whitespace )
{
	config_option_c< int > timeout( "session-timeout" );
	const char str_input[] = "\nsession-timeout = 20  \n";
	std::stringstream input( str_input );

	configuration_c config;
	config.add( timeout );
	config.parse( input );

	20 == actual( timeout.value() );
}


/**
 * Test that a non integer value doesn't freak out when an integer
 * is requested.
 */
TESTPP( test_non_integer )
{
	config_option_c< int > timeout( "session-timeout" );
	const char str_input[] = "session-timeout=hh340\n";
	std::stringstream input( str_input );

	configuration_c config;
	config.add( timeout );
	config.parse( input );

	true == actual( timeout.error() );
	true == actual( config.error() );
}

