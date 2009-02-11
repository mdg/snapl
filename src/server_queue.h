#ifndef SERVER_QUEUE_H
#define SERVER_QUEUE_H
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

#include <queue>
#include <memory>

class mutex_i;
class server_message_c;


/**
 * A server message queue.
 */
class server_queue_i
{
public:
	virtual ~server_queue_i() {}

	/**
	 * Push a new server message into the queue to be processed.
	 */
	virtual void push_inbound( server_message_i * ) = 0;

	/**
	 * Pop a message with a request off of the queue.
	 */
	virtual server_message_i * pop_inbound() = 0;
	/**
	 * Push a message back onto the queue with a response
	 */
	virtual void push_outbound( server_message_i * ) = 0;

	/**
	 * Pop a message with a response off the outbound queue.
	 */
	virtual server_message_i * pop_outbound() = 0;
};


/**
 * Lockable queue for managing server messages.
 */
class server_queue_c
: server_queue_i
{
public:
	server_queue_c();
	/**
	 * Request queue that takes a mutex as a parameter for being
	 * threadsafe.  This is optional if queue won't run in threaded
	 * environment.  The request queue will own this mutex and destroy
	 * the mutex when the queue is destroyed.
	 */
	server_queue_c( mutex_i * );
	virtual ~server_queue_c();

	/**
	 * Push a request to end of the queue.
	 * The request owns the pointer after it's passed in.
	 */
	virtual void push( server_message_c * );
	/**
	 * Pop a request from the front of the queue.
	 * The caller owns the pointer after it's returned.
	 */
	virtual server_message_c * pop();

private:
	std::queue< server_message_c * > m_requests;
	std::auto_ptr< mutex_i > m_mutex;
};


#endif

