#ifndef COMMAND_H
#define COMMAND_H
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

class request_c;
class response_c;


/**
 * Untyped interface for client commands.
 */
class command_i
{
public:
	const request_c & command_request() const { return m_command_request; }
	response_c & command_response() { return m_command_response; }

protected:
	command_i( const request_c &req, response_c &resp )
	: m_command_request( req )
	, m_command_response( resp )
	{}

private:
	const request_c &m_command_request;
	response_c &m_command_response;
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
	/**
	 * Get the template-typed response object.
	 */
	RespT & response() { return m_response; }

protected:
	command_c()
	: command_i( m_request, m_response )
	, m_request()
	, m_response()
	{}

	command_c( const ReqT &req )
	: command_i( m_request, m_response )
	, m_request( req )
	, m_response()
	{}

	ReqT m_request;
	RespT m_response;
};


#endif

