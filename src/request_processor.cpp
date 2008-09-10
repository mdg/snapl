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
#include "connection.h"
#include "request.h"
#include "shession_store.h"


request_processor_c::request_processor_c( shession_store_i &store )
: m_store( store )
{}


void request_processor_c::process( const request_c &req
		, connection_i &conn )
{
	switch ( req.request_type() ) {
		case RT_CREATE_SESSION:
			std::cerr << "process create request\n";
			process_create( req );
			break;
		case RT_SESSION_STATUS:
			std::cerr << "process status request\n";
			process_status( req, conn );
			break;
		case RT_KILL_SESSION:
			std::cerr << "process kill request\n";
			process_kill( req );
			break;
		case RT_CLOSE:
			// process_close( req, conn );
			break;
	}
}

bool request_processor_c::session_status( const std::string &session_id ) const
{
	return m_store.live_session( session_id );
}

void request_processor_c::process_create( const request_c &req )
{
	m_store.create_session( req.session_id() );
}


void request_processor_c::process_status( const request_c &req
		, connection_i &conn )
{
	std::cerr << "begin process_status\n";
	bool live( m_store.renew_session( req.session_id() ) );
	conn.write_line( live ? "live" : "dead" );
	std::cerr << "end process_status\n";
}


void request_processor_c::process_kill( const request_c &req )
{
	m_store.kill_session( req.session_id() );
}

