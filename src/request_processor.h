#ifndef REQUEST_PROCESSOR_H
#define REQUEST_PROCESSOR_H

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

#include <set>
#include <string>


class connection_i;
class request_c;

class request_processor_c
{
public:
	/**
	 * Process a request
	 * This should take a response_c object instead of
	 * a connection.
	 */
	void process( const request_c &, connection_i & );

	bool session_status( const std::string &session_id ) const;

private:
	void process_create( const request_c & );
	void process_status( const request_c &, connection_i & );
	void process_kill( const request_c & );

	std::set< std::string > m_session;
};


#endif

