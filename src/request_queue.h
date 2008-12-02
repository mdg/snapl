#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H
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

#include <queue>


class request_c;
class lock_i;

/**
 * Queue for managing requests.
 */
class request_queue_i
{
public:
	/**
	 * Virtual destructor that does nothing.
	 */
	virtual ~request_queue_i() {}

	/**
	 * Push a request to end of the queue.
	 * The request owns the pointer after it's passed in.
	 */
	virtual void push( request_c * ) = 0;
	/**
	 * Pop a request from the front of the queue.
	 * The caller owns the pointer after it's returned.
	 */
	virtual request_c * pop() = 0;
};


/**
 * Lockable queue for managing requests.
 */
class request_queue_c
: request_queue_i
{
public:
	request_queue_c();
	request_queue_c( lock_i & );
	virtual ~request_queue_c();

	/**
	 * Push a request to end of the queue.
	 * The request owns the pointer after it's passed in.
	 */
	virtual void push( request_c * );
	/**
	 * Pop a request from the front of the queue.
	 * The caller owns the pointer after it's returned.
	 */
	virtual request_c * pop();

private:
	/**
	 * Check if the lock exists.  If so, lock it.
	 */
	inline void lock();
	/**
	 * Check if the lock exists.  If so, unlock it.
	 */
	inline void unlock();

	std::queue< request_c * > m_requests;
	lock_i *m_lock;
};


#endif

