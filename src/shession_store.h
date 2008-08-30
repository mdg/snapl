#ifndef SHESSION_STORE_H
#define SHESSION_STORE_H
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


/**
 * Abstract shession_store interface.
 */
class shession_store_i
{
public:
	/**
	 * Empty destructor to be overridden by implementing classes.
	 */
	virtual ~shession_store_i() {}

	/**
	 * Create a session for the given session_id.
	 */
	virtual void create_session( const std::string &session_id ) = 0;
	/**
	 * Check if the given session_id is live.
	 */
	virtual bool live_session( const std::string &session_id ) const = 0;
	/**
	 * Kill the given session if it exists.
	 */
	virtual void kill_session( const std::string &ession_id ) = 0;
};


#endif

