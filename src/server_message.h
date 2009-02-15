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

#include "snapl/message.h"
#include <memory>

class connection_i;
class response_c;


/**
 * The server message class for passing requests & responses to and from
 * the protocols.
 */
class server_message_c
{
public:
	/**
	 * Construct the server message from a line of text and a connection.
	 */
	server_message_c( const std::string &request, connection_i & );
	/**
	 * Destroy the server_message.
	 */
	~server_message_c();

	/**
	 * Get the request type from this message.
	 */
	const std::string & request_type() const { return m_request.argv(0); }
	/**
	 * Get the request object from this message.
	 */
	const message_c & request() const { return m_request; }
	/**
	 * Get the const message for this server message response.
	 */
	const message_c & response() const { return m_response; }
	/**
	 * Get the non-const message for this server message response.
	 */
	message_c & response() { return m_response; }

	/**
	 * Set response for writing back to the client
	 */
	void set_response( const response_c & );

	/**
	 * Get the port of this server_message
	 */
	short port() const;

	/**
	 * Get the connection from which this message came.
	 */
	connection_i & connection() { return m_connection; }

private:
	const message_c m_request;
	message_c m_response;
	connection_i &m_connection;
};


#endif

