#ifndef LINE_PARSER_H
#define LINE_PARSER_H
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
class line_parser_c
{
public:
	/**
	 * Add input to this parser.
	 */
	void add_input( const std::string & );

	/**
	 * Parse the input into a line of text.
	 */
	void readline( std::string & );

private:
	std::string m_input;
};


#endif
