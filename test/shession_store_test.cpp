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


/**
 * A mock timer class for injecting into the shession_store
 * for testing expiration.
 */
class mock_timer_c
: public shession_store_c::timer_c
{
public:
	/**
	 * Construct the timer, starting at 0
	 */
	mock_timer_c()
	: m_seconds( 0 )
	{}
	/**
	 * Return the constant number of seconds.
	 */
	virtual time_t operator () () const
	{
		return m_seconds;
	}
	/**
	 * Add time to this timer.
	 */
	virtual void operator += ( time_t seconds )
	{
		m_seconds += seconds;
	}

private:
	time_t m_seconds;
};


/**
 * Test 4 basic sessions to make sure they can be added and killed
 * and things work as expected.
 */
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

/**
 * Test that expiration works as expected.
 */
TESTPP( test_expiration )
{
	shession_store_c store( 5 );
	mock_timer_c mock_timer;
	store.set_timer( mock_timer );

	const char *sid_1 = "dog";
	const char *sid_2 = "cat";
	const char *sid_3 = "mouse";
	const char *sid_4 = "flea";

	store.create_session( sid_1 );
	store.create_session( sid_2 );
	store.create_session( sid_3 );
	store.create_session( sid_4 );

	mock_timer += 3;
	true == actual( store.renew_session( sid_4 ) );

	mock_timer += 4;
	true == actual( store.renew_session( sid_4 ) );
	4 == actual( store.size() );
	false == actual( store.renew_session( sid_1 ) );
	3 == actual( store.size() );
	2 == actual( store.kill_expired() );
	1 == actual( store.size() );

	mock_timer += 4;
	true == actual( store.renew_session( sid_4 ) );
}

