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

#include "shession_client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include "connected_socket.h"


shession_client_c::shession_client_c()
: m_connection()
{}

shession_client_c::~shession_client_c()
{
	close();
}


bool shession_client_c::open( const std::string &url, short port )
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

	if ( connect( connection, (const sockaddr *) &addr, sizeof(addr) ) ) {
		std::cerr << "Failure connecting to " << url << std::endl;
		return false;
	}

	m_connection.reset( new connected_socket_c( connection ) );
	std::cerr << "Connected to " << url << "!\n";
	return true;
}

void shession_client_c::close()
{
	m_connection.reset();
}


void shession_client_c::create_session( const std::string &session_id )
{
	write_request( "create", session_id );
}

bool shession_client_c::live_session( const std::string &session_id )
{
	write_request( "status", session_id );

	std::string live;
	m_connection->read_line( live );
	return live == "live";
}

void shession_client_c::kill_session( const std::string &session_id )
{
	write_request( "kill", session_id );
}


void shession_client_c::write_request( const std::string &request_type
		, const std::string &session_id )
{
	std::string request( request_type +" "+ session_id );
	m_connection->write_line( request );
}

