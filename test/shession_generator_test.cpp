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
#include "shession_generator.h"


/**
 */
TESTPP( test_4_sessions )
{
	shession_generator_c concrete_gen;
	shession_generator_i &gen( concrete_gen );

	std::string dog( gen.shession_id( "dog" ) );
	std::string cat( gen.shession_id( "cat" ) );
	std::string mouse( gen.shession_id( "mouse" ) );

	assertpp( dog ) == "dog1804289383";
	assertpp( cat ) == "cat846930886";
	assertpp( mouse ) == "mouse1681692777";
}

