#ifndef PROTOCOL_H
#define PROTOCOL_H
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

#include <map>
#include "request_type.h"

class request_processor_i;
class shession_store_i;


class protocol_c
{
	typedef std::map< request_type_e
		, request_processor_i * > processor_map;
	typedef processor_map::iterator processor_iterator;

public:
	protocol_c( short port );
	virtual ~protocol_c();
	void add( request_processor_i & );

	short port() const { return m_port; }
	request_processor_i * processor( request_type_e );

private:
	short m_port;
	processor_map m_processor;
};


#endif

