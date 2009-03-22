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

using namespace snapl;


pthread_once_t pthread_mutex_once = PTHREAD_ONCE_INIT;


pthread_mutex_c::pthread_mutex_c()
{
	pthread_mutexattr_init( &m_attr );
	pthread_mutex_init( &m_mutex, &m_attr );
}

pthread_mutex_c::~pthread_mutex_c()
{
	pthread_mutex_destroy( &m_mutex );
	pthread_mutexattr_destroy( &m_attr );
}

void pthread_mutex_c::init()
{
	// pthread_init();
}


bool pthread_mutex_c::lock()
{
	return pthread_mutex_lock( &m_mutex ) == 0;
}

bool pthread_mutex_c::unlock()
{
	return pthread_mutex_unlock( &m_mutex ) == 0;
}

bool pthread_mutex_c::trylock()
{
	return pthread_mutex_trylock( &m_mutex ) == 0;
}

