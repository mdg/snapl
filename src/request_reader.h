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

#include <string>
#include "request_type.h"

class connection_i;
class request_c;


/**
 * Interface to abstract different kinds of request_readers which
 * will be able to create different kinds of requests.
 */
class request_reader_i
{
public:
	/**
	 * Virtual destructor
	 */
	virtual ~request_reader_i() {}

	/**
	 * Create a request given a connection.
	 */
	virtual request_c * create_request( connection_i & ) const = 0;
};


/**
 * A class to read requests from an existing connection.
 */
class request_reader_c
: public request_reader_i
{
public:
	/**
	 * Construct a request reader object with a given
	 * connection.
	 */
	request_reader_c();
	/**
	 * Destroy the request reader object.
	 */
	~request_reader_c();

	/**
	 * Create a request by parsing the input from
	 * the socket.
	 */
	request_c * create_request( connection_i & ) const;
};


#endif

