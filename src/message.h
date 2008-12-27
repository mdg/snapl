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


class message_c
{
public:
	message_c();
	void add_arg( const std::string & );
	void add_content( const std::string & );

	int argc() const;
	const std::string & argv( int i ) const;

	const std::list< std::string > & content() const;
	std::list< std::string >::const_iterator begin_content() const;
	std::list< std::string >::const_iterator end_content() const;

private:
	std::vector< std::string > m_arg;
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
	message_export_c & operator + ( T &value )
	{
		// check that too many values haven't already been read
		if ( m_arg >= m_message.argc() ) {
			m_error = true;
			return *this;
		}

		copy( value, m_message.argv[ m_arg++ ] );
		return *this;
	}

	/**
	 * Copy a string value to a typed value.
	 */
	template < typename T >
	void copy( T &dest, const std::string &src )
	{
		std::istringstream in( src );
		in >> dest;
		if ( in.error() ) {
			m_error = true;
		}
	}

private:
	message_c &m_msg;
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
	copy_ostream & operator + ( const T &value )
	{
		std::string arg;
		copy( arg, value );
		out >> value;
		return *this;
	}

	/**
	 * Copy a value into a string type.
	 */
	template < typename T >
	void copy( std::string &arg, const T &value )
	{
		std::ostringstream out;
		out << value;
		arg = out.str();
	}

private:
	std::ostream &m_out;
	int m_arg;
	bool m_error;
};


#endif

