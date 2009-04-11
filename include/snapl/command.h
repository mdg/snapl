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

namespace snapl {

class message_c;


/**
 * Base class for snapl commands.
 */
class command_c
{
public:
	const std::string & service() const { return m_service; }

	const arg_list_c & input() const { return m_input; }
	void get_input( message_c & ) const;
	void set_input( const message_c & );

	const arg_list_c & output() const { return m_output; }
	/**
	 * Copy the output data to a message.
	 */
	void get_output( message_c & ) const;
	/**
	 * Set the output arguments to the values
	 * in the given message_arg_list.
	 */
	void set_output( const message_c & );

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
	const std::string & response_code() const { return m_code; }
	/**
	 * Get the response msg for this command.
	 */
	const std::string & response_msg() const { return m_msg; }


protected:
	/**
	 * Protected constructor.
	 */
	command_c( const std::string &service )
	: m_service( service )
	{}

	arg_list_c m_input;
	arg_list_c m_output;

private:
	std::string m_service;

	std::string m_response_code;
	std::string m_response_msg;

private:
	/**
	 * privatised, unimplemented copy constructor to restrict usage.
	 */
	command_i( const command_i & );
};


} // namespace

#endif

