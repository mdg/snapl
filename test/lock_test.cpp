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

#include "lock_test.h"
#include <testpp/test.h>


mock_mutex_c::mock_mutex_c()
: m_locked( false )
{}

bool mock_mutex_c::lock()
{
	if ( m_locked )
		return false;
	m_locked = true;
	return true;
}

bool mock_mutex_c::trylock()
{
	if ( m_locked )
		return false;
	m_locked = true;
	return true;
}

bool mock_mutex_c::unlock()
{
	if ( ! m_locked )
		return false;
	m_locked = false;
	return true;
}


/**
 * Test basic functionality of the lock.
 */
TESTPP( test_lock_constructor )
{
	mock_mutex_c mutex;
	assertpp( mutex.locked() ).f();
	lock_c lock( mutex );
	assertpp( lock.successful_try() ).t();
	assertpp( mutex.locked() ).t();
	lock.unlock();
	assertpp( mutex.locked() ).f();
}

/**
 * Test that lock destructor actually unlocks.
 * This should be a lock test, not a pthread_mutex test.
 */
TESTPP( test_lock_destructor )
{
	mock_mutex_c mutex;
	int i( 5 );
	if ( i == 5 ) {
		lock_c lock( mutex );
		assertpp( lock.successful_try() ).t();
		assertpp( mutex.locked() ).t();
	}
	assertpp( mutex.locked() ).f();
}

/**
 * Test that manually unlocking allows it to be relocked.
 */
TESTPP( test_trylock_constructor )
{
	failpp( "not implemented." );
	mock_mutex_c mutex;
	lock_c lock( mutex );
	assertpp( lock.successful_try() ).t();
	lock.unlock();

	lock_c lock2( mutex );
	assertpp( lock2.successful_try() ).t();
}

/**
 * Test that manually unlocking allows it to be relocked.
 */
TESTPP( test_trylock_destructor )
{
	failpp( "not implemented." );
	mock_mutex_c mutex;
	lock_c lock( mutex );
	assertpp( lock.successful_try() ).t();

	trylock_c lock2( mutex );
	assertpp( lock2.successful_try() ).f();

	lock.unlock();
}

