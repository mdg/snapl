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


/**
 * Create a mocked connection that contains the given contents.
 */
static connection_i * create_connection( const char *contents )
{
	char connection_name[] = "/tmp/request_reader_test_XXXXXX";
	int connection = mkstemp( connection_name );
	write( connection, contents, strlen( contents ) + 1 );
	close( connection );
	// std::cerr << connection_name << std::endl;
	FILE *connection_file = fopen( connection_name, "r" );
	int fd( fileno( connection_file ) );
	return new connected_socket_c( fd );
}


/**
 * Test that reading by line works.
 */
TESTPP( test_readline )
{
	const char *test_data = "renew dog\n";
	std::auto_ptr< connection_i > conn( create_connection( test_data ) );
	request_reader_c reader;

	std::auto_ptr< request_c > req( reader.create_request( *conn ) );
	static_cast< request_c * >( NULL ) != actual( req.get() );

	RT_RENEW_SESSION == actual( req->request_type() );
	std::string( "dog" ) == actual( req->session_id() );
}


/**
 * Test that lines are correctly split between lines and there's
 * no overlap.
 */
TESTPP( test_multiline )
{
	const char *test_data = "renew dog\n" \
				 "create cat\n";
	std::auto_ptr< connection_i > conn( create_connection( test_data ) );
	request_reader_c reader;

	std::auto_ptr< request_c > req( reader.create_request( *conn ) );
	RT_RENEW_SESSION == actual( req->request_type() );
	std::string( "dog" ) == actual( req->session_id() );

	req.reset( reader.create_request( *conn ) );
	RT_CREATE_SESSION == actual( req->request_type() );
	std::string( "cat" ) == actual( req->session_id() );
}


/**
 * Test that the request_reader doesn't create requests based on partial
 * lines that aren't completed with the newline.
 */
TESTPP( test_incomplete )
{
	// this is a bad request type
	const char *test_data = "session_status dog";
	std::auto_ptr< connection_i > conn( create_connection( test_data ) );
	request_reader_c reader;

	// should be created, but w/ null request type
	std::auto_ptr< request_c > req( reader.create_request( *conn ) );
	static_cast< request_c * >( NULL ) == actual( req.get() );
}


/**
 * Test that the invalid request_type doesn't make things freak out
 * and gives useful info to determine that.
 */ 
TESTPP( test_bad_request )
{
	// this is a bad request type
	const char *test_data = "session_status dog\n";
	std::auto_ptr< connection_i > conn( create_connection( test_data ) );
	request_reader_c reader;

	// should be created, but w/ null request type
	std::auto_ptr< request_c > req( reader.create_request( *conn ) );
	static_cast< request_c * >( NULL ) != actual( req.get() );
	RT_NULL == actual( req->request_type() );
	std::string( "dog" ) == actual( req->session_id() );
}

