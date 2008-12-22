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

class server_message_c;


/**
 * A server message queue.
 */
class server_queue_i
{
public:
	virtual ~server_queue_i() {}

	/**
	 * Pop a message with a request off of the queue.
	 */
	virtual server_message_c * pop() = 0;

	/**
	 * Push a message back onto the queue with a response
	 */
	virtual void push( server_message_c * ) = 0;
};


#endif

