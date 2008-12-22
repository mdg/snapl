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


#include "line_parser.h"
#include <testpp/test.h>
#include <string.h>


/**
 * Test that the line parser correctly parses a single line.
 */
TESTPP( test_single_line )
{
	line_parser_c parser;
	parser.add_input( "status dog\n" );
	std::string parsed_line;
	parser.readline( parsed_line );

	assertpp( parsed_line ) == "status dog";
}


/**
 * Test that it works for multiple lines.
 */
TESTPP( test_multiline )
{
	line_parser_c parser;
	parser.add_input( "status dog\nstore cat\n" );
	std::string parsed_line;
	parser.readline( parsed_line );
	assertpp( parsed_line ) == "status dog";
	parser.readline( parsed_line );
	assertpp( parsed_line ) == "store cat";
}


/**
 * Test that the line parser correctly handles an incomplete
 * second line.  It should return nothing until it gets a full
 * line.
 */
TESTPP( test_incomplete )
{
	std::string parsed_line;
	line_parser_c parser;
	parser.add_input( "status dog\nstore cat" );
	parser.readline( parsed_line );
	assertpp( parsed_line ) == "status dog";
	parser.readline( parsed_line );
	assertpp( parsed_line ) == "";
	parser.add_input( "\n" );
	parser.readline( parsed_line );
	assertpp( parsed_line ) == "store cat";
}


/**
 * The parser needs to tolerate clients sending \r\n line endings.
 * This test proves that works.
 */
TESTPP( test_line_parser_crlf )
{
	std::string parsed_line;
	line_parser_c parser;
	parser.add_input( "status dog\r\nstore cat\r\n" );
	parser.readline( parsed_line );
	assertpp( parsed_line ) == "status dog";
	parser.readline( parsed_line );
	assertpp( parsed_line ) == "store cat";
}


/**
 * The parser needs to not freak out if "\n" is passed.  This
 * test verifies that.
 */
TESTPP( test_blanklf )
{
	std::string parsed_line;
	line_parser_c parser;
	parser.add_input( "\nstore cat\r\n" );
	parser.readline( parsed_line );
	assertpp( parsed_line ) == "";
	parser.readline( parsed_line );
	assertpp( parsed_line ) == "store cat";
}

/**
 * Test that the line_ready function works as expected.
 */
TESTPP( test_line_ready )
{
	std::string parsed_line;
	line_parser_c parser;
	parser.add_input( "store cat\nstatus cat\n" );
	parser.readline( parsed_line );
	assertpp( parser.line_ready() ).t();
}

