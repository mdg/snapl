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

#include "request.h"
#include <sstream>

#include <iostream>

request_c::request_c( const std::string &request_line )
: m_type()
, m_args()
{
	std::istringstream input( request_line );
	std::string parsed_word;

	// get the request_type
	input >> parsed_word;
	m_type = request_type_c( parsed_word );

	// parse the arguments
	input >> parsed_word;
	while ( ! parsed_word.empty() ) {
		m_args.push_back( parsed_word );
		if ( input.eof() )
			break;
		input >> parsed_word;
	}
}

