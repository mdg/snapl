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

#include "snapl/protocol.h"
#include "snapl/service.h"
#include <iostream>

using namespace snapl;


protocol_c::protocol_c( short port )
: m_name()
, m_service()
, m_port( port )
, m_silent( false )
{}

protocol_c::~protocol_c()
{}

service_i * protocol_c::service( const std::string &req_type )
{
	service_iterator it( m_service.find( req_type ) );
	if ( it == m_service.end() ) {
		std::cerr << "No service found for req_type = " << req_type
			<< ".  Supported types are: ";
		for ( it=m_service.begin(); it!=m_service.end(); ++it ) {
			std::cerr << it->first << ", ";
		}
		std::cerr << std::endl;
		return NULL;
	}
	return it->second;
}

