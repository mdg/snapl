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

#include "snapl/protocol.h"
#include <testpp/test.h>

using namespace snapl;


/**
 * Test that the protocol constructor works as expected.
 */
TESTPP( test_protocol_constructor )
{
	protocol_c p( 5 );

	assertpp( p.port() ) == 5;
	assertpp( p.silent() ) == false;
}

