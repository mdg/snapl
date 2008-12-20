#ifndef PROTOCOL_H
#define PROTOCOL_H
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

#include <map>
#include <string>

class action_i;


class protocol_c
{
	typedef std::map< std::string, action_i * > action_map;
	typedef action_map::iterator action_iterator;

public:
	protocol_c( short port );
	virtual ~protocol_c();
	void add( action_i & );

	const std::string & name() const { return m_name; }
	short port() const { return m_port; }
	bool silent() const { return m_silent; }
	action_i * action( const std::string & );

private:
	std::string m_name;
	action_map m_action;
	short m_port;
	bool m_silent;
};


#endif

