#ifndef REQUEST_PROCESSOR_H
#define REQUEST_PROCESSOR_H

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

class request_c;
class response_c;


/**
 * Abstract action interface
 */
class action_i
{
public:
	const std::string & request_type() const { return m_request_type; }
	virtual void execute( const request_c &, response_c & ) = 0;

protected:
	action_i( const std::string &req_type )
	: m_request_type( req_type )
	{}

private:
	const std::string m_request_type;
};


#endif
