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

#include "usage.h"


usage_option_c::usage_option_c( bool param_expected, char short_option
		, const std::string &long_option
		, const std::string &description )
: m_param_expected( param_expected )
, m_short_opt( short_option )
, m_long_opt( long_option )
, m_description( description )
, m_usage_error( false )
, m_set( false )
, m_param()
{}

void usage_option_c::set()
{
	if ( param_expected() ) {
		m_usage_error = true;
		return;
	}
	m_set = true;
}

void usage_option_c::set( const std::string &param )
{
	if ( ! param_expected() ) {
		m_usage_error = true;
		return;
	}
	m_set = true;
	m_param = param;
}

std::string usage_option_c::usage_doc() const
{
}



void usage_c::add( usage_option_c &option )
{
	m_option.push_back( &option );
}

bool usage_c::parse_args( int argc, char **argv )
{
	bool usage_error( false );
	for ( int i(0); i<argc; ++i ) {
		// usage_error = usage_error || 
	}

	return true;
}

std::string usage_c::usage_doc() const
{
}

