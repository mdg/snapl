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


std::list< testpp_runner * > *testpp_runner::s_runners = 0;


testpp_runner::testpp_runner( testpp_func f, const char *test_name
	       , const char *file_name, int line_number )
: f_testpp( f )
{
	static int i( 0 );
	if ( ! s_runners ) {
		std::cerr << "initialize s_runners\n";
		s_runners = new std::list< testpp_runner * >;
	}
	std::cerr << "s_runners->push_back( " << i++ << " )"
		<< " = " << s_runners->size() << std::endl;
	s_runners->push_back( this );
}

testpp_runner::~testpp_runner()
{
	std::list< testpp_runner * >::iterator it;
	it = std::find( s_runners->begin(), s_runners->end(), this );
	if ( it == s_runners->end() ) {
		s_runners->erase( it );
	}
}

void testpp_runner::run()
{
	std::cerr << "testpp( " << m_file_name << ':' << m_test_name;
	std::cerr << ':' << m_line_number << " )\n";
	f_testpp();
}

void testpp_runner::run_all()
{
	std::cerr << "run_all( " << s_runners->size() << " )\n";
	std::list< testpp_runner * >::iterator it;
	int i( 0 );
	for ( it=s_runners->begin(); it!=s_runners->end(); ++it ) {
		std::cerr << "run( " << i++ << " )" << std::endl;
		(*it)->run();
	}
}


int main( int argc, char **argv )
{
	std::cerr << "wtf is this?\n";
	testpp_runner::run_all();
	return 0;
}

