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
#include "usage.h"

static const int DEFAULT_TIMEOUT( 20 );


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

	std::ifstream config_file( ".shessiond" );
	config_parser_c config( config_file );
	config.parse_input();

	int session_timeout( DEFAULT_TIMEOUT );
	if ( config.configured( "session_timeout" ) ) {
		config.value( "session_timeout" );
	}

	connection_acceptor_c acceptor;
	request_reader_c reader;
	request_processor_c processor;
	int port( 9000 ); // make this configurable obviously

	bool accept_err( acceptor.open( port ) );
	if ( ! accept_err ) {
		std::cerr << "Error opening acceptor.\n";
		return 1;
	}

	shession_control_c control( acceptor, reader, processor );
	control.main_loop();
	return 0;
}

