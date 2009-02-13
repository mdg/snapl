#ifndef MESSAGE_ARG_H
#define MESSAGE_ARG_H
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
#include <list>


/**
 * Untyped interface for a typed message argument that needs to be
 * converted to a string.
 */
class message_arg_c
{
public:
	~message_arg_c();

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
	std::ostream & operator << ( std::ostream & );

	/**
	 * Write the string back to the istream.
	 */
	std::istream & operator >> ( std::istream & );

private:
	std::string m_arg;
};


class message_arg_list_c
{
public:

private:
	std::list< message_arg_c > m_arg;
};


#endif

