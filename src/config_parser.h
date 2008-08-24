#ifndef CONFIG_H
#define CONFIG_H
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


/**
 * A parser class to get all the configurations from a file.
 */
class config_parser_c
{
public:
	/**
	 * Construct the config parser for a given input
	 * stream.
	 */
	config_parser_c( std::istream &input );
	/**
	 * Parse the input from the given input stream.
	 */
	void parse_input();

	/**
	 * Check if the given key is configured.
	 */
	bool configured( const std::string &key ) const;

	/**
	 * Get a configured value for a given key.
	 */
	const std::string & value( const std::string &key ) const;

private:
	std::istream &m_input;
	std::map< std::string, std::string > m_config;
	std::string m_empty_value;
};


#endif

