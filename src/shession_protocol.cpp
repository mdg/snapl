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

#include "shession_protocol.h"
#include "request_processor.h"
#include "mirror_protocol.h"


shession_protocol_c::shession_protocol_c( shession_store_i &store, shession_generator_i &gen )
: m_store( store )
, m_service()
, m_mirror()
, m_admin()
, m_create( new create_request_processor_c( store, gen ) )
, m_renew( new renew_request_processor_c( store ) )
, m_kill( new kill_request_processor_c( store ) )
, m_close( new close_request_processor_c( store ) )
, m_mirror_processor( new mirror_request_processor_c( store ) )
, m_export( new export_request_processor_c( store ) )
{}

shession_protocol_c::~shession_protocol_c()
{}


protocol_c & shession_protocol_c::create_service_protocol( short port )
{
	m_service.reset( new protocol_c( port ) );
	m_service->add( *m_create );
	m_service->add( *m_renew );
	m_service->add( *m_kill );
	m_service->add( *m_close );
	return *m_service;
}

protocol_c & shession_protocol_c::create_mirror_protocol( short port )
{
	m_mirror.reset( new protocol_c( port ) );
	m_mirror->add( *m_mirror_processor );
	m_mirror->add( *m_export );
	return *m_mirror;
}

