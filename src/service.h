#ifndef SERVICE_H
#define SERVICE_H
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



/**
 * Untyped service interface.  This gets passed around the server and is
 * what gets called by the type-agnostic framework.
 */
class service_i
{
	virtual ~service_i() {}

	/**
	 * Execute this untyped service.
	 */
	virtual void execute() = 0;

	virtual const response_c & response() const = 0;
};


/**
 * Typed service class.
 * This transfers untyped data into typed objects, calls the service
 * execution and transfers the typed response into untyped data.
 */
template < typename ReqT, typename RespT >
class service_c
{
public:
	service_c( const std::string &req )
	: m_request( req )
	, m_response()
	{}

	virtual const response_c & response() const { return m_response; }

protected:
	const ReqT m_request;
	RespT m_response;
};


#endif

