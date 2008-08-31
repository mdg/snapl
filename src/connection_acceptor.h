#ifndef CONNECTION_ACCEPTOR_H
#define CONNECTION_ACCEPTOR_H
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

#include "connection_listener.h"
#include <map>
#include <queue>


/**
 * A class that accepts socket connections
 * and returns open sockets.
 */
class connection_acceptor_c
: public connection_listener_i
{
	static const int DEFAULT_BACKLOG = 128;

public:
	/**
	 * Constructor for the acceptor class.
	 */
	connection_acceptor_c();

	/**
	 * Destructor.  Calls close.
	 */
	virtual ~connection_acceptor_c();

	/**
	 * Open the service and admin acceptors on the given ports.
	 * @service_port The port on which service connections are be accepted.
	 * @admin_port   The port on which admin connections should be accepted.
	 * @return  true if the sockets were opened successfully.
	 */
	bool open( int service_port, int admin_port
			, int backlog = DEFAULT_BACKLOG );

	/**
	 * Closes both the normal and admin listeners.
	 */
	void close();

	/**
	 * Get a ready connection.
	 * The connection may come from the normal or admin listener.
	 * @return 
	 */
	virtual connection_i * connection();

private:
	static int open_listener( int port, int backlog );
	void accept( int listener );

	connection_i * old_connection( int );

private:
	int m_service_port;
	int m_service_listener;
	int m_admin_port;
	int m_admin_listener;

	std::map< int, connection_i * > m_open;
	std::queue< connection_i * > m_ready;
};


#endif

