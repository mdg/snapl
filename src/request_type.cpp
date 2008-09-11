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

#include "request_type.h"


const std::string request_type_c::CREATE( "create" );
const std::string request_type_c::RENEW( "status" );
const std::string request_type_c::KILL( "kill" );
const std::string request_type_c::CLOSE( "close" );
const std::string request_type_c::s_null;


request_type_c::request_type_c( request_type_e typ )
: m_type( typ )
, m_string( type_to_str( typ ) )
{}

request_type_c::request_type_c( const std::string &str )
: m_type( str_to_type( str ) )
, m_string( str )
{}


const std::string & request_type_c::type_to_str( request_type_e typ )
{
	switch ( typ ) {
		case RT_CREATE_SESSION:
			return CREATE;
		case RT_SESSION_STATUS:
			return RENEW;
		case RT_KILL_SESSION:
			return KILL;
		case RT_CLOSE:
			return CLOSE;
	}
	return s_null;
}

request_type_e request_type_c::str_to_type( const std::string & str )
{
	request_type_e typ( RT_NULL );

	if ( str == CREATE ) {
		typ = RT_CREATE_SESSION;
	} else if ( str == RENEW ) {
		typ = RT_SESSION_STATUS;
	} else if ( str == KILL ) {
		typ = RT_KILL_SESSION;
	} else if ( str == CLOSE ) {
		typ = RT_CLOSE;
	}

	return typ;
}

