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

#include "snapl/net/outbox.h"
#include "snapl/net/connection.h"
#include "server_message.h"


#include <iostream>

using namespace snapl;


outbox_c::outbox_c( queue_front_i< server_message_c > &response_queue
		, queue_back_i< server_message_c > &complete_queue )
: m_response( response_queue )
, m_complete( complete_queue )
{}

outbox_c::~outbox_c()
{}


void outbox_c::iterate()
{
	write_messages();
}

void outbox_c::write_messages()
{
	while ( ! m_response.empty() ) {
		std::auto_ptr< server_message_c > msg( m_response.pop() );

		connection_i &conn( msg->connection() );
		conn.write_line( msg->response().args().arg_string() );

		m_complete.push( msg.release() );
	}
}

