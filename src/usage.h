#ifndef ARG_PARSER_H
#define ARG_PARSER_H
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

#include <map>
#include <string>


/**
 * An option class for command line usage.
 */
class usage_option_c
{
public:
	/**
	 * Construct an option with the given modes of selection.
	 */
	option_c( char short_opt, const char *long_opt
			, bool param_expected
			, const char *description );

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
	 * Check if there was a usage error for this option.
	 */
	bool usage_error() const { return m_usage_error; }

private:
	bool m_has_param;
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
class arg_parser_c
{
public:
	/**
	 * Construct an empty arg parser
	 */
	arg_parser_c();

	void add_option_flag( char short_opt, const char *long_opt
			, const char *explanation );

	void add_option_parameter( char short_opt, const char *long_opt
			, const char *explanation );

	/**
	 * Parse a given set of args
	 */
	void parse_args( int argc, char **argv );

protected:
	virtual void set_flag( char flag ) = 0;
	virtual void set_short_option( 

private:
};


#endif

