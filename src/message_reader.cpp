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

#include "message_reader.h"
#include "snapl/net/connection.h"
#include "server_message.h"

using namespace snapl;


message_reader_c::message_reader_c( connection_i *conn )
: m_connection( *conn )
, m_message()
, m_complete( false )
, m_empty( true )
{}

message_reader_c::~message_reader_c()
{}

bool message_reader_c::read()
{
	if ( complete() ) {
		std::cerr << "already complete\n";
		return true;
	}

	std::string line;
	m_connection.read_line( line );
	if ( line.empty() ) {
		std::cerr << "read empty line\n";
		m_empty = true;
		return false;
	}

	m_message.reset( new server_message_c( line, &m_connection ) );
	m_complete = true;
	return true;
}

server_message_c * message_reader_c::message()
{
	if ( ! complete() )
		return NULL;
	return m_message.release();
}

