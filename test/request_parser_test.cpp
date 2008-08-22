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
#include <string.h>
#include "request_parser.h"


TESTPP( test_single_line )
{
	request_parser_c parser;
	parser.add_input( "status dog\n" );
	std::string( "status dog" ) == actual( parser.readline() );
}


TESTPP( test_multiline )
{
	request_parser_c parser;
	parser.add_input( "status dog\nstore cat\n" );
	std::string( "status dog" ) == actual( parser.readline() );
	std::string( "store cat" ) == actual( parser.readline() );
}


TESTPP( test_incomplete )
{
	request_parser_c parser;
	parser.add_input( "status dog\nstore cat" );
	std::string( "status dog" ) == actual( parser.readline() );
	std::string( "" ) == actual( parser.readline() );
	parser.add_input( "\n" );
	std::string( "store cat" ) == actual( parser.readline() );
}


/**
 * The parser needs to tolerate clients sending \r\n line endings.
 * This test proves that works.
 */
TESTPP( test_crlf )
{
	request_parser_c parser;
	parser.add_input( "status dog\r\nstore cat\r\n" );
	std::string( "status dog" ) == actual( parser.readline() );
	std::string( "store cat" ) == actual( parser.readline() );
}


/**
 * The parser needs to not freak out if "\n" is passed.  This
 * test verifies that.
 */
TESTPP( test_blanklf )
{
	request_parser_c parser;
	parser.add_input( "\nstore cat\r\n" );
	std::string( "" ) == actual( parser.readline() );
	std::string( "store cat" ) == actual( parser.readline() );
}

