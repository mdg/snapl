#ifndef SNAPL_CLIENT_H
#define SNAPL_CLIENT_H
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

#include "snapl/command.h"
#include "snapl/message.h"

class connection_i;
// class message_queue_factory_i;


/**
 * Implemented class of the client interface.
 */
class client_c
{
public:
	client_c();
	/**
	 * Eventually, this should take a set of connections rather
	 * than a single connection.
	 */
	client_c( connection_i & );

	void send_request( command_i & );

	void wait_for_response( command_i & );

private:
	// client_factory_i &m_factory;
	connection_i *m_connection;
};


#endif

