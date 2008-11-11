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
#include <iostream>
#include <sstream>
#include <cstring>


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

void usage_option_c::write_usage_doc( std::ostream &doc ) const
{
	if ( m_short_opt ) {
		doc << "\t-" << m_short_opt;
	}

	if ( ! m_long_opt.empty() ) {
		doc << "\t--" << m_long_opt;
	}

	if ( ! m_description.empty() ) {
		doc << "\t" << m_description;
	}

	doc << std::endl;
}



void usage_c::add( usage_option_c &option )
{
	m_option.push_back( &option );
}

bool usage_c::parse_args( int argc, const char **argv )
{
	bool usage_error( false );
	// skip the first arg which is the command
	for ( int i(1); i<argc; ++i ) {
		// usage_error = usage_error || 
		// std::cerr << "argv[" << i << "] = " << argv[i] << std::endl;

		if ( strlen( argv[i] ) < 2 ) {
			// no options should be less than 2 in length
			return false;
		}

		usage_option_c *option;
		if ( argv[i][0] == '-' && argv[i][1] == '-' ) {
			// long option
			option = find_long_option( argv[i] + 2 );
			if ( ! option ) {
				// this option is not found
				return false;
			}
			option->set();
		} else if ( argv[i][0] == '-' ) {
			// short option
			option = find_short_option( argv[i][1] );
			if ( ! option ) {
				// this option is not found
				return false;
			}
			option->set();
		} else {
			// parameter
			// not yet supported.  ignore for now.
		}
		std::list< usage_option_c * >::iterator it;
		for ( it=m_option.begin(); it!=m_option.end(); ++it ) { 
		}
	}

	return true;
}

void usage_c::write_usage_doc( std::ostream &doc ) const
{
	doc << "Usage: shessiond [OPTIONS]\n\n";
	doc << "Options:\n";
	usage_option_c::list::const_iterator it;
	for ( it=m_option.begin(); it!=m_option.end(); ++it ) {
		(*it)->write_usage_doc( doc );
	}
	doc << "\n";
}

usage_option_c * usage_c::find_short_option( char short_opt )
{
	usage_option_c::list::iterator it;
	for ( it=m_option.begin(); it!=m_option.end(); ++it ) {
		usage_option_c &opt( **it );
		if ( opt.short_opt() == short_opt ) {
			return &opt;
		}
	}
	return NULL;
}

usage_option_c * usage_c::find_long_option( const std::string &long_opt )
{
	usage_option_c::list::iterator it;
	for ( it=m_option.begin(); it!=m_option.end(); ++it ) {
		usage_option_c &opt( **it );
		if ( opt.long_opt() == long_opt ) {
			return &opt;
		}
	}
	return NULL;
}

