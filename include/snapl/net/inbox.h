#ifndef SNAPL_INBOX_H
#define SNAPL_INBOX_H
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

#include "snapl/queue.h"
#include <map>
#include <memory>

class connection_listener_i;
class message_reader_c;
class request_c;
class response_c;
class server_message_c;


/**
 * An inbox for receiving requests to a snapl application.
 */
class inbox_c
{
public:
	/**
	 * Construct the inbox class.
	 */
	inbox_c( connection_listener_i &, queue_back_i< server_message_c > &
			, queue_front_i< server_message_c > & );

	/**
	 * Destroy the inbox
	 */
	~inbox_c();

	/**
	 * Listen on a given port.
	 */
	void listen( short port );

	/**
	 * Run the inbox loop continuously.
	 */
	void loop();

	/**
	 * Run one iteration of the inbox loop.
	 */
	void iterate();

	/**
	 * Replace complete connections back in the listener.
	 */
	void replace_connections();

	/**
	 * Resume reading partial messages and push them onto the queue
	 * for processing.
	 */
	void read_partial_messages();

	/**
	 * Read new messages and push it to the request queue for processing.
	 */
	void read_new_messages();

private:
	connection_listener_i &m_listener;
	queue_back_i< server_message_c > &m_request;
	queue_front_i< server_message_c > &m_complete;
	std::queue< message_reader_c * > m_partial;
};


#endif

