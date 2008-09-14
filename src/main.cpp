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
#include "configuration.h"
#include "connection_acceptor.h"
#include "request_reader.h"
#include "request_processor.h"
#include "shession_control.h"
#include "shession_store.h"
#include "usage.h"

static const int DEFAULT_SESSION_TIMEOUT( 20 );
static const int DEFAULT_SERVICE_PORT( 9000 );
static const int DEFAULT_ADMIN_PORT( 9001 );
static const int DEFAULT_MIRROR_PORT( 9002 );
static const bool DEFAULT_LOCALHOST_LOCKDOWN( false );


int main( int argc, const char **argv )
{
	// command line usage options
	usage_option_c debug_option( false, 'g', "debug"
			, "turn on debugging messages" );

	// config options
	config_option_c< int > session_timeout( "session-timeout"
			, DEFAULT_SESSION_TIMEOUT );
	config_option_c< int > service_port( "service-port"
			, DEFAULT_SERVICE_PORT );
	config_option_c< int > admin_port( "admin-port", DEFAULT_ADMIN_PORT );
	config_option_c< int > mirror_port( "mirror-port"
			, DEFAULT_MIRROR_PORT );
	config_option_c< bool > localhost_lockdown( "localhost-lockdown"
			, DEFAULT_LOCALHOST_LOCKDOWN );

	config_option_list_c< std::string > mirrors( "mirror" );
	config_option_list_c< std::string > service_whitelist(
			"service-whitelist" );
	config_option_list_c< std::string > admin_whitelist(
			"admin-whitelist" );

	// parse usage
	usage_c usage;
	usage.add( debug_option );

	if ( ! usage.parse_args( argc, argv ) ) {
		usage.write_usage_doc( std::cout );
		return -1;
	}

	// parse the config file
	std::ifstream config_file( "shessiond.conf" );
	if ( config_file.is_open() ) {
		configuration_c config;
		config.add( session_timeout );
		config.add( service_port );
		config.add( admin_port );
		config.add( mirror_port );
		config.add( mirrors );
		config.add( service_whitelist );
		config.add( admin_whitelist );
		config.parse( config_file );

		std::cout << "mirrors.size() == " << mirrors.size()
			<< std::endl;
		std::cout << "service_whitelist.size() == "
			<< service_whitelist.size() << std::endl;
		std::cout << "admin_whitelist.size() == "
			<< admin_whitelist.size() << std::endl;
	}


	connection_acceptor_c acceptor;
	request_reader_c reader;
	shession_store_c store( session_timeout.value() );
	request_processor_c processor( store );

	bool accept_open( acceptor.open( service_port.value()
				, admin_port.value() ) );
	if ( ! accept_open ) {
		std::cerr << "Error opening acceptor.\n";
		return 1;
	}

	shession_control_c control( acceptor, reader, processor );
	control.main_loop();
	return 0;
}

