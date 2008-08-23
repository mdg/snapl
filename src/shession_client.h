#ifndef SHESSION_CLIENT_H
#define SHESSION_CLIENT_H
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


/**
 * Client for a shessiond.
 */
class shession_client_i
{
public:
	virtual ~shession_client_i() {}

	/**
	 * Create the a session for the given session_id.
	 */
	virtual void create_session( const std::string &session_id ) = 0;

	/**
	 * Check if a session is alive.
	 */
	virtual bool live_session( const std::string &session_id ) = 0;

	/**
	 * Kill a session that is no longer valid.
	 */
	virtual void kill_session( const std::string &session_id ) = 0;
};


/**
 * Concrete implementation of this.  Probably need to rename
 * and move to another place later.
 */
class shession_client_c
: public shession_client_i
{
public:
	shession_client_c();
	virtual ~shession_client_c();

	/**
	 * Open the client to a shessiond at the given URL and port.
	 */
	bool open( const std::string &url, short port );
	/**
	 * Close the shession_client_c
	 */
	void close();

	virtual void create_session( const std::string &session_id );
	virtual bool live_session( const std::string &session_id );
	virtual void kill_session( const std::string &session_id );

private:
	int m_socket;
};


#endif
