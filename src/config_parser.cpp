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
	std::string key_chunk;
	std::string value_chunk;
	std::string key;
	std::string value;

	while ( ! m_input.eof() ) {
		// separate the line into chunks broken by the first '='
		getline( m_input, line );
		std::istringstream line_parser( line );

		getline( line_parser, key_chunk, '=' );
		getline( line_parser, value_chunk );

		// parse the key and values out of the chunks
		std::istringstream key_parser( key_chunk );
		std::istringstream value_parser( value_chunk );

		key_parser >> key;
		value_parser >> value;

		if ( ! ( key.empty() || value.empty() ) ) {
			if ( value[ value.length() - 1 ] == '\r' ) {
				value.erase( value.length() - 1 );
			}
			m_config[ key ] = value;
		}
	}
}


bool config_parser_c::configured( const std::string &key ) const
{
	return m_config.find( key ) != m_config.end();
}

const std::string & config_parser_c::str_value( const std::string &key ) const
{
	std::map< std::string, std::string >::const_iterator it;
	it = m_config.find( key );
	if ( it == m_config.end() ) {
		return m_empty_value;
	}
	return it->second;
}

int config_parser_c::int_value( const std::string &key ) const
{
	std::string str_val( str_value( key ) );
	std::istringstream parser( str_val );
	int value( 0 );
	parser >> value;
	return value;
}

