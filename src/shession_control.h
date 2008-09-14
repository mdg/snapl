#ifndef SHESSION_CONTROL_H
#define SHESSION_CONTROL_H
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

#include <map>
#include <memory>

class connection_listener_i;
class protocol_c;
class request_c;
class request_processor_c;
class request_reader_i;


/**
 * The controlling object for the overall
 * shession application.
 */
class shession_control_c
{
	typedef std::map< short, request_reader_i * > reader_map;
	typedef reader_map::const_iterator reader_iterator;
	typedef std::map< short, protocol_c * > protocol_map;
	typedef protocol_map::iterator protocol_iterator;

public:
	/**
	 * Construct the shession control
	 * object.
	 */
	shession_control_c( connection_listener_i & );

	/**
	 * Destroy the shession_control_c
	 */
	~shession_control_c();

	/**
	 * Add a reader and connect it to the given port.
	 */
	void add_reader( short port, request_reader_i & );

	/**
	 * Add a protocol to be executed.
	 */
	void add_protocol( short port, protocol_c & );

	/**
	 * Start the shession
	 * This isn't a threaded solution.
	 */
	bool main_loop();
	/**
	 * Run one iteration of the main loop.
	 */
	void iterate();

private:
	connection_listener_i &m_connection_factory;
	reader_map m_reader;
	protocol_map m_protocol;
};


#endif

