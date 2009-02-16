#ifndef SNAPL_REQUEST_H
#define SNAPL_REQUEST_H
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

#include "arg.h"

class message_c;


/**
 * An object to describe a request to the server to manage
 * the sessions.
 */
class request_c
{
public:
	/**
	 * Construct a request object with a given request type
	 * and a string parameter.
	 */
	request_c( const std::string &req_type = std::string() );

	/**
	 * Copy a message into this request.
	 */
	void copy_from( const message_c & );

	/**
	 * Get the type of this request
	 */
	const std::string & type() const { return m_type; }

	/**
	 * The arguments to this request.
	 */
	const arg_list_c & args() const { return m_args; }

	/**
	 * Number of arguments to this request.
	 */
	int argc() const { return m_args.size(); }
	/**
	 * Get a specific argument to this request.
	 */
	std::string argv( int i ) const { return m_args.argv( i ); }

	/**
	 * Get the name of the protocol where this request arrived.
	 */
	const std::string & protocol() const { return m_protocol; }

	/**
	 * Get the port that this request came in on.
	 */
	int port() const { return m_port; }

protected:
	arg_list_c m_args;
private:
	std::string m_type;
	std::string m_protocol;
	int m_port;
};


#endif

