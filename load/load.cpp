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

#include "shession_client.h"
#include <iostream>
#include <list>
#include <sstream>
#include <time.h>


void run_load_1( int n )
{
	shession_client_c client;
	if ( ! client.open( "127.0.0.1", 9000 ) ) {
		std::cerr << "Error connecting socket.\n";
		return;
	}

	// create session ids in memory
	std::list< std::string > sessions;
	for ( int i( 0 ); i<n; ++i ) {
		std::ostringstream s;
		s << "session" << i;
		sessions.push_back( s.str() );
	}

	std::cerr << "begin load test\n";
	// clock_t start_ticks( clock() );
	time_t start_time( time( NULL ) );
	std::list< std::string >::const_iterator it;

	// check sessions and then create them
	for ( it=sessions.begin(); it!=sessions.end(); ++it ) {
		if ( client.live_session( *it ) ) {
			std::cerr << "session is already live\n";
		}
		client.create_session( *it );

		// std::cerr << "created session: " << *it << std::endl;
	}

	// check sessions now that they're there
	for ( it=sessions.begin(); it!=sessions.end(); ++it ) {
		if ( ! client.live_session( *it ) ) {
			std::cerr << "session isn't alive\n";
		}
		client.kill_session( *it );

		if ( client.live_session( *it ) ) {
			std::cerr << "session is still alive\n";
		}

		// std::cerr << "killed session: " << *it << std::endl;
	}

	// clock_t stop_time( clock() );
	// clock_t run_time( stop_time - start_time );
	// clock_t run_ms( ( run_time * 1000 ) / CLOCKS_PER_SEC );
	time_t run_time( time( NULL ) - start_time );
	std::cerr << n << " sessions in " << run_time << " seconds\n";
}

void run_load_2( int n )
{
	shession_client_c client;
	if ( ! client.open( "127.0.0.1", 9000 ) ) {
		std::cerr << "Error connecting socket.\n";
		return;
	}

	// create session ids in memory
	std::list< std::string > sessions;
	for ( int i( 0 ); i<n; ++i ) {
		std::ostringstream s;
		s << "load2_session_" << i;
		sessions.push_back( s.str() );
	}

	std::cerr << "setup load test\n";
	std::list< std::string >::const_iterator it;
	// create all them
	for ( it=sessions.begin(); it!=sessions.end(); ++it ) {
		client.create_session( *it );
	}

	std::cerr << "begin load test\n";
	time_t start_time( time( NULL ) );

	// check sessions now that they're there
	time_t stop_time( time( NULL ) + 12 );
	it = sessions.begin();
	int count( 0 );
	while ( time( NULL ) < stop_time ) {
		client.live_session( *it );
		++count;
		if ( ++it == sessions.end() ) {
			it = sessions.begin();
		}
	}

	std::cerr << count << " requests in 12 seconds\n";
	std::cerr << 5 * count << " requests per minute\n";
	std::cerr << count / 12 << " requests per second\n";
}


int main( int argc, char **argv )
{
	run_load_2( 80 );

	return 0;
}

