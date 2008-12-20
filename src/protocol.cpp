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

#include "protocol.h"
#include "action.h"
#include <iostream>


protocol_c::protocol_c( short port )
: m_name()
, m_action()
, m_port( port )
, m_silent( false )
{}

protocol_c::~protocol_c()
{}

void protocol_c::add( action_i &action )
{
	m_action[ action.request_type() ] = &action;
}

action_i * protocol_c::action( const std::string &req_type )
{
	action_iterator it( m_action.find( req_type ) );
	if ( it == m_action.end() ) {
		std::cerr << "No processor found for req_type = " << req_type
			<< ".  Supported types are: ";
		for ( it=m_action.begin(); it!=m_action.end(); ++it ) {
			std::cerr << it->first << ", ";
		}
		std::cerr << std::endl;
		return NULL;
	}
	return it->second;
}

