#ifndef MIRROR_PROTOCOL_H
#define MIRROR_PROTOCOL_H
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

#include "protocol.h"
#include "request_processor.h"


/**
 * Request to mirror a session that was created or renewed on another
 * from another shessiond server.
 */
class mirror_request_processor_c
: public request_processor_i
{
public:
	mirror_request_processor_c( shession_store_i & );
	virtual void process( const request_c &, response_c & );
};


/**
 * Request to dump the full shession_store out for a mirrored server
 * that is just starting up.
 */
class export_request_processor_c
: public request_processor_i
{
public:
	export_request_processor_c( shession_store_i & );
	virtual void process( const request_c &, response_c & );
};


#endif

