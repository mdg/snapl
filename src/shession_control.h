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


#include <list>
#include <memory>

class connection_factory_i;
class request_c;
class request_processor_c;
class request_reader_c;


/**
 * The controlling object for the overall
 * shession application.
 */
class shession_control_c
{
public:
	/**
	 * Construct the shession control
	 * object.
	 */
	shession_control_c( connection_factory_i &, request_reader_c &
			, request_processor_c & );
	/**
	 * Destroy the shession_control_c
	 */
	~shession_control_c();

	/**
	 * Start the shession
	 * This isn't a threaded solution.
	 */
	bool main_loop();
	/**
	 * Run one iteration of the main loop.
	 */
	bool iterate();

private:
	connection_factory_i &m_connection_factory;
	request_reader_c & m_reader;
	request_processor_c &m_processor;
};


#endif

