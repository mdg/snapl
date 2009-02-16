#ifndef SNAPL_ARG_LIST_H
#define SNAPL_ARG_LIST_H
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
class message_arg_list_c;


/**
 * Untyped interface for a typed message argument that needs to be
 * converted to a string.
 */
class arg_i
{
public:
	virtual ~arg_i() {}

	/**
	 * Write the value into a string.
	 */
	virtual const std::string & operator >> ( std::string & ) const = 0;

	/**
	 * Parse a string into the value.
	 */
	virtual bool operator << ( const std::string & ) = 0;
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

	virtual const std::string & operator >> ( std::string &str ) const
	{
		str.clear();
		std::ostringstream out;
		out << m_value;
		str = out.str();
		return str;
	}

	virtual bool operator << ( const std::string &str )
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
	bool operator = ( const message_arg_list_c & );

	/**
	 * Get the number of arguments in this list.
	 */
	int size() const { return m_arg.size(); }

	/**
	 * Iterator class for looking into the arg_list
	 */
	class iterator
	{
	public:
		iterator( std::list< arg_i * >::const_iterator i )
		: m_it( i )
		{}
		const arg_i & operator * () const { return **m_it; }
		const arg_i * operator -> () const { return *m_it; }
		iterator & operator ++ () { ++m_it; return *this; }
		iterator operator ++ (int) { return iterator( m_it++ ); }
		/** Check if this iterator is equal to another */
		bool operator == ( const iterator &o ) const
		{
			return m_it == o.m_it;
		}
		/** Check if this iterator is _not_ equal to another */
		bool operator != ( const iterator &o ) const
		{
			return m_it != o.m_it;
		}
	private:
		std::list< arg_i * >::const_iterator m_it;
	};

	iterator begin() const { return iterator( m_arg.begin() ); }
	iterator end() const { return iterator( m_arg.end() ); }

private:
	// declared private and not implemented to avoid usage.
	arg_list_c( const arg_list_c & );

	std::list< arg_i * > m_arg;
};


#endif

