#ifndef REQUEST_TYPE_H
#define REQUEST_TYPE_H
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


/**
 * An enumeration of the possible types of requests.
 */
enum request_type_e
{	RT_NULL
,	RT_CREATE_SESSION
,	RT_RENEW_SESSION
,	RT_KILL_SESSION
,	RT_CLOSE
};


/**
 * A string request_type
 */
class request_type_c
{
public:
	/**
	 * Empty constructor for a null request_type
	 */
	request_type_c();
	/**
	 * Construct a stringed request type given a request type enum
	 */
	request_type_c( request_type_e );
	/**
	 * Construct a stringed request type given a type name
	 */
	request_type_c( const std::string &name );
	/**
	 * Assignment operator
	 */
	request_type_c & operator = ( const request_type_c & );

	/**
	 * Return the type of request.
	 */
	request_type_e type() const { return m_type; }
	/**
	 * Return the string type of request.
	 */
	const std::string & name() const { return m_name; }

	/**
	 * Convert a request_type_e to a string.
	 */
	static const std::string & type_to_name( request_type_e );
	/**
	 * Convert a string to a request_type_e.
	 */
	static request_type_e name_to_type( const std::string & );

	static const std::string CREATE;
	static const std::string RENEW;
	static const std::string KILL;
	static const std::string CLOSE;

private:
	request_type_e m_type;
	const std::string &m_name;

	static const std::string s_null;
};


#endif

