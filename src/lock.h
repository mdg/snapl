#ifndef LOCK_H
#define LOCK_H
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

namespace snapl {


/**
 * A mutex lock interface.
 */
class mutex_i
{
	friend class lock_c;
	friend class trylock_c;

public:
	virtual ~mutex_i() {}

private:
	/**
	 * Lock this lock.
	 */
	virtual bool lock() = 0;

	/**
	 * Unlock the lock.
	 */
	virtual bool unlock() = 0;

	/**
	 * Try to lock, but don't block if the lock isn't available.
	 */
	virtual bool trylock() = 0;

};


/**
 * A mutex lock.  This will block on construction until the lock can be
 * acquired.
 */
class lock_c
{
public:
	/**
	 * Construct the lock on the mutex.  This will block until the
	 * mutex can be locked.
	 */
	lock_c( mutex_i &mutex )
	: m_mutex( &mutex )
	{
		if ( m_mutex )
			m_mutex->lock();
	}
	/**
	 * Construct the lock on a mutex ptr.  This will block until the
	 * mutex can be locked.  It will tolerate a null pointer and do
	 * nothing.
	 */
	lock_c( mutex_i *mutex )
	: m_mutex( mutex )
	{
		if ( m_mutex )
			m_successful_try = m_mutex->lock();
	}

	/**
	 * Destructor to automatically unlock the mutex when the lock is
	 * destroyed.  Unlocking automatically is the reason for this
	 * class's existence.
	 */
	~lock_c()
	{
		unlock();
	}

	/**
	 * Unlock the mutex prior to destruction of this object.
	 */
	void unlock()
	{
		if ( m_mutex )
			m_mutex->unlock();
	}

	/**
	 * Check if the try successfully locked the mutex.
	 */
	bool successful_try() const { return m_successful_try; }

private:
	mutex_i *m_mutex;
	bool m_successful_try;
};

/**
 * A try lock.  This won't block if it can't get the lock.
 */
class trylock_c
{
public:
	/**
	 * Construct the trylock and attempt to lock the mutex.
	 * Set the successful try flag for calling code to check success.
	 */
	trylock_c( mutex_i &mutex )
	: m_mutex( &mutex )
	, m_successful_try( mutex.trylock() )
	{}
	/**
	 * Construct the trylock for a mutex pointer and attempt to lock
	 * it if the pointer is valid.  Don't do anything if the mutex pointer
	 * is null.
	 * Set the successful try flag for calling code to check success.
	 */
	trylock_c( mutex_i *mutex )
	: m_mutex( mutex )
	, m_successful_try( mutex ? mutex->trylock() : false )
	{}

	/**
	 * Destructor that automatically unlocks the mutex when it is
	 * destroyed.  Unlocking automatically is reason for this class's
	 * existence.
	 */
	~trylock_c()
	{
		unlock();
	}

	/**
	 * Unlock the mutex prior to going out of scope.
	 */
	void unlock()
	{
		m_mutex->unlock();
	}

	/**
	 * Check if the try successfully locked the mutex.
	 */
	bool successful_try() const { return m_successful_try; }

private:
	mutex_i *m_mutex;
	const bool m_successful_try;
};


} // namespace

#endif

