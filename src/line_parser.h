#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H
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
 * A class to parse strings for requests.
 */
class request_parser_c
{
public:
	/**
	 * Construct a request parser object.
	 */
	// request_parser_c() {}
	/**
	 * Destroy the request parser object.
	 */
	// ~request_reader_c() {}

	/**
	 * Add input to this parser.
	 */
	void add_input( const std::string & );

	/**
	 * Parse the input into a line of text.
	 */
	std::string readline();

private:
	std::string m_input;
};


#endif

