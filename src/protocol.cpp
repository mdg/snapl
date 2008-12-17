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
#include "request_processor.h"
#include <iostream>


protocol_c::protocol_c( short port )
: m_port( port )
, m_processor()
{}

protocol_c::~protocol_c()
{}

void protocol_c::add( action_i &proc )
{
	m_processor[ proc.request_type() ] = &proc;
}

action_i * protocol_c::processor(
		const std::string &req_type )
{
	processor_iterator it( m_processor.find( req_type ) );
	if ( it == m_processor.end() ) {
		std::cerr << "No processor found for req_type = " << req_type
			<< ".  Supported types are: ";
		for ( it=m_processor.begin(); it!=m_processor.end(); ++it ) {
			std::cerr << it->first << ", ";
		}
		std::cerr << std::endl;
		return NULL;
	}
	return it->second;
}

