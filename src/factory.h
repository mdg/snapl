#ifndef FACTORY_H
#define FACTORY_H
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


template < typename I >
class factory_i
{
public:
	/**
	 * Empty virtual constructor so subclasses will have things deleted.
	 */
	virtual ~factory_i() {}

	/**
	 * Pure virtual for creating objects of the given interface type.
	 */
	virtual I * create() const = 0;
};


template < typename C, typename I >
class factory_c
: public factory_i< I >
{
public:
	virtual ~factory_c() {}

	virtual I * create() const
	{
		return new C();
	}
};


} // namespace

#endif

