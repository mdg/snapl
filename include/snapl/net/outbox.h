#ifndef SNAPL_OUTBOX_H
#define SNAPL_OUTBOX_H
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

class server_message_c;


/**
 * An outbox for sending requests from a snapl application.
 */
class outbox_c
{
public:
	/**
	 * Construct the outbox class.
	 */
	outbox_c( queue_front_i< server_message_c > &response_queue
			, queue_back_i< server_message_c > &complete_queue );

	/**
	 * Destroy the outbox
	 */
	~outbox_c();

	/**
	 * Run one iteration of the outbox loop.
	 */
	void iterate();

	/**
	 * Write messages and push them out as complete.
	 */
	void write_messages();

private:
	queue_front_i< server_message_c > &m_response;
	queue_back_i< server_message_c > &m_complete;
};


#endif

