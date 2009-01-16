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

#include "connection_test.h"
#include <testpp/test.h>


mock_connection_c::mock_connection_c( std::queue< std::string > &read_queue
			, std::queue< std::string > &write_queue
			, short port )
: m_read_queue( read_queue )
, m_write_queue( write_queue )
, m_port( port )
{}

void mock_connection_c::read_line( std::string &line )
{
	if ( m_read_queue.empty() ) {
		return;
	}

	line = m_read_queue.front();
	m_read_queue.pop();
}

void mock_connection_c::write_line( const std::string &line )
{
	m_write_queue.push( line );
}

bool mock_connection_c::line_ready() const
{
	return ! m_read_queue.empty();
}


mock_client_server_connection_c::mock_client_server_connection_c( short port )
: m_client_read_queue()
, m_server_read_queue()
, m_client( m_client_read_queue, m_server_read_queue, port )
, m_server( m_server_read_queue, m_client_read_queue, port )
{}

