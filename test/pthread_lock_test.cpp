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

#include "pthread_lock.h"
#include <testpp/test.h>


/**
 * Test basic functionality of the lock.
 */
TESTPP( test_pthread_lock )
{
	pthread_mutex_c mutex;
	lock_c lock( mutex );
	assertpp( lock.successful_try() ).t();
	lock.unlock();
}

/**
 * Test that lock destructor actually unlocks.
 * This should be a lock test, not a pthread_mutex test.
 */
TESTPP( test_lock_destructor )
{
	failpp( "not implemented." );
}

/**
 * Test that manually unlocking allows it to be relocked.
 */
TESTPP( test_pthread_relock )
{
	pthread_mutex_c mutex;
	lock_c lock( mutex );
	assertpp( lock.successful_try() ).t();
	lock.unlock();

	lock_c lock2( mutex );
	assertpp( lock2.successful_try() ).t();
}

/**
 * Test that manually unlocking allows it to be relocked.
 */
TESTPP( test_pthread_failed_trylock )
{
	pthread_mutex_c mutex;
	lock_c lock( mutex );
	assertpp( lock.successful_try() ).t();

	trylock_c lock2( mutex );
	assertpp( lock2.successful_try() ).f();

	lock.unlock();
}

