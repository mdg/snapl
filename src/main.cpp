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


#include <stdio.h>
#include <iostream>
#include <fstream>
#include "config_parser.h"
#include "connection_acceptor.h"
#include "request_reader.h"
#include "request_processor.h"
#include "shession_control.h"
#include "shession_store.h"
#include "usage.h"

static const int DEFAULT_TIMEOUT( 20 );
static const int DEFAULT_PORT( 9000 );


int main( int argc, const char **argv )
{
	usage_option_c debug_option( false, 'g', "debug"
			, "turn on debugging messages" );
	usage_c usage;
	usage.add( debug_option );

	if ( ! usage.parse_args( argc, argv ) ) {
		usage.write_usage_doc( std::cout );
		return -1;
	}

	// default options
	int session_timeout( DEFAULT_TIMEOUT );
	int port( DEFAULT_PORT );
	// parse the config file
	std::ifstream config_file( "shessiond.conf" );
	if ( config_file.is_open() ) {
		config_parser_c config( config_file );
		config.parse_input();

		if ( config.configured( "session-timeout" ) ) {
			session_timeout = config.int_value( "session-timeout" );
		}

		if ( config.configured( "port" ) ) {
			port = config.int_value( "port" );
		}
	}

	connection_acceptor_c acceptor;
	request_reader_c reader;
	shession_store_c store( session_timeout );
	request_processor_c processor( store );

	bool accept_err( acceptor.open( port ) );
	if ( ! accept_err ) {
		std::cerr << "Error opening acceptor.\n";
		return 1;
	}

	shession_control_c control( acceptor, reader, processor );
	control.main_loop();
	return 0;
}

