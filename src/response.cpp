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

#include "response.h"


response_c::response_c()
: m_code()
, m_msg()
, m_content()
, m_has_content( false )
{
	m_arg << m_code << m_msg;
}

void response_c::ok( const std::string &msg )
{
	m_code = "ok";
	m_msg = msg;
}

void response_c::err( const std::string &msg )
{
	m_code = "err";
	m_msg = msg;
}

void response_c::write_line( const std::string &line )
{
	m_content << '\t' << line << std::endl;
	m_has_content = true;
}

std::string response_c::coded_msg() const
{
	std::string msg( m_code );
	if ( ! m_msg.empty() ) {
		msg += ( " "+ m_msg );
	}
	return msg;
}

