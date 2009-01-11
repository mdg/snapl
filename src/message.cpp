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

#include "message.h"

#include <iostream>


message_arg_list_c::~message_arg_list_c()
{
	std::vector< message_arg_i * >::iterator it;
	for ( it=m_arg.begin(); it!=m_arg.end(); ++it ) {
		delete *it;
	}
	m_arg.clear();
}

std::string message_arg_list_c::argv( int i ) const
{
	std::string value;
	m_arg[i]->get_string( value );
	return value;
}

void message_arg_list_c::argv( int i, std::string &argv ) const
{
	if ( i >= m_arg.size() ) {
		std::cerr << "i( " << i << " ) > m_arg.size()\n";
	}

	message_arg_i *arg( m_arg[i] );
	if ( arg == NULL ) {
		std::cerr << "arg is null\n";
	}

	arg->get_string( argv );
}

std::string message_arg_list_c::str() const
{
	std::ostringstream out;
	std::string value;
	int argc( size() );
	for ( int i(0); i<argc; ++i ) {
		argv( i, value );

		if ( i > 0 ) {
			out << " ";
		}
		out << value;
	}

	return out.str();
}


message_c::message_c()
: m_arg()
{}

message_c::message_c( const std::string &args )
: m_arg()
{
	parse_args( args );
}

message_c::~message_c()
{}


void message_c::add_arg( const std::string &arg )
{
	// m_arg.add_arg( arg );
}

std::string message_c::argv( int i ) const
{
	std::string arg;
	m_arg.argv( i, arg );
	return arg;
}


void message_c::parse_args( const std::string &args )
{
	/*
from request.cpp
	std::istringstream input( request_line );
	std::string parsed_word;

	// parse the arguments
	input >> parsed_word;
	while ( ! parsed_word.empty() ) {
		// m_args.push_back( parsed_word );
		if ( input.eof() )
			break;
		input >> parsed_word;
	}
	*/
	/*
	std::istringstream in( args );
	std::string value;
	while ( in >> value ) {
		add_arg( value );
	}
	*/
}

