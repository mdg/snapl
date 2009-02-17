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
: m_listener()
, m_open()
, m_ready()
, m_backlog( connection_acceptor_c::DEFAULT_BACKLOG )
{}


connection_acceptor_c::~connection_acceptor_c()
{
	close();
}

bool connection_acceptor_c::listen( short port )
{
	int listener( create_listener_socket( port, m_backlog ) );
	if ( ! listener ) {
		return false;
	}

	m_listener[ listener ] = port;
	std::cerr << "m_listener[ " << listener << " ] = " << port << "\n";
	return true;
}

int connection_acceptor_c::create_listener_socket( int port, int backlog )
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
	int listen_error = ::listen( listener, backlog );
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
	// close the listeners first
	listener_iterator listener( m_listener.begin() );
	for ( ; listener!=m_listener.end(); ++listener ) {
		shutdown( listener->first, SHUT_RDWR );
	}
	m_listener.clear();

	// close the open connections
	connection_iterator conn( m_open.begin() );
	for ( ; conn!=m_open.end(); ++conn ) {
		shutdown( conn->first, SHUT_RDWR );
		delete conn->second;
	}
	m_ready.clear();
	m_open.clear();
}

connection_i * connection_acceptor_c::connection()
{
	// check if there's already a ready connection queued
	connection_i *ready_conn = NULL;
	if ( ! m_ready.empty() ) {
		ready_conn = m_ready.front();
		m_ready.pop_front();
		return ready_conn;
	}

	// build the poll set to check for new connections and input
	int listener_count( m_listener.size() );
	int connection_count( m_open.size() );
	int poll_count( listener_count + connection_count );
	pollfd *polls = new pollfd[ poll_count ];

	int i( 0 );
	// build listener poll structures
	listener_iterator lit( m_listener.begin() );
	for ( ; lit != m_listener.end(); ++lit ) {
		polls[i].fd = lit->first;
		polls[i].events = POLLIN;
		polls[i++].revents = 0;
	}

	// build polls for open connections
	connection_iterator conn( m_open.begin() );
	for ( ; conn!=m_open.end(); ++conn ) {
		polls[i].fd = conn->first;
		polls[i].events = POLLIN;
		polls[i++].revents = 0;
	}

	std::cerr << "poll( " << listener_count << ", " << connection_count
	       << " )...\n";
	int ready_count( poll( polls, poll_count, 1000 ) );
	if ( ready_count == 0 ) {
		return NULL;
	}

	std::cerr << "ready_count == " << ready_count << std::endl;
	if ( ready_count < 0 ) {
		perror( "Poll error" );
	}

	// accept connections on the listeners
	for ( i=0; i<listener_count; ++i ) {
		if ( polls[i].revents & POLLIN ) {
			int listener( polls[i].fd );
			int port( m_listener[ listener ] );
			accept( listener, port );
		} else if ( polls[i].revents != 0 ) {
			std::cerr << "polls[" << i << "].revents = "
				<< polls[i].revents << std::endl;
		}
	}

	// check for input on open connections
	for ( i=listener_count; i<poll_count; ++i ) {
		if ( polls[i].revents & POLLHUP ) {
			// this connection is closed.
			// delete it.
			std::cerr << "deleting a closed connection\n";
			close_socket( polls[i].fd );
		} else if ( polls[i].revents & POLLIN ) {
			std::cerr << "i=" << i << "; ";
			std::cerr << "m_ready.push_back( m_open["
				<< polls[i].fd << "] )\n";
			m_ready.push_back( m_open[ polls[i].fd ] );
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
	m_ready.pop_front();
	return ready_conn;
}

void connection_acceptor_c::accept( int listener, int port )
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
	m_open[ sock ] = new connected_socket_c( sock, port );
}


void connection_acceptor_c::close_socket( int socket )
{
	connection_iterator it( m_open.find( socket ) );
	if ( it == m_open.end() ) {
		return;
	}

	delete it->second;
	m_open.erase( it->first );
}

