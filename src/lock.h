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


/**
 * Locking object interface.
 */
class lock_i
{
public:
	virtual ~lock_i() {}

	/**
	 * Lock this lock.
	 */
	virtual void lock() = 0;

	/**
	 * Unlock the lock.
	 */
	virtual void unlock() = 0;

	/**
	 * Try to lock, but don't block if the lock isn't available.
	 */
	virtual void trylock() = 0;

};


#endif

