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

#include "connected_socket.h"
#include <sys/socket.h>
#include <errno.h>


connected_socket_c::connected_socket_c( int socket, int port )
: m_socket( socket )
, m_port( port )
{}


connected_socket_c::~connected_socket_c()
{
	shutdown( m_socket, SHUT_RDWR );
	m_socket = 0;
	m_port = 0;
}


void connected_socket_c::read_line( std::string &line )
{
	line.erase();

	char buffer[256] = { 0 };
	ssize_t bytes( ::read( m_socket, buffer, sizeof(buffer) ) );
	if ( bytes == -1 ) {
		if ( errno == EWOULDBLOCK ) {
			// do nothing
		} else {
			perror( "request read failure" );
			return;
		}
	} else {
		m_line_parser.add_input( buffer );
	}

	m_line_parser.readline( line );
}

void connected_socket_c::write_line( const std::string &line )
{
	std::string formatted( line + "\n" );
	::write( m_socket, formatted.c_str(), formatted.length() );
}

bool connected_socket_c::line_ready() const
{
	return m_line_parser.line_ready();
}

