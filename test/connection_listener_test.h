#ifndef CONNECTION_LISTENER_TEST_H
#define CONNECTION_LISTENER_TEST_H
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

#include "snapl/net/connection_listener.h"


class mock_connection_listener_c
: public connection_listener_i
{
public:
	mock_connection_listener_c( connection_i &conn )
	: m_connection( conn )
	{}
	virtual ~mock_connection_listener_c() {}

	virtual bool listen( short port ) { return true; }

	virtual connection_i * connection()
	{
		return m_connection.line_ready() ? &m_connection : NULL;
	}

	virtual void replace( connection_i * ) {}

private:
	connection_i &m_connection;
};


#endif

