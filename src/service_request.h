#ifndef SERVICE_REQUEST_H
#define SERVICE_REQUEST_H
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

#include "request.h"
#include <memory>


/**
 * The untyped server_request class for the server to use while reading
 * info as a string.
 */
class service_request_c
: public request_c
{
public:
	service_request_c( const std::string &request );
	~service_request_c();

	const std::string & request_type() const { return m_request.type(); }
	const request_c & request() const { return m_request; }
	const response_c & response() const { return m_response; }
	response_c & response() { return m_response; }

	short port() const;
	const std::string & protocol() const { return m_request.protocol(); }

	connection_i & connection() { return m_connection; }
};


#endif

