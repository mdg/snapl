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

#include "shession_store.h"


shession_store_c::shession_store_c( int timeout_seconds )
: m_default_timer()
, m_timer( &m_default_timer )
, m_timeout( timeout_seconds )
, m_store()
{}

shession_store_c::~shession_store_c()
{}

void shession_store_c::set_timer( shession_store_c::timer_c &timer )
{
	m_timer = &timer;
}


void shession_store_c::create_session( const std::string &session_id )
{
	m_store[ session_id ] = (*m_timer)() + m_timeout;
}

bool shession_store_c::renew_session( const std::string &session_id )
{
	std::map< std::string, time_t >::iterator it;
	// look for the session_id
	it = m_store.find( session_id );
	if ( it == m_store.end() ) {
		return false;
	}
	time_t now( (*m_timer)() );
	// check that it hasn't expired
	if ( now > it->second ) {
		m_store.erase( it );
		return false;
	}
	// renew the live session timeout
	it->second = now + m_timeout;
	return true;
}

void shession_store_c::kill_session( const std::string &session_id )
{
	m_store.erase( session_id );
}

int shession_store_c::kill_expired()
{
	int kill_count( 0 );
	std::map< std::string, time_t >::iterator it;
	time_t now( (*m_timer)() );
	for ( it=m_store.begin(); it!=m_store.end(); ++it ) {
		if ( now > it->second ) {
			m_store.erase( it );
			++kill_count; 
		}
	}
	return kill_count;
}

int shession_store_c::size() const
{
	return m_store.size();
}

