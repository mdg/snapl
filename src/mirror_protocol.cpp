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
#include "response.h"
#include "shession_store.h"
#include <sstream>
#include <iostream>


mirror_request_processor_c::mirror_request_processor_c(
		shession_store_i &store )
: request_processor_i( RT_MIRROR, store )
{}

void mirror_request_processor_c::process( const request_c &req
		, response_c &resp )
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

	m_store.mirror( shession_id, user_id );
}


export_request_processor_c::export_request_processor_c(
		shession_store_i &store )
: request_processor_i( RT_EXPORT, store )
{}

void export_request_processor_c::process( const request_c &req
		, response_c &resp )
{
	time_t now( time( NULL ) );

	resp.ok();

	// need a way to iterate over sessions
	const_shession_iterator_c it( m_store.begin() );
	for ( ; it!=m_store.end(); ++it ) {
		std::ostringstream out;
		out << it->shession_id() << " " << it->expiration() - now;
		if ( ! it->user_id().empty() ) {
			out << " " << it->user_id();
		}
		resp.write_line( out.str() );
	}
}


mirror_protocol_c::mirror_protocol_c( short port, shession_store_i &store )
: protocol_c( port )
, m_create( store )
, m_export( store )
{
	add( m_create );
	add( m_export );
}

mirror_protocol_c::~mirror_protocol_c()
{}

