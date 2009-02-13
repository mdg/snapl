#ifndef ARG_LIST_H
#define ARG_LIST_H
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


#include <vector>
#include <string>
#include <list>
#include <sstream>

class message_arg_c;


/**
 * Untyped interface for a typed message argument that needs to be
 * converted to a string.
 */
class arg_i
{
public:
	virtual ~arg_i() {}
	/**
	 * Rename this to str()
	 */
	virtual void get_string( std::string & ) const = 0;
	/**
	 * Rename this to parse_value()
	 */
	virtual bool set_string( const std::string & ) = 0;

	virtual std::istream & operator >> ( std::istream & ) = 0;
	virtual std::ostream & operator << ( std::ostream & ) const = 0;
};


/**
 * Template-typed implementation of the message arg that will hold
 * information about arguments to messages
 */
template < typename T >
class arg_c
: public arg_i
{
public:
	arg_c( T &val )
	: m_value( val )
	{}
	virtual ~arg_c() {}

	/**
	 * Get the value of this argument.
	 */
	const T & value() const { return m_value; }

	virtual std::istream & operator >> ( std::istream &in )
	{
		in >> m_value;
		return in;
	}

	virtual std::ostream & operator << ( std::ostream &out ) const
	{
		out << m_value;
		return out;
	}

	/**
	 * Get the string version of this argument.
	 */
	virtual void get_string( std::string &str ) const
	{
		str.clear();
		std::ostringstream out;
		out << m_value;
		str = out.str();
	}

	/**
	 * Set the value of this argument as a string.
	 */
	virtual bool set_string( const std::string &str )
	{
		std::istringstream in( str );
		in >> m_value;
		return in;
	}

private:
	T &m_value;
};


/**
 * A list of arguments in a message.
 */
class arg_list_c
{
public:
	arg_list_c();
	~arg_list_c();

	/**
	 * Add an argument to the argument list.
	 * This is the way that requests & responses will add typed
	 * values to the message.
	 */
	template < typename T >
	arg_list_c & operator << ( T &value )
	{
		arg_c< T > *arg = new arg_c< T >( value );
		m_arg.push_back( arg );
		return *this;
	}

	/**
	 * Copy the values from the src arg list to this arg list.
	 */
	void operator = ( const std::list< message_arg_c > & );

	/**
	 * Get the number of arguments in this list.
	 */
	int size() const { return m_arg.size(); }

	/**
	 * Return a string version of a given argument.
	 */
	std::string argv( int i ) const;

	/**
	 * Get a string version of a given argument.
	 */
	void argv( int i, std::string &argv ) const;

	/**
	 * Convert this arg list into a string.
	 */
	std::string str() const;

	/**
	 * Parse a line of text into the values for this arg list.
	 */
	void parse( const std::string &line );

private:
	// declared private and not implemented to avoid usage.
	arg_list_c( const arg_list_c & );

	std::list< arg_i * > m_arg;
};


#endif

