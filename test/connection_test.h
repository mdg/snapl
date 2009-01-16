#ifndef CONNECTION_TEST_H
#define CONNECTION_TEST_H
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
#include <string>
#include <queue>


/**
 * A mocked connection for simulating a connection between 2 remote machines.
 */
class mock_connection_c
: public connection_i
{
public:
	mock_connection_c( std::queue< std::string > &read_queue
			, std::queue< std::string > &write_queue
			, short port = 0 );

	virtual short port() const { return m_port; }

	virtual void read_line( std::string & );
	virtual void write_line( const std::string & );
	virtual bool line_ready() const;

private:
	std::queue< std::string > &m_read_queue;
	std::queue< std::string > &m_write_queue;
	short m_port;
};

/**
 * Mock connections for simulating a client & server on remote machines
 */
class mock_client_server_connection_c
{
public:
	mock_client_server_connection_c( short port = 0 );

	connection_i & client() { return m_client; }
	connection_i & server() { return m_server; }

private:
	std::queue< std::string > m_client_read_queue;
	std::queue< std::string > m_server_read_queue;
	mock_connection_c m_client;
	mock_connection_c m_server;
};


#endif

