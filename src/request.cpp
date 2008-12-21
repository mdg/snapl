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


const std::string request_c::CREATE( "create" );
const std::string request_c::RENEW( "renew" );
const std::string request_c::KILL( "kill" );
const std::string request_c::CLOSE( "close" );

const std::string request_c::MIRROR( "mirror" );
const std::string request_c::EXPORT( "export" );


request_c::request_c( const std::string &request_line )
: m_type()
, m_args()
, m_port( 0 )
{
	std::istringstream input( request_line );
	std::string parsed_word;

	// get the request_type
	input >> parsed_word;
	m_type = parsed_word;

	// parse the arguments
	input >> parsed_word;
	while ( ! parsed_word.empty() ) {
		m_args.push_back( parsed_word );
		if ( input.eof() )
			break;
		input >> parsed_word;
	}
}
