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

#include "server_queue.h"
#include "lock.h"


server_queue_c::server_queue_c()
: m_requests()
, m_mutex()
{}

server_queue_c::server_queue_c( mutex_i *mutex )
: m_requests()
, m_mutex( mutex )
{}

server_queue_c::~server_queue_c() {}


void server_queue_c::push( server_message_c *msg )
{
	lock_c lock( m_mutex.get() );
	m_requests.push( msg );
	// lock is freed by destructor
}

server_message_c * server_queue_c::pop()
{
	server_message_c *msg = 0;
	lock_c lock( m_mutex.get() );
	if ( ! m_requests.empty() ) {
		msg = m_requests.front();
		m_requests.pop();
	}
	lock.unlock();
	return msg;
}

