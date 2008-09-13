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

#include <iostream>
#include <map>

#include <set>


class config_option_c
{
public:
	config_option_c( const std::string &name );
	virtual ~config_option_c();
	virtual bool parse( const std::string & ) = 0;
	virtual std::string doc() const = 0;

private:
	std::string m_name;
};

class str_config_option_c
: public config_option_c
{
public:
};

class int_config_option_c
: public config_option_c
{
};


/**
 * A parser class to get all the configurations from a file.
 */
class configuration_c
{
public:
	/**
	 * Construct the config parser for a given input
	 * stream.
	 */
	configuration_c();

	/**
	 * Add an option that can be set in the configuration file.
	 */
	void option( const std::string & );
	void int_option( const std::string & );
	void bool_option( const std::string & );

	/**
	 * Parse the input from the given input stream.
	 */
	void parse_input( std::istream &input );

	/**
	 * Check if the given key is configured.
	 */
	bool configured( const std::string &key ) const;

	/**
	 * Get a configured string value for a given key.
	 */
	const std::string & value( const std::string &key ) const;

	/**
	 * Get a configured int value for a given key.
	 * Returns 0 if the value is not a valid number.
	 * This is lame and needs to be fixed.
	 */
	int int_value( const std::string &key ) const;

private:
	std::set< std::string > m_option;
	std::map< std::string, std::string > m_config;
	std::string m_empty_value;
};


#endif

