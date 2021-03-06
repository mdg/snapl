#ifndef SNAPL_RESPONSE_H
#define SNAPL_RESPONSE_H
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

namespace snapl {

class message_c;


/**
 * The response object for request processors to send output
 * back to a client.
 */
class response_c
{
public:

	/**
	 * Add a line of text as output for this response.
	 */
	void write_line( const std::string &line );

	/**
	 * Check if this response has content.
	 */
	bool has_content() const { return m_has_content; }
	/**
	 * Get the content to be sent with this response.
	 */
	std::string content() const { return m_content.str(); }

protected:
private:
	std::ostringstream m_content;
	bool m_has_content;
};


} // namespace

#endif

