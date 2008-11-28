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

#include "request_processor.h"
#include <iostream>
#include "request.h"
#include "response.h"
#include "shession_generator.h"
#include "shession_store.h"


request_processor_i::request_processor_i( request_type_e req_type
		, shession_store_i &store )
: m_store( store )
, m_request_type( req_type )
{}


create_request_processor_c::create_request_processor_c(
		shession_store_i &store, shession_generator_i &gen )
: request_processor_i( RT_CREATE_SESSION, store )
, m_generator( gen )
{}

void create_request_processor_c::process( const request_c &req
		, response_c &resp )
{
	if ( req.argc() > 1 ) {
		// error
		resp.err();
		return;
	}

	// process the request
	std::string user_id;
	if ( req.argc() == 1 ) {
		user_id = req.argv( 0 );
	}
	std::string shession_id( m_generator.shession_id( user_id ) );

	m_store.create( shession_id, user_id );
	resp.ok( shession_id );
}


renew_request_processor_c::renew_request_processor_c( shession_store_i &store )
: request_processor_i( RT_RENEW_SESSION, store )
{}

void renew_request_processor_c::process( const request_c &req
		, response_c &resp )
{
	// verify arguments
	if ( req.argc() != 1 ) {
		resp.err( "wrong number of params" );
		return;
	}

	// make arguments meaningful
	const std::string &session_id( req.argv( 0 ) );

	// process arguments
	bool live( m_store.renew( session_id ) );
	resp.ok( live ? "live" : "dead" );
}


kill_request_processor_c::kill_request_processor_c( shession_store_i &store )
: request_processor_i( RT_KILL_SESSION, store )
{}

void kill_request_processor_c::process( const request_c &req
		, response_c &resp )
{
	if ( req.argc() != 1 ) {
		// error
		resp.err();
		return;
	}

	const std::string &session_id( req.argv( 0 ) );
	m_store.kill( session_id );
	resp.ok();
}


close_request_processor_c::close_request_processor_c( shession_store_i &store )
: request_processor_i( RT_CLOSE, store )
{}

void close_request_processor_c::process( const request_c &req
		, response_c &resp )
{
	// need to actually do something here.
	resp.ok();
}

