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


pthread_lock_c::pthread_lock_c()
{
	pthread_mutex_init( &m_mutex, &m_mutex_attr );
}

pthread_lock_c::~pthread_lock_c()
{
	pthread_mutex_destroy( &m_mutex );
}


void pthread_lock_c::lock()
{
	pthread_mutex_lock( &m_mutex );
}

void pthread_lock_c::unlock()
{
	pthread_mutex_unlock( &m_mutex );
}

void pthread_lock_c::trylock()
{
	pthread_mutex_trylock( &m_mutex );
}

