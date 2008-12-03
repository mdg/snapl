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

#include "request_queue.h"
#include "lock.h"


request_queue_c::request_queue_c()
: m_requests()
, m_mutex( NULL )
{}

request_queue_c::request_queue_c( mutex_i &mutex )
: m_requests()
, m_mutex( &mutex )
{}

request_queue_c::~request_queue_c() {}


void request_queue_c::push( request_c *req )
{
	lock_c lock( m_mutex );
	m_requests.push( req );
	// lock is freed by destructor
}

request_c * request_queue_c::pop()
{
	request_c *req = 0;
	lock_c lock( m_mutex );
	if ( ! m_requests.empty() ) {
		req = m_requests.front();
		m_requests.pop();
	}
	lock.unlock();
	return req;
}

