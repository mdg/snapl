#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H
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
#include "response.h"
#include <memory>

class connection_i;


class server_message_c
{
public:
	server_message_c( const std::string &request, connection_i & );
	~server_message_c();

	const std::string & request_type() const { return m_request.type(); }
	const request_c & request() const { return m_request; }
	const response_c & response() const { return m_response; }
	response_c & response() { return m_response; }

	short port() const;
	const std::string & protocol() const { return m_request.protocol(); }

	connection_i & connection() { return m_connection; }

private:
	request_c m_request;
	response_c m_response;
	connection_i &m_connection;
};


#endif

