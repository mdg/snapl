#ifndef SNAPL_PROTOCOL_H
#define SNAPL_PROTOCOL_H
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
#include <string>

namespace snapl {

class request_c;
class service_i;


class protocol_c
{
	typedef std::map< std::string, service_i * > service_map;
	typedef service_map::iterator service_iterator;

public:
	protocol_c( short port );
	virtual ~protocol_c();

	/**
	 * Add a service that knows its own name.
	 */
	void add( service_i &service );

	/**
	 * Add a service with an explicitly assigned name.
	 */
	void add( const std::string &name, service_i &service )
	{
		m_service[ name ] = &service;
	}

	service_i * service( const std::string &service_name );

	const std::string & name() const { return m_name; }
	short port() const { return m_port; }
	bool silent() const { return m_silent; }

private:
	std::string m_name;
	service_map m_service;
	short m_port;
	bool m_silent;
};


} // namespace

#endif

