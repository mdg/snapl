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

#include "message_queue.h"


void do_with_queue( message_queue_i &queue )
{
	std::auto_ptr< message_i > msg_in( queue.pop_incoming() );
	message_i msg_out;

	execute( *msg_in, msg_out );
	queue.queue( msg_out );
}

void loop_iteration( message_queue_i &queue )
{
	std::auto_ptr< request_message_i > req_msg( queue.pop_request() );
	response_c response;

	execute( req_msg->request(), response );

	response_message_c resp_msg( req_msg, response );
	queue.push( resp_msg );
}


