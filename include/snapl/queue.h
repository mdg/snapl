#ifndef SNAPL_QUEUE_H
#define SNAPL_QUEUE_H
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
#include <queue>
#include <memory>


/**
 * A server message queue.
 */
template < typename T >
class queue_front_i
{
public:
	virtual ~queue_front_i() {}

	/**
	 * Pop an object off the front of the queue.
	 */
	virtual T * pop() = 0;

	/**
	 * Check if this queue is empty.
	 */
	virtual bool empty() const = 0;
};


/**
 * A server message queue.
 */
template < typename T >
class queue_back_i
{
public:
	virtual ~queue_back_i() {}

	/**
	 * Push an object onto the back of the queue.
	 */
	virtual void push_inbound( T * ) = 0;
};


/**
 * Lockable queue for managing objects.
 * Deletes objects if the queue still owns them when it's deleted.
 */
template < typename T >
class queue_c
: public queue_front_i< T >
, public queue_back_i< T >
{
public:
	/**
	 * Construct a queue with no locking.
	 */
	queue_c()
	: m_queue()
	, m_mutex()
	{}

	/**
	 * Request queue that takes a mutex as a parameter for being
	 * threadsafe.  This is optional if queue won't run in threaded
	 * environment.  The request queue will own this mutex and destroy
	 * the mutex when the queue is destroyed.
	 */
	queue_c( mutex_i *mutex );
	: m_queue()
	, m_mutex( mutex )
	{}

	/**
	 * Destroy the queue.  Deallocate all the values that are
	 * in the queue.
	 */
	virtual ~queue_c()
	{
		lock_c lock( m_mutex.get() );
		while ( ! m_queue.empty() ) {
			std::auto_ptr< T > ptr( m_queue.front() );
			m_queue.pop();
		}
	}

	/**
	 * Push an object onto end of the queue.
	 * The request owns the pointer after it's passed in.
	 */
	virtual void push( T *ptr );
	{
		lock_c lock( m_mutex.get() );
		m_queue.push( ptr );
		// lock is freed by destructor
	}

	/**
	 * Pop an object from the front of the queue.
	 * The caller owns the pointer after it's returned.
	 */
	virtual T * pop();
	{
		T *ptr = 0;
		lock_c lock( m_mutex.get() );
		if ( ! m_queue.empty() ) {
			ptr = m_queue.front();
			m_queue.pop();
		}
		// lock is freed by destructor
		return msg;
	}

	/**
	 * Check if the queue is empty.
	 */
	virtual bool empty() const
	{
		lock_c lock( m_mutex.get() );
		return m_queue.empty();
	}

private:
	std::queue< T * > m_queue;
	std::auto_ptr< mutex_i > m_mutex;
};


#endif

