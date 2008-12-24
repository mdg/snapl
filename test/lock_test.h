#ifndef LOCK_TEST_H
#define LOCK_TEST_H
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

#include "lock.h"


/**
 * A single threaded lock class for testing locking code.
 */
class mock_mutex_c
: public mutex_i
{
public:
	mock_mutex_c();

	bool lock();
	bool trylock();
	bool unlock();

	bool locked() { return m_locked; }

private:
	bool m_locked;
};


#endif

