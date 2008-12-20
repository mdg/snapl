#ifndef MESSAGE_H
#define MESSAGE_H
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

#include <string>
#include <memory>

class connection_i;
class request_c;
class response_c;


class client_message_c
{
public:
	client_message_c( const request_c & );
	~client_message_c();

	void set_response( response_c * );

	bool has_response() const;
	const response_c & response() const;

	connection_i * release_connection();

private:
	std::string m_request;
	std::auto_ptr< response_c > m_response;
	std::auto_ptr< connection_i > m_connection;
};


#endif

