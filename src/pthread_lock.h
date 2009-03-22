#ifndef PTHREAD_LOCK_H
#define PTHREAD_LOCK_H
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
#include <pthread.h>
#include <memory>

namespace snapl {


/**
 * pthread based lock.
 */
class pthread_mutex_c
: public mutex_i
{
public:
	pthread_mutex_c();
	virtual ~pthread_mutex_c();
	static void init();

	/**
	 * Lock this lock.
	 */
	virtual bool lock();
	/**
	 * Unlock the lock.
	 */
	virtual bool unlock();

	/**
	 * Try to lock, but don't block if the lock isn't available.
	 */
	virtual bool trylock();

private:
	pthread_mutex_t m_mutex;
	pthread_mutexattr_t m_attr;
};


} // namespace

#endif

