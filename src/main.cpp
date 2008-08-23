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
#include "connection_acceptor.h"
#include "request_processor.h"
#include "shession_control.h"


int main( int argc, char **argv )
{
	connection_acceptor_c acceptor;
	request_processor_c processor;
	int port( 9000 ); // make this configurable obviously

	bool accept_err( acceptor.open( port ) );
	if ( ! accept_err ) {
		std::cerr << "Error opening acceptor.\n";
		return 1;
	}

	shession_control_c control( acceptor, processor );
	control.execute();
	return 0;
}

