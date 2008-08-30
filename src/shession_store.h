#ifndef SHESSION_STORE_H
#define SHESSION_STORE_H
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

#include <string>
#include <map>


/**
 * Abstract shession_store interface.
 */
class shession_store_i
{
public:
	/**
	 * Empty destructor to be overridden by implementing classes.
	 */
	virtual ~shession_store_i() {}

	/**
	 * Create a session for the given session_id.
	 */
	virtual void create_session( const std::string &session_id ) = 0;
	/**
	 * Check if the given session_id is live.
	 * Renew the session if it exists.
	 * @return true if it is still alive.
	 */
	virtual bool renew_session( const std::string &session_id ) = 0;
	/**
	 * Kill the given session if it exists.
	 */
	virtual void kill_session( const std::string &ession_id ) = 0;

	/**
	 * Check if any sessions are expired and kill them.
	 */
	virtual void kill_expired() = 0;
};


/**
 * Implementing class for the shession_store interface.
 * This might need to be renamed and put in a different file
 * at some point.  For now it will live here.
 */
class shession_store_c
{
public:
	shession_store_c( int timeout );

	/**
	 * Create a session for the given session_id.
	 */
	virtual void create_session( const std::string &session_id );
	/**
	 * Check if the given session_id is live.
	 * Renew the session if it exists.
	 * @return true if it is still alive.
	 */
	virtual bool renew_session( const std::string &session_id );
	/**
	 * Kill the given session if it exists.
	 */
	virtual void kill_session( const std::string &ession_id );

	/**
	 * Check if any sessions are expired and kill them.
	 */
	virtual void kill_expired();

private:
	int m_timeout;
	std::map< std::string, time_t > m_store;
};


#endif

