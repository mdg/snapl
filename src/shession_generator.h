#ifndef SHESSION_GENERATOR_H
#define SHESSION_GENERATOR_H
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
 * Abstract interface for generating shession_ids.
 */
class shession_generator_i
{
public:
	/**
	 * Empty destructor to be overridden by implementing classes.
	 */
	virtual ~shession_generator_i() {}

	/**
	 * Create a session_id for the given user_id.
	 */
	virtual std::string shession_id( const std::string &user_id ) = 0;

};


/**
 * Implementing class for the shession_generator interface.
 * This might need to be renamed and put in a different file
 * at some point.  For now it will live here.
 */
class shession_generator_c
: public shession_generator_i
{
public:
	/**
	 * Destructor for the session_generator object.
	 */
	virtual ~shession_generator_c();

	/**
	 * Create a session id for the optional user_id
	 */
	virtual std::string shession_id( const std::string &user_id );

};


#endif

