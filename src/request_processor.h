#ifndef REQUEST_PROCESSOR_H
#define REQUEST_PROCESSOR_H

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

#include <set>
#include <string>


class connection_i;
class request_c;
class response_c;
class shession_generator_i;
class shession_store_i;


/**
 * Abstract request_processor interface
 */
class action_i
{
public:
	const std::string & request_type() const { return m_request_type; }
	virtual void process( const request_c &, response_c & ) = 0;

protected:
	action_i( const std::string &req_type, shession_store_i & );

	shession_store_i &m_store;
	const std::string m_request_type;
};

// planning to rename request_processor_i to action_i
// typedef action_i request_processor_i;


/**
 * Create session request processor
 */
class create_action_c
: public action_i
{
public:
	create_action_c( shession_store_i &
			, shession_generator_i & );
	/**
	 * Process a create request.
	 */
	virtual void process( const request_c &, response_c & );

private:
	shession_generator_i &m_generator;
};


/**
 * Renew session request processor
 */
class renew_action_c
: public action_i
{
public:
	renew_action_c( shession_store_i & );
	/**
	 * Process a renew request.
	 */
	virtual void process( const request_c &, response_c & );
};


/**
 * Kill session action
 */
class kill_action_c
: public action_i
{
public:
	kill_action_c( shession_store_i & );
	/**
	 * Process a kill request.
	 */
	virtual void process( const request_c &, response_c & );
};


/**
 * The close request processor.
 */
class close_action_c
: public action_i
{
public:
	close_action_c( shession_store_i & );
	virtual void process( const request_c &, response_c & );
};


#endif

