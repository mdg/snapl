#ifndef REQUEST_READER_H
#define REQUEST_READER_H
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


#include <sstream>
#include "request_type.h"

class request_c;


/**
 * A class to read requests from an existing connection.
 */
class request_reader_c
{
public:
	/**
	 * Construct a request reader object with a given
	 * connection.
	 */
	request_reader_c( int connection );
	/**
	 * Destroy the request reader object.
	 */
	~request_reader_c();

	/**
	 * Check if this request reader is still open.
	 */
	bool connected() const { return m_connection; }

	/**
	 * Close this request reader and it's associated
	 * resources, like the socket connection.
	 */
	void close();

	/**
	 * Create a request by parsing the input from
	 * the socket.
	 */
	request_c * create_request();

	/**
	 * Release the connection for this request reader.
	 */
	int release_connection();

private:
	std::string readline() const;

	static request_type_e get_request_type( const std::string& req_type );

	int m_connection;
};


#endif

