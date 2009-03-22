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

#include "snapl/request.h"
#include "snapl/message.h"
#include <sstream>

using namespace snapl;


request_c::request_c( const std::string &req_type )
: m_type( req_type )
, m_protocol()
, m_port( 0 )
{
	// add m_type as the first message argument
	m_args << m_type;
}

void request_c::copy_from( const message_c &msg )
{
	m_args = msg.args();
}

void request_c::copy_to( message_c &msg ) const
{
	msg.set_args( m_args );
}

