#ifndef COMMAND_TEST_H
#define COMMAND_TEST_H
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
#include "request_test.h"
#include "response_test.h"


/**
 * A mock command implementation for verifying that the derived
 * class works.
 */
class mock_command_c
: public command_c< mock_request_c, mock_response_c >
{
public:
	mock_command_c( const std::string &id, int number )
	{
		m_request.set( id, number );
	}
};


#endif

