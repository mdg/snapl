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
#include "request_reader.h"


void request_processor_c::process( request_reader_c &reader
		, const request_c &req )
{
	switch ( req.request_type() ) {
		case RT_CREATE_SESSION:
			process_create( req );
			break;
		case RT_SESSION_STATUS:
			process_status( reader, req );
			break;
		case RT_KILL_SESSION:
			process_kill( req );
			break;
	}
}

bool request_processor_c::session_status( const std::string &session_id ) const
{
	return m_session.find( session_id ) != m_session.end();
}


void request_processor_c::process_create( const request_c &req )
{
	m_session.insert( req.session_id() );
}


void request_processor_c::process_status( const request_c &req,
		, connection_i &conn )
{
	// std::cerr << "begin process_status\n";
	bool live( session_status( req.session_id() ) );
	conn.write( live ? "live" : "dead" );
	// std::cerr << "end process_status\n";
}


void request_processor_c::process_kill( const request_c &req )
{
	m_session.erase( req.session_id() );
}

