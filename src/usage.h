#ifndef USAGE_H
#define USAGE_H
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

#include <list>
#include <string>


/**
 * An option class for command line usage.
 */
class usage_option_c
{
public:
	/**
	 * List of usage option objects.
	 */
	typedef std::list< usage_option_c * > list;

public:
	/**
	 * Construct an option with the given modes of selection.
	 */
	usage_option_c( bool param_expected, char short_opt
			, const std::string &long_option
			, const std::string &description );

	/**
	 * Check if a param is expected for this option.
	 */
	bool param_expected() const { return m_param_expected; }
	/**
	 * Get the short style option string
	 */
	char short_opt() const { return m_short_opt; }
	/**
	 * Get the long style option string
	 */
	const std::string & long_opt() const { return m_long_opt; }
	/**
	 * Get the description of this option.
	 */
	const std::string & description() const { return m_description; }


	/**
	 * Set this option without a parameter.
	 */
	void set();
	/**
	 * Set this option w/ the given parameter.
	 */
	void set( const std::string &param );


	/**
	 * Check if this option was set at the command line.
	 */
	bool is_set() const { return m_set; }
	/**
	 * Check if this option was set with a parameter.
	 */
	bool has_param() const { return ! m_param.empty(); }
	/**
	 * Get the parameter for this option.
	 */
	const std::string & param() const { return m_param; }


	/**
	 * Build a line of text documenting this option.
	 */
	void write_usage_doc( std::ostream & ) const;
	/**
	 * Check if there was a usage error for this option.
	 */
	bool usage_error() const { return m_usage_error; }

private:
	bool m_param_expected;
	char m_short_opt;
	std::string m_long_opt;
	std::string m_description;

	bool m_set;
	bool m_usage_error;
	std::string m_param;
};


/**
 * An argument parser class
 */
class usage_c
{
public:
	/**
	 * Construct an empty arg parser
	 */
	usage_c() {}

	/**
	 * Add a usage option.
	 */
	void add( usage_option_c & );

	/**
	 * Parse a given set of args
	 * @return true if the usage was parsed successfully
	 */
	bool parse_args( int argc, const char **argv );

	/**
	 * Build a usage document for all options.
	 */
	void write_usage_doc( std::ostream & ) const;

private:
	/**
	 * search for an option given a short style character
	 */
	usage_option_c * find_short_option( char short_opt );
	/**
	 * search for an option given a long style string
	 */
	usage_option_c * find_long_option( const std::string &long_opt );

	usage_option_c::list m_option;
};


#endif

