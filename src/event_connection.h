#ifndef SNAPL_EVENT_CONNECTION_H
#define SNAPL_EVENT_CONNECTION_H
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

#include "net/connection.h"


/**
 * An interface to handle connections and parsing their input.
 */
class event_connection_c
{
public:
	/**
	 * Virtual destroyer of the connection
	 */
	virtual ~event_connection_c();

	/**
	 * Return the server port that this connection is on
	 */
	virtual short port() const;

	/**
	 * Read a line of input from this connection.
	 */
	virtual void read_line( std::string& );

	/**
	 * Write a string back to the connection.
	 */
	virtual void write_line( const std::string & );

	/**
	 * Check if this connection has more lines of input
	 * ready.
	 */
	virtual bool line_ready() const;
};


#endif

