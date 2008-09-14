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
#include "request_type.h"


class connection_i;
class request_c;
class shession_store_i;


/**
 * Abstract request_processor interface
 */
class request_processor_i
{
public:
	request_type_e request_type() const { return m_request_type; }
	virtual void process( const request_c &, connection_i & ) = 0;
protected:
	request_processor_i( request_type_e, shession_store_i & );
	shession_store_i &m_store;
	request_type_e m_request_type;
};


/**
 * Create session request processor
 */
class create_request_processor_c
: public request_processor_i
{
public:
	create_request_processor_c( shession_store_i & );
	/**
	 * Process a create request.
	 */
	virtual void process( const request_c &, connection_i & );
};


/**
 * Renew session request processor
 */
class renew_request_processor_c
: public request_processor_i
{
public:
	renew_request_processor_c( shession_store_i & );
	/**
	 * Process a renew request.
	 */
	virtual void process( const request_c &, connection_i & );
};


/**
 * Kill session request processor
 */
class kill_request_processor_c
: public request_processor_i
{
public:
	kill_request_processor_c( shession_store_i & );
	/**
	 * Process a kill request.
	 */
	virtual void process( const request_c &, connection_i & );
};


/**
 * The close request processor.
 */
class close_request_processor_c
: public request_processor_i
{
public:
	close_request_processor_c( shession_store_i & );
	virtual void process( const request_c &, connection_i & );
};


#endif

