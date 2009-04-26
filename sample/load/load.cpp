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

#include "snapl/client.h"
#include "sample_protocol.h"
#include "snapl/net/client_connection.h"
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <ctime>


void functional_test()
{
	snapl::client_connection_c conn;
	conn.connect( "127.0.0.1", 9000 );
	snapl::client_c client( conn );

	get_command_c get( "dog" );
	client.send_request( get );
	client.wait_for_response( get );

	std::cerr << "response output = " << get.output
		<< std::endl;
}


void run_load_2( int n, int seconds )
{
	snapl::client_connection_c conn;
	conn.connect( "127.0.0.1", 9000 );
	snapl::client_c client( conn );

	// set to second boundary
	time_t boundary_time( time( NULL ) + 1 );
	while ( time( NULL ) < boundary_time ) {
		// spin
	}

	std::cerr << "begin load test\n";

	// check sessions now that they're there
	int count( 0 );
	// see how many queries can be made in a certain time
	time_t stop_time( time( NULL ) + seconds );
	while ( time( NULL ) < stop_time ) {
		std::ostringstream msg;
		msg << "value_" << ++count;

		get_command_c get_cmd( msg.str() );
		client.send_request( get_cmd );
		client.wait_for_response( get_cmd );
		/*
		std::cout << "response = '" << get_cmd.response().output()
			<< "'\n";
			*/
	}

	std::cerr << count << " requests in " << seconds << " seconds\n";
	std::cerr << ( 60 * count ) / seconds << " requests per minute\n";
	std::cerr << count / seconds << " requests per second\n";
}


int main( int argc, char **argv )
{
	functional_test();
	run_load_2( 1, 12 );

	return 0;
}

