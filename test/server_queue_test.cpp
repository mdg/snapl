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

#include "server_queue_test.h"
#include "server_message.h"


mock_server_queue_c::mock_server_queue_c()
: m_queue()
, m_connection( NULL )
{}

mock_server_queue_c::~mock_server_queue_c()
{
	while ( ! m_queue.empty() ) {
		server_message_c *msg = m_queue.front();
		delete msg;
		m_queue.pop();
	}
}

void mock_server_queue_c::queue_mock_message( const std::string &req )
{
	m_queue.push( new server_message_c( req, *m_connection ) );
}

server_message_c * mock_server_queue_c::pop()
{
	server_message_c *msg = m_queue.front();
	m_queue.pop();
	return msg;
}

void mock_server_queue_c::push( server_message_c * )
{
}

