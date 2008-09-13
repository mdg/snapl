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


testpp_runner::testpp_runner( testpp_func f, const char *test_name
	       , const char *file_name, int line_number )
: f_testpp( f )
, m_test_name( test_name )
, m_file_name( file_name )
, m_line_number( line_number )
{
	/*
	static int i( 0 );
	std::cerr << "runners().push_back( " << i++ << " )"
		<< " = " << runners().size() << std::endl;
	*/
	runners().push_back( this );
}

testpp_runner::~testpp_runner()
{
	std::list< testpp_runner * >::iterator it;
	it = std::find( runners().begin(), runners().end(), this );
	if ( it == runners().end() ) {
		runners().erase( it );
	}
}

void testpp_runner::run()
{
	std::cout << "testpp( " << m_file_name << ':' << m_test_name;
	std::cout << ':' << m_line_number << " )" << std::endl;
	try {
		f_testpp();
	} catch (...) {
		std::cerr << "catch...";
	}
}

void testpp_runner::run_all()
{
	// std::cerr << "run_all( " << runners().size() << " )\n";
	std::list< testpp_runner * >::iterator it;
	int i( 0 );
	for ( it=runners().begin(); it!=runners().end(); ++it ) {
		// std::cerr << "run( " << i++ << " )" << std::endl;
		(*it)->run();
	}
}


std::list< testpp_runner * > & testpp_runner::runners()
{
	static std::list< testpp_runner * > static_runners;
	return static_runners;
}


int main( int argc, char **argv )
{
	testpp_runner::run_all();
	return 0;
}

