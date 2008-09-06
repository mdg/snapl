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
: m_service_port( 0 )
, m_service_listener( 0 )
, m_admin_port( 0 )
, m_admin_listener( 0 )
{
}

connection_acceptor_c::~connection_acceptor_c()
{
	close();
}

bool connection_acceptor_c::open( int service_port, int admin_port
		, int backlog )
{
	m_service_port = service_port;
	m_admin_port = admin_port;

	m_service_listener = open_listener( m_service_port, backlog );
	m_admin_listener = open_listener( m_admin_port, backlog );
	return m_service_listener && m_admin_listener;
}

int connection_acceptor_c::open_listener( int port, int backlog )
{
	int listener( 0 );
	// create the socket
	listener = socket( PF_INET, SOCK_STREAM, 0 );
	if ( listener < 0 ) {
		// error.  do something.
		perror( "Unable to create socket." );
		return false;
	} else if ( listener == 0 ) {
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
	int bind_error = bind( listener, (struct sockaddr *) &addr
			, sizeof(addr) );
	if ( bind_error ) {
		// error.  do something.
		perror( "Unable to bind socket." );
		return false;
	}
	// std::cout << "Socket is bound.\n";

	// make the socket listen
	int listen_error = listen( listener, backlog );
	if ( listen_error < 0 ) {
		// error.  do something.
		perror( "Socket won't listen." );
		return false;
	}
	// printf( "Listening on port %u...\n", port );

	struct sockaddr_in name;
	socklen_t name_len = sizeof( name );
	int sockname_err = getsockname( listener, (struct sockaddr *) &name
			, &name_len );
	if ( sockname_err ) {
		perror( "getsockname error" );
		return false;
	}

	fcntl( listener, F_SETFL, O_NONBLOCK );
	return listener;
}

void connection_acceptor_c::close()
{
	m_service_port = 0;
	m_admin_port = 0;
	if ( m_service_listener ) {
		std::cerr << "acceptor_c::close()\n";
		shutdown( m_service_listener, SHUT_RDWR );
		m_service_listener = 0;
	}
	if ( m_admin_listener ) {
		std::cerr << "acceptor_c::close( admin )\n";
		shutdown( m_admin_listener, SHUT_RDWR );
		m_admin_listener = 0;
	}
}

connection_i * connection_acceptor_c::connection()
{
	// check if there's already a ready connection queued
	connection_i *ready_conn = NULL;
	if ( ! m_ready.empty() ) {
		ready_conn = m_ready.front();
		m_ready.pop();
		return ready_conn;
	}

	// build the poll set to check for new connections and input
	int poll_count( m_open.size() + 2 );
	pollfd *polls = new pollfd[ poll_count ];

	int i( 0 );
	std::map< int, connection_i * >::const_iterator it;

	// build service listener poll
	polls[i].fd = m_service_listener;
	polls[i].events = POLLIN;
	polls[i++].revents = 0;
	// build admin listener poll
	polls[i].fd = m_admin_listener;
	polls[i].events = POLLIN;
	polls[i++].revents = 0;

	// build polls for open connections
	for ( it=m_open.begin(); it!=m_open.end(); ++it ) {
		polls[i].fd = it->first;
		polls[i].events = POLLIN;
		polls[i++].revents = 0;
	}

	std::cerr << "poll( " << poll_count << " )...\n";
	int ready_count( poll( polls, poll_count, 1000 ) );
	if ( ready_count == 0 ) {
		return NULL;
	}

	std::cerr << "ready_count == " << ready_count << std::endl;
	if ( ready_count < 0 ) {
		perror( "Poll error" );
	}

	// accept connections on the listeners if there's anything
	if ( polls[0].revents & POLLIN ) {
		accept( m_service_listener );
	}
	if ( polls[1].revents & POLLIN ) {
		accept( m_admin_listener );
	}
	// check for input on open connections
	for ( i=2; i<poll_count; ++i ) {
		if ( polls[i].revents & POLLHUP ) {
			// this connection is closed.
			// delete it.
			delete m_open[ polls[i].fd ];
			m_open.erase( polls[i].fd );
		} else if ( polls[i].revents & POLLIN ) {
			m_ready.push( m_open[ polls[i].fd ] );
		} else {
			std::cerr << "polls[" << i << "].revents = "
				<< polls[i].revents << std::endl;
		}
	}

	// return the ready connection if there is one
	if ( m_ready.empty() ) {
		return NULL;
	}
	ready_conn = m_ready.front();
	m_ready.pop();
	return ready_conn;
}

void connection_acceptor_c::accept( int listener )
{
	int sock( ::accept( listener, NULL, 0 ) );
	if ( sock < 0 ) {
		if ( errno == EWOULDBLOCK ) {
			// non-block, when no resource is available
			// std::cerr << "EWOULDBLOCK\n";
			return;
		} else if ( errno == EAGAIN ) {
			// non-block, when no resource is available
			std::cerr << "EAGAIN\n";
			return;
		} else if ( errno == EPERM ) {
			std::cerr << "EPERM\n";
			return;
		} else if ( sock < 0 ) {
			std::cerr << "sock error = " << sock << std::endl;
			perror( "No connection." );
			return;
		}
		std::cerr << "accept() failed\n";
		return;
	}
	std::cerr << "Connected at " << sock << std::endl;

	// set the socket as non-blocking before returning it
	fcntl( sock, F_SETFL, O_NONBLOCK );
	m_open[ sock ] = new connected_socket_c( sock );
}

