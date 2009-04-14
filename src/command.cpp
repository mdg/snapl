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

#include "snapl/command.h"
#include "snapl/message.h"
#include "snapl/response.h"
#include <sstream>

using namespace snapl;


void command_c::get_request( message_c &msg ) const
{
	msg.set_args( m_request );
}

void command_c::set_request( const message_c &msg )
{
	m_request = msg.args();
}

void command_c::get_response( message_c &msg ) const
{
	msg.set_args( m_response );
}

void command_c::set_response( const message_c &msg )
{
	m_response = msg.args();
}

void command_c::ok()
{
	m_response_code = "ok";
	m_response_msg = std::string();
}

void command_c::err( const std::string &msg )
{
	m_response_code = "err";
	m_response_msg = msg;
}

void command_c::err( const std::string &file, int line )
{
	m_response_code = "err";
	std::ostringstream format;
	format << file << ':' << line;
	m_response_msg = format.str();
}

