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


#include "request_parser.h"
#include <sstream>
#include <iostream>
#include <list>


void request_parser_c::add_input( const std::string &input )
{
	m_input.append( input );
}

std::string request_parser_c::readline()
{
	if ( m_input.find( "\n" ) == std::string::npos ) {
		return std::string();
	}
	std::istringstream str( m_input );
	std::list< std::string > lines;
	std::string line;
	do {
		std::getline( str, line );
		lines.push_back( line );
		std::cerr << "line: " << line;
	} while ( ! str.eof() );

	// m_input = remainder;
	m_input = std::string();

	return line;
}

