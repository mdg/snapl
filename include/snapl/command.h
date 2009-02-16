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

class message_c;
class request_c;
class response_c;


/**
 * Untyped interface for client commands.
 */
class command_i
{
public:
	/**
	 * Get a request for this command.
	 */
	const request_c & command_request() const { return m_command_request; }

	/**
	 * Set the response for this command from a given message.
	 */
	void set_command_response( const message_c & );

protected:
	command_i( const request_c &req, response_c &resp )
	: m_command_request( req )
	, m_command_response( resp )
	{}

private:
	const request_c &m_command_request;
	response_c &m_command_response;

private:
	/**
	 * privatised, unimplemented copy constructor to restrict usage.
	 */
	command_i( const command_i & );
};


/**
 * Typed class for client commands to the server.
 * Uses templated request & response that are shared w/ the
 * server-side service.
 */
template < typename ReqT, typename RespT >
class command_c
: public command_i
{
public:
	/**
	 * Get the template-typed request object.
	 */
	const ReqT & request() const { return m_request; }
	/**
	 * Get the template-typed const response object.
	 */
	const RespT & response() const { return m_response; }

protected:
	command_c()
	: command_i( m_request, m_response )
	, m_request()
	, m_response()
	{}

	ReqT m_request;
	RespT m_response;

private:
	/**
	 * privatised, unimplemented copy constructor to restrict usage.
	 */
	command_c( const command_c< ReqT, RespT > & );
};


#endif

