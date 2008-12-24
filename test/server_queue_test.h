#ifndef SERVER_QUEUE_TEST_H
#define SERVER_QUEUE_TEST_H
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

#include "server_queue.h"
#include <string>
#include <queue>

class connection_i;


class mock_server_queue_c
: public server_queue_i
{
public:
	mock_server_queue_c();
	~mock_server_queue_c();

	void queue_mock_message( const std::string &msg );

	server_message_c * pop();

	void push( server_message_c * );

private:
	std::queue< server_message_c * > m_queue;
	connection_i *m_connection;
};

#endif

