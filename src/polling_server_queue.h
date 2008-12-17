#ifndef POLLING_SERVER_QUEUE_H
#define POLLING_SERVER_QUEUE_H
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

#include "server_queue.h"


class connection_listener_i;


/**
 * A connection polling server message queue.
 */
class polling_server_queue_c
: public server_queue_i
{
public:
	polling_server_queue_c( connection_listener_i &listener );

	virtual ~polling_server_queue_c();

	/**
	 * Pop a request message off of the queue.
	 */
	virtual request_message_i * pop();

	/**
	 * Push a response message onto the queue.
	 */
	virtual void push( response_message_i * );

private:
	connection_listener_i &m_listener;
};


#endif

