#ifndef SERVICE_TEST_H
#define SERVICE_TEST_H
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

#include "service.h"
#include "request_test.h"
#include "response_test.h"


class mock_service_c
: public service_c< mock_request_c, mock_response_c >
{
public:
	void execute( const mock_request_c &req, mock_response_c &resp )
	{
		std::ostringstream msg;
		msg << req.id() << '_' << req.number();
		resp.ok( msg.str() );
	}
};


#endif

