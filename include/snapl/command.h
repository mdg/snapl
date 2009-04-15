#ifndef SNAPL_COMMAND_H
#define SNAPL_COMMAND_H
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

#include <string>
#include "snapl/arg.h"

namespace snapl {

class message_c;


/**
 * Base class for snapl commands.
 */
class command_c
{
public:
	const std::string & service() const { return m_service; }

	const arg_list_c & request() const { return m_request; }
	void get_request( message_c & ) const;
	bool set_request( const message_c & );

	const arg_list_c & response() const { return m_response; }
	/**
	 * Copy the output data to a message.
	 */
	void get_response( message_c & ) const;
	/**
	 * Set the output arguments to the values
	 * in the given message_arg_list.
	 */
	bool set_response( const message_c & );

	/**
	 * Flag this response as successful.
	 */
	void ok();
	/**
	 * Flag this response as having failed.
	 * Must include an error message to explain the error.
	 */
	void err( const std::string &msg );
	/**
	 * Flag this response as having failed.
	 * Report the file and line of the error.
	 */
	void err( const std::string &file, int line );

	/**
	 * Get the response code for this command. ok or err
	 */
	const std::string & response_code() const { return m_response_code; }
	/**
	 * Get the response msg for this command.
	 */
	const std::string & response_msg() const { return m_response_msg; }


protected:
	/**
	 * Protected constructor.
	 */
	command_c( const std::string &service )
	: m_service( service )
	{
		m_request << m_service;
		m_response << m_response_code << m_response_msg;
	}

	arg_list_c m_request;
	arg_list_c m_response;

private:
	std::string m_service;

	std::string m_response_code;
	std::string m_response_msg;

private:
	/**
	 * privatised, unimplemented copy constructor to restrict usage.
	 */
	command_c( const command_c & );
};


} // namespace

#endif

