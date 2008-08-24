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

#include "config_parser.h"
#include <sstream>


config_parser_c::config_parser_c( std::istream &input )
: m_input( input )
{
}

void config_parser_c::parse_input()
{
	std::string line;
	std::string key;
	std::string value;

	while ( ! m_input.eof() ) {
		getline( m_input, line );
		std::istringstream line_parser( line );

		getline( line_parser, key, '=' );
		getline( line_parser, value );

		m_config[ key ] = value;
	}
}


bool config_parser_c::configured( const std::string &key ) const
{
	return m_config.find( key ) != m_config.end();
}

const std::string & config_parser_c::value( const std::string &key ) const
{
	std::map< std::string, std::string >::const_iterator it;
	it = m_config.find( key );
	if ( it == m_config.end() ) {
		return m_empty_value;
	}
	return it->second;
}

