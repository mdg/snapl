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

#include "snapl/net/inbox.h"
#include "snapl/request.h"
#include "snapl/response.h"
#include "server_message.h"


inbox_c::inbox_c( connection_listener_i &listener
		, queue_back_i< server_message_c > &request_queue
		, queue_front_i< server_message_c > &complete_queue )
: m_listener( listener )
, m_request_queue( request_queue )
, m_complete_queue( complete_queue )
{}

inbox_c::~inbox_c()
{}


void inbox_c::listen( short port )
{
	m_listener.listen( port );
}

void inbox_c::loop()
{
	bool success( false );
	for (;;) {
		replace_complete();
		push_request();
	}

	return success;
}

void inbox_c::replace_complete()
{
	while ( ! m_complete_queue.empty() ) {
		server_message_c *msg = m_complete.pop();
		connection_i *conn = msg.connection();
		m_listener.replace( conn );
	}
}

void inbox_c::push_request()
{
	connection_i *conn = m_listener.connection();
	if ( ! conn ) {
		// sleep or yield or something, then reiterate
		return;
	}

	server_message_c *msg = new server_message_c( conn );
	m_request_queue.push( msg );
}

