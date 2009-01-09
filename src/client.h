#ifndef CLIENT_H
#define CLIENT_H
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

class command_i;


/**
 * Framework interface for sending commands 
 */
class client_i
{
public:
	virtual ~client_i() {}

	/**
	 * Send the command through to the remote server.
	 */
	virtual void send( command_i & ) = 0;

	/**
	 * Wait for a response to a given command.
	 */
	virtual void wait( command_i & ) = 0;
};


/**
 * Implemented class of the client interface.
 */
class client_c
{
public:
	client_c();

	template < typename ReqT, typename RespT >
	void send_request( const command_c< ReqT, RespT > &cmd )
	{
		message_c msg;
		message_import_c msg_import( msg );
		msg_import.copy_message( cmd.request() );
		send_message( msg );
	}

	virtual void send_request( command_i & );

	virtual void wait_for_response( command_i & );

	void send_message( const message_c & );

private:
	// client_factory_i &m_factory;
};


#endif

