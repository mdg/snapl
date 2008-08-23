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


void run_load( int n )
{
	shession_client_c client;
	if ( ! client.open( "localhost", 9000 ) ) {
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

	// check sessions and then create them
	std::list< std::string >::const_iterator it;
	for ( it=sessions.begin(); it!=sessions.end(); ++it ) {
		if ( client.live_session( *it ) ) {
			std::cerr << "session is already live\n";
		}
		client.create_session( *it );
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
	}
}


int main( int argc, char **argv )
{
	run_load( 100 );

	return 0;
}

