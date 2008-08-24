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


#include "connection_acceptor.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include "connected_socket.h"


connection_acceptor_c::connection_acceptor_c()
: m_port( 0 )
, m_listener( 0 )
{
}

connection_acceptor_c::~connection_acceptor_c()
{
	close();
}

bool connection_acceptor_c::open( int port, int backlog )
{
	// create the socket
	m_listener = socket( PF_INET, SOCK_STREAM, 0 );
	if ( m_listener < 0 ) {
		// error.  do something.
		perror( "Unable to create socket." );
		return false;
	} else if ( m_listener == 0 ) {
		perror( "wtf happened?" );
		return false;
	}
	// printf( "Socket connected at: %u\n", m_listener );

	// bind the socket
	struct sockaddr_in addr;
	memset( &addr, 0, sizeof(addr) );
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );
	addr.sin_addr.s_addr = INADDR_ANY;
	int bind_error = bind( m_listener, (struct sockaddr *) &addr
			, sizeof(addr) );
	if ( bind_error ) {
		// error.  do something.
		perror( "Unable to bind socket." );
		return false;
	}
	// std::cout << "Socket is bound.\n";

	// make the socket listen
	int listen_error = listen( m_listener, backlog );
	if ( listen_error < 0 ) {
		// error.  do something.
		perror( "Socket won't listen." );
		return false;
	}
	// printf( "Listening on port %u...\n", port );

	struct sockaddr_in name;
	socklen_t name_len = sizeof( name );
	int sockname_err = getsockname( m_listener, (struct sockaddr *) &name
			, &name_len );
	if ( sockname_err ) {
		perror( "getsockname error" );
		return false;
	}

	fcntl( m_listener, F_SETFL, O_NONBLOCK );
	return true;
}

void connection_acceptor_c::close()
{
	m_port = 0;
	if ( m_listener ) {
		std::cerr << "acceptor_c::close()\n";
		shutdown( m_listener, SHUT_RDWR );
		m_listener = 0;
	}
}

connection_i * connection_acceptor_c::connection()
{
	// sockaddr addr;
	// socklen_t addr_len( sizeof(addr) );
	// int sock = accept( m_listener, &addr, &addr_len );
	int sock = accept( m_listener, NULL, 0 );
	if ( sock < 0 ) {
		if ( errno == EWOULDBLOCK ) {
			// non-block, when no resource is available
			// std::cerr << "EWOULDBLOCK\n";
			return 0;
		} else if ( errno == EAGAIN ) {
			// non-block, when no resource is available
			std::cerr << "EAGAIN\n";
			return 0;
		} else if ( errno == EPERM ) {
			std::cerr << "EPERM\n";
			return 0;
		} else if ( sock < 0 ) {
			std::cerr << "sock error = " << sock << std::endl;
			perror( "No connection." );
			return 0;
		}
		std::cerr << "accept() failed\n";
		return 0;
	}
	std::cerr << "Connected at " << sock << std::endl;

	// set the socket as non-blocking before returning it
	fcntl( sock, F_SETFL, O_NONBLOCK );
	return new connected_socket_c( sock );
}

