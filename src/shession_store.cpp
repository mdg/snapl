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

#include "shession_store.h"


shession_store_c::shession_store_c( int timeout )
: m_timeout( timeout )
, m_store()
{}


void shession_store_c::create_session( const std::string &session_id )
{
}

bool shession_store_c::renew_session( const std::string &session_id )
{
	return true;
}

void shession_store_c::kill_session( const std::string &session_id )
{
}

void shession_store_c::kill_expired()
{
}

