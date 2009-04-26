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
#include "snapl/arg.h"
#include <sstream>

#include <iostream>

namespace snapl {


std::ostream & operator << ( std::ostream &out, const message_arg_c &arg )
{
	bool use_quotes( false );

	if ( arg.get().empty() ) {
		use_quotes = true;
	} else {
		const std::string &txt( arg.get() );
		std::string::const_iterator it;
		for ( it=txt.begin(); it!=txt.end(); ++it ) {
			if ( isspace( *it ) ) {
				use_quotes = true;
				break;
			}
		}
	}

	if ( use_quotes ) {
		out << '"' << arg.get() << '"';
	} else {
		out << arg.get();
	}

	return out;
}

std::istream & operator >> ( std::istream &in, message_arg_c &arg )
{
	std::ostringstream out;
	bool quoted( false );
	bool backslash( false );

	while ( in.peek() > 0 ) {
		char c( in.get() );
		if ( c == '"' ) {
			quoted = ! quoted;
		} else if ( isspace( c ) && ! quoted ) {
			break;
		} else {
			out << c;
		}
	}

	arg.set( out.str() );

	return in;
}


message_arg_list_c::message_arg_list_c()
{
	m_arg.reserve( 8 );
}

message_arg_list_c::~message_arg_list_c()
{}

void message_arg_list_c::operator = ( const arg_list_c &src )
{
	m_arg.clear();

	std::string value;
	arg_list_c::iterator it( src.begin() );
	for ( ; it!=src.end(); ++it ) {
		it->write( value );
		m_arg.push_back( message_arg_c( value ) );
	}
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
		out << *it;
		insert_space = true;
	}

	return out.str();
}

void message_arg_list_c::parse( const std::string &line )
{
	std::istringstream in( line );
	message_arg_c arg;

	in >> arg;
	while ( in ) {
		m_arg.push_back( arg );
		in >> arg;
	}
}


} // namespace

