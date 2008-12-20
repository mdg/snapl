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
#include "action.h"
#include "protocol.h"
#include "request.h"
#include "response.h"
#include <iostream>


dispatcher_c::dispatcher_c( server_queue_i &queue )
: m_queue( queue )
, m_protocol()
{}

dispatcher_c::~dispatcher_c() {}


void dispatcher_c::add_protocol( short port, protocol_c &protocol )
{
	m_protocol[ port ] = &protocol;
}


bool dispatcher_c::main_loop()
{
	bool success( false );
	for (;;) {
		std::auto_ptr< request_message_i > msg( m_queue.pop() );
		if ( ! msg.get() ) {
			// sleep or yield or something, then reiterate
			continue;
		}

		dispatch( *req, *resp );
	}

	return success;
}

void request_router_c::dispatch( const request_c &req, response_c &resp )
{
	bool success( false );
	std::auto_ptr< response_c > resp( new response_c() );

	protocol_c *protocol = find_protocol( port );
	if ( ! protocol ) {
		// can't do anything.
		// write to the response and return
		std::ostringstream err;
		err << "No protocol for port " << port";
		resp.err( err.str() );
		return;
	}

	action_i *action = protocol->action( req.type() );
	if ( ! action ) {
		std::cerr << "no request processor for " << req.type()
			<< std::endl;
		resp.err( "unknown request type: '"+ req.type()
		       +"'" );
		return;
	}

	action->execute( req, resp );

	if ( ! protocol->silent() ) {
		m_queue.push( resp.release() );
	}
}

protocol_i * request_router_c::find_protocol( int port )
{
	protocol_iterator it( m_protocol.find( port ) );
	if ( it == m_protocol.end() ) {
		std::cerr << "port " << port << " has no protocol\n";
		// maybe should close this connection also?
		return NULL;
	}
	return it->second;
}

