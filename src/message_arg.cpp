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

#include "snapl/message.h"
#include <sstream>

#include <iostream>


message_arg_list_c::message_arg_list_c()
{
	m_arg.reserve( 8 );
}

message_arg_list_c::~message_arg_list_c()
{}

void message_arg_list_c::operator = ( const arg_list_c &src )
{
	// currently unimplemented
}

const std::string & message_arg_list_c::argv( int i ) const
{
	return m_arg[i].get();
}

std::string message_arg_list_c::arg_string() const
{
	std::ostringstream out;
	std::vector< message_arg_c >::const_iterator it( m_arg.begin() );
	bool insert_space( false );
	for ( ; it!=m_arg.end(); ++it ) {
		if ( insert_space ) {
			out << " ";
		}
		out << it->get();
		insert_space = true;
	}

	return out.str();
}

void message_arg_list_c::parse( const std::string &line )
{
	std::istringstream in( line );
	std::string token;

	while ( parse_token( in, token ) ) {
		m_arg.push_back( message_arg_c( token ) );
	}
}

bool message_arg_list_c::parse_token( std::istream &in, std::string &token )
{
	return in >> token;
}

