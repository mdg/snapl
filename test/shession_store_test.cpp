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
#include "shession_store.h"


TESTPP( test_4_sessions )
{
	shession_store_c store( 1 );

	const char *sid_1 = "dog";
	const char *sid_2 = "cat";
	const char *sid_3 = "mouse";
	const char *sid_4 = "flea";

	store.create_session( sid_1 );
	store.create_session( sid_2 );
	store.create_session( sid_3 );
	store.create_session( sid_4 );

	true == actual( store.renew_session( sid_1 ) );
	true == actual( store.renew_session( sid_2 ) );
	true == actual( store.renew_session( sid_3 ) );
	true == actual( store.renew_session( sid_4 ) );

	store.kill_session( sid_1 );
	store.kill_session( sid_2 );
	store.kill_session( sid_3 );
	store.kill_session( sid_4 );

	false == actual( store.renew_session( sid_1 ) );
	false == actual( store.renew_session( sid_2 ) );
	false == actual( store.renew_session( sid_3 ) );
	false == actual( store.renew_session( sid_4 ) );
}

