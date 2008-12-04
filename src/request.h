#ifndef REQUEST_H
#define REQUEST_H
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
#include <vector>


/**
 * An object to describe a request to the server to manage
 * the sessions.
 */
class request_c
{
public:
	static const std::string CREATE;
	static const std::string RENEW;
	static const std::string KILL;

public:
	/**
	 * Construct a request object with a given request type
	 * and a string parameter.
	 */
	request_c( const std::string &request_line );

	/**
	 * Get the type of this request
	 */
	const std::string & type() const { return m_type; }

	/**
	 * Number of arguments to this request.
	 */
	int argc() const { return m_args.size(); }
	/**
	 * Get a specific argument to this request.
	 */
	const std::string & argv( int i ) const { return m_args[i]; }

private:
	std::string m_type;
	std::vector< std::string > m_args;
};


#endif

