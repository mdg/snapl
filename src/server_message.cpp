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

#include "server_message.h"
#include "snapl/net/connection.h"

using namespace snapl;


server_message_c::server_message_c( const std::string &request
		, connection_i *conn )
: m_request(request)
, m_response()
, m_connection( conn )
{}

server_message_c::~server_message_c()
{}


short server_message_c::port() const
{
	return m_connection->port();
}

connection_i * server_message_c::release_connection()
{
	connection_i *released = m_connection;
	m_connection = NULL;
	return released;
}

