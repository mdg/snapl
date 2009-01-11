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


#include <vector>
#include <string>
#include <list>
#include <sstream>


/**
 * Untyped interface for a typed message argument that needs to be
 * converted to a string.
 */
class message_arg_i
{
public:
	virtual ~message_arg_i() {}
	virtual void get_string( std::string & ) const = 0;
	virtual void set_string( const std::string & ) = 0;
};


/**
 * Template-typed implementation of the message arg that will hold
 * information about arguments to messages
 */
template < typename T >
class message_arg_c
: public message_arg_i
{
public:
	message_arg_c( T &val )
	: m_value( val )
	{}
	virtual ~message_arg_c() {}

	/**
	 * Get the value of this argument.
	 */
	const T & value() const { return m_value; }

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
	virtual void set_string( const std::string &str )
	{
		std::istringstream in( str );
		in >> m_value;
	}

private:
	T &m_value;
};


/**
 * A list of arguments in a message.
 */
class message_arg_list_c
{
public:
	~message_arg_list_c();

	/**
	 * Add an argument to the argument list.
	 * This is the way that requests & responses will add typed
	 * values to the message.
	 */
	template < typename T >
	message_arg_list_c & operator << ( T &arg )
	{
		message_arg_c< T > *msg_arg = new message_arg_c< T >( arg );
		m_arg.push_back( msg_arg );
	}

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

	std::string str() const;

	void parse( const std::string &line );

private:
	std::vector< message_arg_i * > m_arg;
};


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
	void add_arg( const std::string & );
	void add_content( const std::string & );

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

