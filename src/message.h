#ifndef MESSAGE_H
#define MESSAGE_H
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


class message_i
{
public:
	virtual ~message_i() {}

	virtual void parse_message( istream & ) = 0;
	virtual void format_message( ostream & ) = 0;

	virtual connection_i * release_connection() = 0;
};

/**
 * Maybe unnecessary.  Just message_i for now probably.
 */
class incoming_message_i
{
public:
	virtual void parse_message( istream & ) = 0;
};

/**
 * Maybe unnecessary.  Just message_i for now probably.
 */
class outgoing_message_i
{
public:
	virtual void format_message( ostream & ) = 0;
};


class request_message_i
: public message_i
{
public:
	virtual const request_c & request() const = 0;
};

class response_message_i
: public message_i
{
{
public:
	virtual const response_c & response() const = 0;
};



#endif

