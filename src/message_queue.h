#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H
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


/**
 * A server message queue.
 */
class server_queue_i
{
public:
	virtual ~server_message_queue_i() {}

	/**
	 * Pop a request message off of the queue.
	 */
	virtual request_message_i * pop() = 0;

	/**
	 * Push a response message onto the queue.
	 */
	virtual void push( response_message_i * ) = 0;
};


class client_queue_i
{
public:
	virtual ~client_message_queue_i() {}

	virtual void push( request_message_i * ) = 0;

	virtual response_message_i * pop() = 0;
};


#endif

