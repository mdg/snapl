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


#include "request_reader.h"
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <errno.h>
#include "request.h"
#include "request_type.h"
#include "connected_socket.h"


request_reader_c::request_reader_c()
{}

request_reader_c::~request_reader_c()
{}


request_c * request_reader_c::create_request( connection_i &conn ) const
{
	std::string request_line;
	conn.read_line( request_line );
	if ( request_line.empty() ) {
		// no input here
		return NULL;
	}

	std::istringstream stream( request_line );
	std::string request;
	std::string session_id;
	stream >> request;
	stream >> session_id;

	request_type_c req_type( request );
	// std::cerr << "req_type = " << (int) req_type << std::endl;
	request_c *req = new request_c( req_type.type(), session_id );
	std::string token_name;

	// check if this is a close request
	if ( req_type.type() == RT_CLOSE ) {
		std::cerr << "close!\n";
		// return the close request
	} else if ( req_type.type() == RT_NULL ) {
		// do nothing here.  return it with an RT_NULL for now.
	}

	return req;
}

