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

class connection_i;


/**
 * Client for a shessiond.
 */
class shession_client_i
{
public:
	/**
	 * Destroy the implemented session client object.
	 */
	virtual ~shession_client_i() {}

	/**
	 * Create the a session for the given session_id.
	 */
	virtual void create_session( const std::string &session_id ) = 0;

	/**
	 * Check if a session is alive.
	 */
	virtual bool renew_session( const std::string &session_id ) = 0;

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
	/**
	 * Construct the shession_client object.
	 * Need to modify this so it takes a connection_i parameter.
	 */
	shession_client_c();
	/**
	 * Destory the implemented session_client object.
	 */
	virtual ~shession_client_c();

	/**
	 * Open the client to a shessiond at the given URL and port.
	 */
	bool open( const std::string &url, short port );
	/**
	 * Close the shession_client_c
	 */
	void close();

	/**
	 * Send a create_session request for the given session_id.
	 */
	virtual void create_session( const std::string &session_id );
	/**
	 * Send a live_session request for the given session_id
	 */
	virtual bool renew_session( const std::string &session_id );
	/**
	 * Send a kill_session request for the given session_id
	 */
	virtual void kill_session( const std::string &session_id );

private:
	/**
	 * Write a request to the connection.
	 */
	void write_request( const std::string &request_type
			, const std::string &session_id );
	// need to modify this so it can be passed in,
	// not created internally
	std::auto_ptr< connection_i > m_connection;
};


#endif

