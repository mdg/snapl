#ifndef CONNECTION_H
#define CONNECTION_H
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
 * An interface to handle connections and parsing their input.
 */
class connection_i
{
public:
	/**
	 * Virtual destroyer of the connection
	 */
	virtual ~connection_i() {}

	/**
	 * Return the server port that this connection is on
	 */
	virtual short port() const = 0;

	/**
	 * Read a line of input from this connection.
	 */
	virtual void read_line( std::string& ) = 0;

	/**
	 * Write a string back to the connection.
	 */
	virtual void write_line( const std::string & ) = 0;

	/**
	 * Check if this connection has more lines of input
	 * ready.
	 */
	virtual bool line_ready() const = 0;
};


#endif

