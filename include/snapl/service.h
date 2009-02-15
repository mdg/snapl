#ifndef SNAPL_SERVICE_H
#define SNAPL_SERVICE_H
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


/**
 * Untyped service interface.  This gets passed around the server and is
 * what gets called by the type-agnostic framework.
 */
class service_i
{
public:
	virtual ~service_i() {}

	/**
	 * Execute this untyped service.
	 */
	virtual void execute( const message_c &, message_c & ) = 0;
};


/**
 * Typed service class.
 * This transfers untyped data into typed objects, calls the service
 * execution and transfers the typed response into untyped data.
 */
template < typename ReqT, typename RespT >
class service_c
: public service_i
{
public:
	/**
	 * Construct a service w/ no parameters.
	 */
	service_c() {}

	/**
	 * Execute the service with an input message and output message.
	 * This creates typed request & response objects and passes
	 * to the typed execute function.
	 */
	virtual void execute( const message_c &req_msg, message_c &resp_msg )
	{
		ReqT request( req_msg );
		RespT response;
		execute( request, response );
		// response.copy( resp_msg );
	}

	/**
	 * Virtual execute method w/ typed request & response parameters.
	 * This must be overridden by the implementing service class.
	 */
	virtual void execute( const ReqT &, RespT & ) = 0;

};


#endif

