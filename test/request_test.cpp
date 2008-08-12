#include "testpp.h"
#include "request.h"
#include "request_type.h"


TESTPP( test_constructor_1 )
{
	request_c req( RT_SESSION_STATUS, "dog" );
	RT_SESSION_STATUS == actual( req.request_type() );
	std::string( "dog" ) == actual( req.session_id() );
}

TESTPP( test_constructor_2 )
{
	request_c req( RT_STORE_SESSION, "cat" );
	RT_STORE_SESSION == actual( req.request_type() );
	std::string( "cat" ) == actual( req.session_id() );
}

