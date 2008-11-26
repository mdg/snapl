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


shession_c::shession_c( const std::string &shession_id
		, const std::string &user_id )
: m_shession_id( shession_id )
, m_user_id( user_id )
, m_expiration( 0 )
{}


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


void shession_store_c::create( const std::string &shession_id
		, const std::string &user_id )
{
	std::map< std::string, shession_c >::iterator it;
	it = m_store.find( shession_id );

	time_t now( (*m_timer)() + m_timeout );
	if ( it == m_store.end() ) {
		shession_c sh( shession_id, user_id );
		sh.expire_at( now );
		std::pair< std::string, shession_c > insertion(
				shession_id, sh ); 
		m_store.insert( insertion );
	} else {
		// log a warning that it already exists
		// but update the time to the most recent expiration
		it->second.expire_at( now );
	}
}

bool shession_store_c::live( const std::string &session_id ) const
{
	std::map< std::string, shession_c >::const_iterator it;
	// look for the session_id
	it = m_store.find( session_id );
	if ( it == m_store.end() ) {
		return false;
	}

	time_t now( (*m_timer)() );
	// check that it hasn't expired
	return ! it->second.expired( now );
}

bool shession_store_c::renew( const std::string &session_id )
{
	std::map< std::string, shession_c >::iterator it;
	// look for the session_id
	it = m_store.find( session_id );
	if ( it == m_store.end() ) {
		return false;
	}

	time_t now( (*m_timer)() );
	// check that it hasn't expired
	if ( it->second.expired( now ) ) {
		m_store.erase( it );
		return false;
	}

	// renew the live session timeout
	it->second.expire_at( now + m_timeout );
	return true;
}

void shession_store_c::kill( const std::string &session_id )
{
	m_store.erase( session_id );
}

void shession_store_c::mirror( const std::string &shession_id
		, const std::string &user_id )
{
	time_t expiration( (*m_timer)() + m_timeout );
	std::map< std::string, shession_c >::iterator it;
	it = m_store.find( shession_id );

	if ( it == m_store.end() ) {
		shession_c new_sh( shession_id, user_id );
		new_sh.expire_at( expiration );
		std::pair< std::string, shession_c > insertion(
				shession_id, new_sh );
		m_store.insert( insertion );
	} else {
		it->second.expire_at( expiration );
	}
}


int shession_store_c::kill_expired()
{
	int kill_count( 0 );
	std::map< std::string, shession_c >::iterator it;
	time_t now( (*m_timer)() );
	for ( it=m_store.begin(); it!=m_store.end(); ++it ) {
		if ( it->second.expired( now ) ) {
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

