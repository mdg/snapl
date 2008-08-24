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


#include "testpp.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "connected_socket.h"
#include "request.h"
#include "request_reader.h"


static request_reader_c * create_reader( const char *contents )
{
	char connection_name[] = "/tmp/request_reader_test_XXXXXX";
	int connection = mkstemp( connection_name );
	write( connection, contents, strlen( contents ) + 1 );
	close( connection );
	// std::cerr << connection_name << std::endl;
	FILE *connection_file = fopen( connection_name, "r" );
	int fd( fileno( connection_file ) );
	connection_i *conn = new connected_socket_c( fd );
	return new request_reader_c( conn );
}


TESTPP( test_readline )
{
	const char *test_data = "status dog\n";
	std::auto_ptr< request_reader_c > reader( create_reader( test_data ) );

	std::auto_ptr< request_c > req( reader->create_request() );
	static_cast< request_c * >( NULL ) != actual( req.get() );

	RT_SESSION_STATUS == actual( req->request_type() );
	std::string( "dog" ) == actual( req->session_id() );

	close( reader->release_connection() );
}


TESTPP( test_multiline )
{
	const char *test_data = "status dog\n" \
				 "create cat\n";
	std::auto_ptr< request_reader_c > reader( create_reader( test_data ) );

	std::auto_ptr< request_c > req( reader->create_request() );
	RT_SESSION_STATUS == actual( req->request_type() );
	std::string( "dog" ) == actual( req->session_id() );

	req.reset( reader->create_request() );
	RT_CREATE_SESSION == actual( req->request_type() );
	std::string( "cat" ) == actual( req->session_id() );

	close( reader->release_connection() );
}


TESTPP( test_incomplete )
{
	// this is a bad request type
	const char *test_data = "session_status dog";
	std::auto_ptr< request_reader_c > reader( create_reader( test_data ) );

	// should be created, but w/ null request type
	std::auto_ptr< request_c > req( reader->create_request() );
	static_cast< request_c * >( NULL ) == actual( req.get() );

	close( reader->release_connection() );
}



TESTPP( test_bad_request )
{
	// this is a bad request type
	const char *test_data = "session_status dog\n";
	std::auto_ptr< request_reader_c > reader( create_reader( test_data ) );

	// should be created, but w/ null request type
	std::auto_ptr< request_c > req( reader->create_request() );
	static_cast< request_c * >( NULL ) != actual( req.get() );
	RT_NULL == actual( req->request_type() );
	std::string( "dog" ) == actual( req->session_id() );

	close( reader->release_connection() );
}

