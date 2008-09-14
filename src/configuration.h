#ifndef CONFIGURATION_H
#define CONFIGURATION_H
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

#include <sstream>
#include <map>
#include <vector>


/**
 * Config option interface.  It hides the type of the various
 * options so the configuration class can parse all options
 * without having to know about their type.
 */
class config_option_i
{
public:
	/**
	 * Empty virtual destructor
	 */
	virtual ~config_option_i() {}

	/**
	 * Virtual parser
	 */
	virtual bool parse( const std::string & ) = 0;

	/**
	 * Get the name of this option.
	 */
	virtual const std::string & name() const = 0;
	/**
	 * Check if this option was set _correctly_ in the configuration file.
	 * It returns false if there was an error.
	 */
	virtual bool set() const = 0;
	/**
	 * Check if this option was set incorrectly in the configuration file.
	 */
	virtual bool error() const = 0;

	// support other features first.
	// virtual std::string doc() const = 0;
};

/**
 * Templated implementation of the config_option_i interface.
 * A config_option_c class should be declared for each option
 * that can be set in the configuration file.
 * The >> ( istream& ) operator must be implemented for typename T.
 */
template < typename T >
class config_option_c
: public config_option_i
{
public:
	/**
	 * Construct the config option.  The name is the key in the
	 * configuration file.
	 */
	config_option_c( const std::string &name )
	: m_name( name )
	, m_value()
	, m_set( false )
	, m_error( false )
	{}

	/**
	 * Construct the config option with a default value.  The name
	 * is the key in the configuration file.
	 */
	config_option_c( const std::string &name, const T &default_value )
	: m_name( name )
	, m_value( default_value )
	, m_set( true )
	, m_error( false )
	{}
	virtual ~config_option_c() {}

	/**
	 * Parse the string value in the typed m_value.
	 */
	virtual bool parse( const std::string &str_value )
	{
		std::istringstream input( str_value );
		input >> m_value;
		m_error = input.fail();
		m_set = ! m_error;
	}

	/**
	 * Get the name of this config option.
	 */
	virtual const std::string & name() const { return m_name; }
	/**
	 * Return the parsed value.
	 */
	const T & value() const { return m_value; }
	/**
	 * Check if the config option was set _correctly_ in the
	 * configuration file.
	 */
	virtual bool set() const { return m_set; }
	/**
	 * Check if the config option was set _incorrectly_ in the
	 * configuration file.
	 */
	virtual bool error() const { return m_error; }

	// virtual std::string doc() const = 0;

private:
	std::string m_name;
	T m_value;
	bool m_set;
	bool m_error;
};

/**
 * Templated implementation of the config_option_i interface.
 * A config_option_list_c allows multiple configurations to
 * be declared for a single option.
 * The >> ( istream& ) operator must be implemented for typename T.
 */
template < typename T >
class config_option_list_c
: public config_option_i
{
public:
	typedef typename std::vector< T >::const_iterator iterator;
private:
	typedef std::vector< T > value_list;

public:
	/**
	 * Construct the config option.  The name is the key in the
	 * configuration file.
	 */
	config_option_list_c( const std::string &name )
	: m_name( name )
	, m_values()
	, m_set( false )
	, m_error( false )
	{}
	virtual ~config_option_list_c() {}

	/**
	 * Parse the string value in the typed m_value.
	 */
	virtual bool parse( const std::string &str_value )
	{
		std::istringstream input( str_value );
		m_values.push_back( T() );
		input >> m_values.back();
		m_error = input.fail();
		m_set = ! m_error;
	}

	/**
	 * Get the name of this config option.
	 */
	virtual const std::string & name() const { return m_name; }

	/**
	 * Check if the config option was set _correctly_ in the
	 * configuration file.
	 */
	virtual bool set() const { return m_set; }
	/**
	 * Check if the config option was set _incorrectly_ in the
	 * configuration file.
	 */
	virtual bool error() const { return m_error; }

	/**
	 * Return the number of parsed values.
	 */
	int size() const { return m_values.size(); }
	/**
	 * [] operator to return the ith value.
	 */
	const T & operator [] ( int i ) const { return m_values[ i ]; }
	/**
	 * Return the ith value.
	 */
	const T & value( int i ) const { return m_values[ i ]; }
	/**
	 * Get the begin iterator for the list of values.
	 */
	iterator begin() const { return m_values.begin(); }
	/**
	 * Get the end iterator for the list of values.
	 */
	iterator end() const { return m_values.end(); }

	// virtual std::string doc() const = 0;

private:
	std::string m_name;
	value_list m_values;
	bool m_set;
	bool m_error;
};


/**
 * A parser class to get all the configurations from a file.
 */
class configuration_c
{
private:
	typedef std::map< std::string, config_option_i * > option_map;

public:
	/**
	 * Construct the config parser for a given input
	 * stream.
	 */
	configuration_c();

	/**
	 * Add an option that can be set in the configuration file.
	 */
	void add( config_option_i & );

	/**
	 * Parse the input from the given input stream.
	 */
	void parse( std::istream &input );

	/**
	 * Check if there was an error parsing the configuration.
	 */
	bool error() const { return m_error; }

private:
	option_map m_option;
	bool m_error;
};


#endif

