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

#include "snapl/arg.h"
#include "snapl/message_arg.h"
#include <sstream>

#include <iostream>


arg_list_c::arg_list_c()
{
}

arg_list_c::~arg_list_c()
{
	std::list< arg_i * >::iterator it( m_arg.begin() );
	for ( ; it!=m_arg.end(); ++it ) {
		delete *it;
	}
	m_arg.clear();
}

bool arg_list_c::operator = ( const message_arg_list_c &args )
{
	if ( m_arg.size() != args.argc() ) {
		return false;
	}

	std::list< arg_i * >::iterator it( m_arg.begin() );
	message_arg_list_c::iterator msg_it( args.begin() );
	for ( ; it!=m_arg.end(); ++it ) {
		if ( ! ( **it << msg_it->get() ) ) {
			return false;
		}
		++msg_it;
	}
	return true;
}

