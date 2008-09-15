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

#include "mirror_protocol.h"


mirror_create_processor_c::mirror_create_processor_c(
		shession_store_i &store )
: request_processor_i( RT_NULL, store )
{}

void mirror_create_processor_c::process( const request_c &req
		, connection_i &conn )
{
}


mirror_protocol_c::mirror_protocol_c( short port, shession_store_i &store )
: protocol_c( port )
, m_create( store )
{
	add( m_create );
}

mirror_protocol_c::~mirror_protocol_c()
{}

