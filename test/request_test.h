#ifndef REQUEST_TEST_H
#define REQUEST_TEST_H
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

#include "snapl/request.h"


/**
 * Mock request implementation for testing code that needs an implemented
 * request class.
 */
class mock_request_c
: public request_c
{
public:
	mock_request_c()
	: request_c( "mock" )
	, m_id()
	, m_number( 0 )
	{
		m_arg << m_id << m_number;
	}

	mock_request_c( const std::string &id, int number )
	: request_c( "mock" )
	, m_id( id )
	, m_number( number )
	{
		m_arg << m_id << m_number;
	}

	void set( const std::string &id, int number )
	{
		m_id = id;
		m_number = number;
	}

	const std::string & id() const { return m_id; }
	int number() const { return m_number; }

private:
	std::string m_id;
	int m_number;
};


#endif

