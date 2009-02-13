#ifndef RESPONSE_H
#define RESPONSE_H
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

#include "arg.h"
#include <string>
#include <sstream>


/**
 * The response object for request processors to send output
 * back to a client.
 */
class response_c
{
public:
	/**
	 * Construct an empty response object.  It will be filled
	 * in by the request processors.
	 */
	response_c();

	/**
	 * Flag this response as successful.
	 * Include an optional message.
	 */
	void ok( const std::string &msg = std::string() );

	/**
	 * Flag this response as having failed.
	 * Include an optional error message.
	 */
	void err( const std::string &msg = std::string() );

	/**
	 * Add a line of text as output for this response.
	 */
	void write_line( const std::string &line );

	/**
	 * Get the code & message in a single line.
	 */
	std::string coded_msg() const;
	/**
	 * Get the code for this response. ok or err
	 */
	const std::string & code() const { return m_code; }
	/**
	 * Get the msg that is part of this response.
	 */
	const std::string & msg() const { return m_msg; }

	/**
	 * Check if this response has content.
	 */
	bool has_content() const { return m_has_content; }
	/**
	 * Get the content to be sent with this response.
	 */
	std::string content() const { return m_content.str(); }

protected:
	arg_list_c m_arg;
private:
	std::string m_code;
	std::string m_msg;
	std::ostringstream m_content;
	bool m_has_content;
};


#endif

