#ifndef CONNECTED_SOCKET_H
#define CONNECTED_SOCKET_H
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

#include "connection.h"
#include "line_parser.h"


/**
 * A network socket connection object to handle
 * connections and their input and output.
 */
class connected_socket_c
: public connection_i
{
public:
	/**
	 * Construct the connected socket object, given an open
	 * socket.
	 */
	connected_socket_c( int socket );
	virtual ~connected_socket_c();

	/**
	 * Read a line of input from this connection.
	 */
	virtual void read_line( std::string& );

	/**
	 * Write a string back to the connection.
	 */
	virtual void write_line( const std::string & );

private:
	int m_socket;
	line_parser_c m_line_parser;
};


#endif

