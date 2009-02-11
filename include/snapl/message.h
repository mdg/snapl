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


#include "message_arg.h"
#include <vector>
#include <string>
#include <list>
#include <sstream>


/**
 * An object for turning a typed request or response object into
 * serialized strings so it can be passed to an open network connection.
 */
class message_c
{
public:
	message_c();
	message_c( const std::string &args );
	~message_c();
	void add_content( const std::string & );

	void copy( const message_c & );

	/**
	 * Get the number of args for this message.
	 */
	int argc() const { return m_arg.size(); }
	std::string argv( int i ) const;
	/**
	 * Get an argument as a string.
	 */
	void argv( int i, std::string &argv ) const
	{
		m_arg.argv( i, argv );
	}
	/**
	 * Set an argument as a string.
	 */
	void set_argv( int i, const std::string &argv );

	const std::list< std::string > & content() const;
	std::list< std::string >::const_iterator begin_content() const;
	std::list< std::string >::const_iterator end_content() const;

	std::string arg_string() const { return m_arg.str(); }

	void parse_args( const std::string & );

protected:
	message_arg_list_c m_arg;
};


#endif

