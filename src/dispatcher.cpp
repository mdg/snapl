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


#include "dispatcher.h"
#include "protocol.h"
#include "request.h"
#include "response.h"
#include "service.h"
#include "server_message.h"
#include "server_queue.h"
#include <iostream>


dispatcher_c::dispatcher_c( server_queue_i &queue )
: m_queue( queue )
, m_protocol()
{}

dispatcher_c::~dispatcher_c() {}


void dispatcher_c::add( protocol_c &protocol )
{
	m_protocol[ protocol.port() ] = &protocol;
}


bool dispatcher_c::main_loop()
{
	bool success( false );
	for (;;) {
		iterate();
	}

	return success;
}

void dispatcher_c::iterate()
{
	server_message_c *msg = m_queue.pop();
	if ( ! msg ) {
		// sleep or yield or something, then reiterate
		return;
	}

	dispatch( msg );
}

void dispatcher_c::dispatch( server_message_c *msg_ptr )
{
	std::auto_ptr< server_message_c > msg( msg_ptr );
	bool success( false );

	protocol_c *protocol = find_protocol( msg->port() );
	if ( ! protocol ) {
		// can't do anything.
		// write to the response and return
		std::ostringstream err;
		err << "No protocol for port " << msg->port();
		msg->response().err( err.str() );
		return;
	}

	service_i *service = protocol->service( msg->request_type() );
	if ( ! service ) {
		std::cerr << "no service for " << msg->request_type()
			<< std::endl;
		msg->response().err( "unknown request type: '"
				+ msg->request_type() +"'" );
		return;
	}

	service->execute( msg->request(), msg->response() );

	if ( ! protocol->silent() ) {
		m_queue.push( msg.release() );
	}
}

protocol_c * dispatcher_c::find_protocol( int port )
{
	protocol_iterator it( m_protocol.find( port ) );
	if ( it == m_protocol.end() ) {
		std::cerr << "port " << port << " has no protocol\n";
		// maybe should close this connection also?
		return NULL;
	}
	return it->second;
}

