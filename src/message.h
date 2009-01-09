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


class message_arg_i
{
public:
	virtual ~message_arg_i() {}
	virtual void get_string( std::string & ) const = 0;
	virtual void set_string( const std::string & ) = 0;
};


template < typename T >
class message_arg_c
: public message_arg_i
{
public:
	message_arg_c( T &val )
	: m_value( val )
	{}
	virtual ~message_arg_c() {}

	virtual void get_string( std::string &str ) const
	{
		str.clear();
		std::ostringstream out;
		out << m_value;
		str = out.str();
	}

	virtual void set_string( const std::string &str )
	{
		std::istringstream in( str );
		in >> m_value;
	}

	const T & value() const { return m_value; }

private:
	T &m_value;
};


class message_arg_list_c
{
public:
	~message_arg_list_c();

	/**
	 * Add an argument to the argument list.
	 */
	template < typename T >
	message_arg_list_c & operator << ( T &arg )
	{
		m_arg.push_back( new message_arg_c< T >( arg ) );
	}

	int argc() const { return m_arg.size(); }

	void get_argv( int i, std::string &argv ) const
	{
		m_arg[i]->get_string( argv );
	}

private:
	std::vector< message_arg_i * > m_arg;
};


class message_c
{
public:
	message_c();
	message_c( const std::string &args );
	~message_c();
	void add_arg( const std::string & );
	void add_content( const std::string & );

	int argc() const { return m_arg.size(); }
	const std::string & argv( int i ) const { return m_arg[ i ]; }

	const std::list< std::string > & content() const;
	std::list< std::string >::const_iterator begin_content() const;
	std::list< std::string >::const_iterator end_content() const;

	void parse_args( const std::string & );
	void write_args( std::string & ) const;

private:
	std::vector< std::string > m_arg;
	message_arg_list_c m_arg_list;
};



/**
 * Object that exports general values from a message class into a typed
 * object.
 */
class message_export_c
{
public:
	message_export_c( const message_c &msg )
	: m_message( msg )
	, m_arg( 0 )
	, m_error( false )
	{}

	template < typename T >
	void copy_message( const T &dest )
	{
		dest.copy( *this );
	}

	template < typename T >
	message_export_c & operator + ( T &value )
	{
		// check that too many values haven't already been read
		if ( m_arg >= m_message.argc() ) {
			m_error = true;
			return *this;
		}

		copy_value( value, m_message.argv( m_arg++ ) );
		return *this;
	}

	/**
	 * Copy a string value to a typed value.
	 */
	template < typename T >
	void copy_value( T &dest, const std::string &src )
	{
		std::istringstream in( src );
		in >> dest;
		if ( ! in ) {
			m_error = true;
		}
	}

private:
	const message_c &m_message;
	int m_arg;
	bool m_error;
};


/**
 * Object that imports values from a typed object into a string-based message.
 */
class message_import_c
{
public:
	message_import_c( message_c &msg )
	: m_message( msg )
	, m_arg( 0 )
	, m_error( false )
	{}

	template < typename T >
	void copy_message( const T &typed_obj )
	{
		typed_obj.copy( *this );
	}

	template < typename T >
	message_import_c & operator + ( const T &value )
	{
		std::string arg;
		copy_value( arg, value );
		m_message.add_arg( arg );
		return *this;
	}

	/**
	 * Copy a value into a string type.
	 */
	template < typename T >
	void copy_value( std::string &arg, const T &value )
	{
		std::ostringstream out;
		out << value;
		arg = out.str();
	}

private:
	message_c &m_message;
	int m_arg;
	bool m_error;
};


class message_reader_i
{
};

class message_writer_i
{
};


#endif

