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

#include "connection_factory.h"

/**
 * A class that accepts socket connections
 * and returns open sockets.
 */
class connection_acceptor_c
: public connection_factory_i
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
	 * Open the acceptor on the given port.
	 * @port The port on which connections should be accepted.
	 */
	bool open( int port, int backlog = DEFAULT_BACKLOG );

	/**
	 * Closes the acceptor.
	 */
	void close();

	/**
	 * Get an open connection from the listener.
	 * @return 
	 */
	virtual int connection();

private:
	int m_port;
	int m_listener;
};


#endif

