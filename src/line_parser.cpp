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
#include <sstream>
#include <iostream>
#include <list>


void line_parser_c::add_input( const std::string &input )
{
	m_input.append( input );
}

void line_parser_c::readline( std::string &line )
{
	line.erase();

	size_t newline = m_input.find( "\n" );
	if ( newline == std::string::npos ) {
		return;
	}

	line = m_input.substr( 0, newline );
	// need to add a check here for null strings

	// kind of awkward check for \r line ending
	size_t last_char = line.length() - 1;
	if ( line[ last_char ] == '\r' ) {
		line.erase( last_char );
	}

	m_input = m_input.substr( newline + 1 );
	// std::cerr << "readline = '" << line << "'\n";
}

