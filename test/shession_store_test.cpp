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
 * Test that the shession_constructor sets members to the proper default
 * values.
 */
TESTPP( test_shession_constructor )
{
	shession_c sh( "dog" );

	assertpp( sh.shession_id() ) == "dog";
	assertpp( sh.user_id() ) == "";
	assertpp( sh.expiration() ) == 0;
	assertpp( sh.expired( 5 ) ).t();
}

/**
 * Test that the constructor with the user ID works as expected.
 */
TESTPP( test_shession_user_id_constructor )
{
	shession_c sh( "dog", "cat" );

	assertpp( sh.shession_id() ) == "dog";
	assertpp( sh.user_id() ) == "cat";
	assertpp( sh.expiration() ) == 0;
	assertpp( sh.expired( 4 ) ).t();
}

/**
 * Test that the expiration functionality works.
 */
TESTPP( test_shession_expiration )
{
	shession_c sh( "dog" );

	sh.expire_at( 5 );
	assertpp( sh.expired( 4 ) ).f();
	assertpp( sh.expired( 5 ) ).t(); // should expire at the given time
	assertpp( sh.expired( 6 ) ).t();
}


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
TESTPP( test_storing_4_sessions )
{
	shession_store_c store( 1 );

	const char *sid_1 = "dog";
	const char *sid_2 = "cat";
	const char *sid_3 = "mouse";
	const char *sid_4 = "flea";
	std::string empty;

	store.create_session( sid_1, empty );
	store.create_session( sid_2, empty );
	store.create_session( sid_3, empty );
	store.create_session( sid_4, empty );

	assertpp( store.renew( sid_1 ) ).t();
	assertpp( store.renew( sid_2 ) ).t();
	assertpp( store.renew( sid_3 ) ).t();
	assertpp( store.renew( sid_4 ) ).t();

	store.kill_session( sid_1 );
	store.kill_session( sid_2 );
	store.kill_session( sid_3 );
	store.kill_session( sid_4 );

	assertpp( store.renew( sid_1 ) ).f();
	assertpp( store.renew( sid_2 ) ).f();
	assertpp( store.renew( sid_3 ) ).f();
	assertpp( store.renew( sid_4 ) ).f();
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
	std::string user_id;

	store.create_session( sid_1, user_id );
	store.create_session( sid_2, user_id );
	store.create_session( sid_3, user_id );
	store.create_session( sid_4, user_id );

	mock_timer += 3;
	assertpp( store.renew( sid_4 ) ).t();

	mock_timer += 4;
	assertpp( store.renew( sid_4 ) ).t();
	assertpp( store.size() ) == 4;
	assertpp( store.renew( sid_1 ) ).f();
	assertpp( store.size() ) == 3;
	assertpp( store.kill_expired() ) == 2;
	assertpp( store.size() ) == 1;

	mock_timer += 4;
	assertpp( store.renew( sid_4 ) ).t();
}

/**
 * Test that mirroring works correctly for creation.
 */
TESTPP( test_store_mirror_creation )
{
	shession_store_c store( 60 );

	store.mirror( "dog", "cat" );

	assertpp( store.live( "dog" ) ).t();
}

/**
 * Test that mirroring works correctly for renewal.
 */
TESTPP( test_store_mirror_renewal )
{
	shession_store_c store( 5 );
	mock_timer_c mock_timer;
	store.set_timer( mock_timer );

	store.mirror( "dog", "cat" );
	mock_timer += 3;
	store.mirror( "dog", "cat" );
	mock_timer += 4;

	assertpp( store.live( "dog" ) ).t();
}

