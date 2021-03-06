#ifndef SNAPL_MESSAGE_ARG_H
#define SNAPL_MESSAGE_ARG_H
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
#include <iostream>
#include <vector>

namespace snapl {

class arg_list_c;


/**
 * Untyped interface for a typed message argument that needs to be
 * converted to a string.
 */
class message_arg_c
{
public:
	message_arg_c()
	: m_arg()
	{}
	message_arg_c( const std::string &arg )
	: m_arg( arg )
	{}
	~message_arg_c()
	{}

	/**
	 * Rename this to str()
	 */
	const std::string & get() const
	{
		return m_arg;
	}

	/**
	 * Set this argument.
	 */
	void set( const std::string &arg )
	{
		m_arg = arg;
	}

	/**
	 * Parse a string out of an ostream.
	 */
	friend std::ostream & operator << ( std::ostream &
			, const message_arg_c & );

	/**
	 * Write the string back to the istream.
	 */
	friend std::istream & operator >> ( std::istream &, message_arg_c & );

private:
	std::string m_arg;
};


class message_arg_list_c
{
public:
	typedef std::vector< message_arg_c >::const_iterator iterator;

public:
	message_arg_list_c();
	~message_arg_list_c();

	void operator = ( const arg_list_c & );

	/**
	 * Return the number of args in this list.
	 */
	int argc() const { return m_arg.size(); }

	/**
	 * Get the ith argument.
	 */
	const std::string & argv( int i ) const;

	/**
	 * Serialize this list of args in a string.
	 */
	std::string arg_string() const;

	/**
	 * Parse a given string into the arg list of separated strings.
	 */
	void parse( const std::string &arg_string );

	iterator begin() const { return m_arg.begin(); }
	iterator end() const { return m_arg.end(); }

private:
	std::vector< message_arg_c > m_arg;
};


} // namespace

#endif

