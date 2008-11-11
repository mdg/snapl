#ifndef SHESSION_PROTOCOL_H
#define SHESSION_PROTOCOL_H
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

#include "protocol.h"
#include <memory>

class shession_generator_i;


class shession_protocol_c
{
public:
	shession_protocol_c( shession_store_i &, shession_generator_i & );
	~shession_protocol_c();

	protocol_c & create_service_protocol( short service_port );
	protocol_c & create_mirror_protocol( short mirror_port );
	protocol_c & create_admin_protocol( short admin_port );

private:
	shession_store_i &m_store;

	// protocols
	std::auto_ptr< protocol_c > m_service;
	std::auto_ptr< protocol_c > m_mirror;
	std::auto_ptr< protocol_c > m_admin;

	std::auto_ptr< request_processor_i > m_create;
	std::auto_ptr< request_processor_i > m_renew;
	std::auto_ptr< request_processor_i > m_kill;
	std::auto_ptr< request_processor_i > m_close;
};


#endif

