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
#include "usage.h"
#include <sstream>


/**
 * Test that the short style command line usage works.
 */
TESTPP( test_short_usage )
{
	usage_c usage;
	usage_option_c debug( false, 'g', "debug", "Add debugging logging." );
	usage.add( debug );

	static const int argc( 2 );
	const char *argv[20] = { "shessiond", "-g" };

	usage.parse_args( argc, argv );

	assertpp( debug.is_set() ).t();
}

/**
 * Test that the long style command line usage works.
 */
TESTPP( test_long_usage )
{
	usage_c usage;
	usage_option_c debug( false, 'g', "debug", "Add debugging options." );
	usage.add( debug );

	static const int argc( 2 );
	const char *argv[20] = { "shessiond", "--debug" };

	usage.parse_args( argc, argv );

	assertpp( debug.is_set() ).t();
}

/**
 * Test that option document creation works and formats properly.
 */
TESTPP( test_option_doc )
{
	usage_option_c debug( false, 'g', "debug", "Write debugging logging." );
	std::ostringstream doc;
	debug.write_usage_doc( doc );

	assertpp( doc.str() ) == "\t-g\t--debug\tWrite debugging logging.\n";
}

