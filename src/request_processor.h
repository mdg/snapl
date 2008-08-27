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


class request_c;
class request_reader_c;


/**
 * An object that processes requests.  Probably needs to
 * be rewritten and reshaped at some point.
 */
class request_processor_c
{
public:
	/**
	 * Process a request
	 */
	void process( request_reader_c &, const request_c & );

	/**
	 * Check if this session is live
	 */
	bool session_status( const std::string &session_id ) const;

private:
	/**
	 * Process a create request.
	 */
	void process_create( const request_c & );
	/**
	 * Process a status request.
	 */
	void process_status( request_reader_c &, const request_c & );
	/**
	 * Process a kill request.
	 */
	void process_kill( const request_c & );

	std::set< std::string > m_session;
};


#endif

