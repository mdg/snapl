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

#include "client_message.h"
#include "response.h"


client_message_c::client_message_c( const request_c &req )
: m_request()
, m_response()
, m_connection( NULL )
{}

client_message_c::~client_message_c()
{}

void client_message_c::set_response( response_c *resp )
{
	m_response.reset( resp );
}

