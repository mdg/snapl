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
	client_connection_c conn;
	conn.connect( "127.0.0.1", 9000 );
	client_c client( conn );

	get_command_c get( "dog" );
	client.send_request( get );
	client.wait_for_response( get );

	std::cerr << "response output = " << get.response().output()
		<< std::endl;
}


void run_load_2( int n, int seconds )
{
	client_c client;
	/*
	if ( ! client.open( "127.0.0.1", 9000 ) ) {
		std::cerr << "Error connecting socket.\n";
		return;
	}
	*/

	// create session ids in memory
	std::map< std::string, std::string > sessions;
	for ( int i( 0 ); i<n; ++i ) {
		std::ostringstream s;
		s << "load2_user_" << i;
		sessions[ s.str() ];
	}

	std::cerr << "setup load test\n";
	std::map< std::string, std::string >::const_iterator it;
	// create all them
	for ( it=sessions.begin(); it!=sessions.end(); ++it ) {
		/*
		create_command_c create_cmd( it->first );
		client.send_request( create_cmd );
		client.wait_for_response( create_cmd );
		sessions[ it->first ] = create_cmd.session_id();
		*/
	}

	std::cerr << "begin load test\n";

	// check sessions now that they're there
	it = sessions.begin();
	int count( 0 );
	// see how many queries can be made in a certain time
	time_t stop_time( time( NULL ) + seconds );
	while ( time( NULL ) < stop_time ) {
		/*
		renew_command_c renew_cmd( *it );
		client.send_request( renew_cmd );
		client.wait_for_response( renew_cmd );
		*/

		std::cerr << "executed live_session\n";
		++count;
		if ( ++it == sessions.end() ) {
			std::cerr << "start over again\n";
			// start over again
			it = sessions.begin();
		}
	}

	std::cerr << count << " requests in " << seconds << " seconds\n";
	std::cerr << ( 60 * count ) / seconds << " requests per minute\n";
	std::cerr << count / seconds << " requests per second\n";
}


int main( int argc, char **argv )
{
	// run_load_2( 1, 12 );
	functional_test();

	return 0;
}

