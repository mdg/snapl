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
#include <fstream>
#include "request_reader.h"


static int open_test_connection( const char *contents )
{
	const char *connection_name = tmpnam( NULL );
	std::ofstream fout( connection_name );
	fout << contents;
	fout.close();
	FILE *connection_file = fopen( connection_name, "r" );
	return fileno( connection_file );
}


TESTPP( test_readline )
{
	const char *test_data = "session_status dog";
	int connection( open_test_connection( test_data ) );

	char buffer[40] = { 0 };
	int length = read( connection, buffer, sizeof(buffer) );
	std::cout << buffer << std::endl;
	close( connection );
}

