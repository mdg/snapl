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
#include "request.h"
#include "connection.h"
#include <sstream>


mirror_request_processor_c::mirror_request_processor_c(
		shession_store_i &store )
: request_processor_i( RT_NULL, store )
{}

void mirror_request_processor_c::process( const request_c &req
		, connection_i &conn )
{
	if ( req.argc() == 0 ) {
		// error
		// write to the log, don't write anything back to the sender
		return;
	}
	if ( req.argc() > 2 ) {
		// error
		// write to the log, don't write anything back to the sender
		return;
	}

	// process the request
	std::string shession_id( req.argv( 0 ) );
	std::string user_id;
	if ( req.argc() == 2 ) {
		user_id = req.argv( 1 );
	}

	// m_store.create_session( shession_id, user_id );
}


mirror_dump_processor_c::mirror_dump_processor_c( shession_store_i &store )
: request_processor_i( RT_NULL, store )
{}

void mirror_dump_processor_c::process( const request_c &req
		, connection_i &conn )
{
	std::ostringstream out;
	time_t now( time( NULL ) );

	// need a way to iterate over sessions
}


mirror_protocol_c::mirror_protocol_c( short port, shession_store_i &store )
: protocol_c( port )
, m_create( store )
{
	add( m_create );
}

mirror_protocol_c::~mirror_protocol_c()
{}

