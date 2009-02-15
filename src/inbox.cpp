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
#include "snapl/net/connection_listener.h"
#include "server_message.h"
#include "message_reader.h"

#include <iostream>


inbox_c::inbox_c( connection_listener_i &listener
		, queue_back_i< server_message_c > &request_queue
		, queue_front_i< server_message_c > &complete_queue )
: m_listener( listener )
, m_request( request_queue )
, m_complete( complete_queue )
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
		replace_connections();
		read_partial_messages();
		read_new_messages();
	}
}

void inbox_c::replace_connections()
{
	while ( ! m_complete.empty() ) {
		std::auto_ptr< server_message_c > msg( m_complete.pop() );
		connection_i *conn = msg->release_connection();
		m_listener.replace( conn );
	}
}

void inbox_c::read_partial_messages()
{
}

void inbox_c::read_new_messages()
{
	connection_i *conn = m_listener.connection();
	if ( ! conn ) {
		// sleep or yield or something, then reiterate
		return;
	}

	std::auto_ptr< message_reader_c > reader(
			new message_reader_c( conn ) );
	if ( reader->read() ) {
		m_request.push( reader->message() );
	} else {
		m_partial.push( reader.release() );
		std::cerr << "incomplete message\n";
	}
}

