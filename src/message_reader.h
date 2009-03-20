#ifndef MESSAGE_READER_H
#define MESSAGE_READER_H
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

#include <memory>

class connection_i;
class server_message_c;


/**
 * A class to read a message from a connection.
 */
class message_reader_c
{
public:
	/**
	 * Construct the server message from a line of text and a connection.
	 */
	message_reader_c( connection_i * );
	/**
	 * Destroy the server_message.
	 */
	~message_reader_c();

	/**
	 * Check if this message_reader has completely read a message.
	 */
	bool complete() const { return m_complete; }

	/**
	 * Check if this message_reader has nothing to read.
	 */
	bool empty() const { return m_empty; }

	/**
	 * Read a message from the given connection.
	 * @return true if the message is read completely.
	 */
	bool read();

	/**
	 * Get a complete message from the reader.
	 */
	server_message_c * message();

private:
	connection_i &m_connection;
	std::auto_ptr< server_message_c > m_message;
	bool m_complete;
	bool m_empty;
};


#endif

