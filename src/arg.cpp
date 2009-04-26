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

#include "snapl/arg.h"
#include "snapl/message_arg.h"
#include <sstream>
#include <iostream>

namespace snapl {



arg_list_c::arg_list_c()
{
}

arg_list_c::~arg_list_c()
{
	std::list< arg_i * >::iterator it( m_arg.begin() );
	for ( ; it!=m_arg.end(); ++it ) {
		delete *it;
	}
	m_arg.clear();
}

bool arg_list_c::operator = ( const message_arg_list_c &args )
{
	if ( m_arg.size() != args.argc() ) {
		std::cerr << "arg_list size != message_arg_list size\n";
		return false;
	}

	std::list< arg_i * >::iterator it( m_arg.begin() );
	message_arg_list_c::iterator msg_it( args.begin() );
	for ( ; it!=m_arg.end(); ++it ) {
		arg_i &arg( **it );
		if ( ! arg.parse( msg_it->get() ) ) {
			std::cerr << "msg_arg(" << msg_it->get() << ")" \
				" cannot be parsed.\n";
			return false;
		}
		++msg_it;
	}
	return true;
}


template <>
bool string_to_arg( std::string &value, const std::string &arg )
{
	value = arg;
	return true;
}

template <>
bool arg_to_string( std::string &arg, const std::string &value )
{
	arg = value;
	return true;
}

template <>
bool string_to_arg( int &value, const std::string &arg )
{
	std::istringstream in( arg );
	return in >> value;
}

template <>
bool arg_to_string( std::string &arg, const int &value )
{
	std::ostringstream out;
	if ( out << value ) {
		arg = out.str();
		return true;
	}
	return false;
}

template <>
bool string_to_arg( bool &value, const std::string &arg )
{
	std::istringstream in( arg );
	return in >> value;
}

template <>
bool arg_to_string( std::string &arg, const bool &value )
{
	arg = value ? "1" : "0";
	return true;
}


}

