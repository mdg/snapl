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

#include "snapl/net/client_connection.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include "connected_socket.h"


client_connection_c::client_connection_c()
: m_connection()
{}

client_connection_c::~client_connection_c()
{
	close();
}


bool client_connection_c::connect( const std::string &url, short port )
{
	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );
	inet_aton( url.c_str(), &addr.sin_addr );
	if ( addr.sin_addr.s_addr == 0 ) {
		std::cerr << "Error identifying address for " << url
			<< std::endl;
		return false;
	}

	int connection( socket( PF_INET, SOCK_STREAM, 0 ) );
	if ( connection < 0 ) {
		std::cerr << "Error creating socket.\n";
		return false;
	}

	if ( ::connect( connection, (const sockaddr *) &addr, sizeof(addr) ) ) {
		std::cerr << "Failure connecting to " << url << std::endl;
		return false;
	}

	m_connection.reset( new connected_socket_c( connection, port ) );
	std::cerr << "Connected to " << url << "!\n";
	return true;
}

bool client_connection_c::open() const
{
	return m_connection.get() && m_connection->open();
}

void client_connection_c::close()
{
	m_connection.reset();
}


short client_connection_c::port() const
{
	return m_connection->port();
}

void client_connection_c::read_line( std::string &line )
{
	m_connection->read_line( line );
}

void client_connection_c::write_line( const std::string &line )
{
	m_connection->write_line( line );
}

bool client_connection_c::line_ready() const
{
	return m_connection->line_ready();
}

