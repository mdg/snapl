#ifndef SNAPL_DISPATCHER_H
#define SNAPL_DISPATCHER_H
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

namespace snapl {

class protocol_c;
class server_message_c;


/**
 * The controlling object for the overall
 * shession application.
 */
class dispatcher_c
{
	typedef std::map< short, protocol_c * > protocol_map;
	typedef protocol_map::iterator protocol_iterator;

public:
	/**
	 * Construct the shession control
	 * object.
	 */
	dispatcher_c( queue_front_i< server_message_c > &request_queue
			, queue_back_i< server_message_c > &response_queue );

	/**
	 * Destroy the dispatcher_c
	 */
	~dispatcher_c();

	/**
	 * Add a protocol to be executed.
	 */
	void add( protocol_c & );

	/**
	 * Start the shession
	 * This isn't a threaded solution.
	 */
	bool main_loop();
	/**
	 * Run one iteration of the main loop.
	 */
	void iterate();
	/**
	 * Dispatch a server message through to the correct protocol.
	 * Dispatch will own the pointer that's passed in.
	 */
	void dispatch( server_message_c & );

	protocol_c * find_protocol( int port );

private:
	queue_front_i< server_message_c > &m_request_queue;
	queue_back_i< server_message_c > &m_response_queue;
	protocol_map m_protocol;
};


} // snapl

#endif

