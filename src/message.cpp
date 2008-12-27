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

#include "message.h"


message_c::message_c()
: m_arg()
{}

message_c::message_c( const std::string &args )
: m_arg()
{
	parse_args( args );
}

message_c::~message_c()
{}


void message_c::add_arg( const std::string &arg )
{
	m_arg.push_back( arg );
}

void message_c::parse_args( const std::string &args )
{
	std::istringstream in( args );
	std::string value;
	while ( in >> value ) {
		add_arg( value );
	}
}

