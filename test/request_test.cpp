#include "request_test.h"
#include <iostream>
#include "request.h"
#include "request_type.h"


void request_test_c::test_constructor_1()
{
	request_c req( RT_SESSION_STATUS, "dog" );
	assert_equal( RT_SESSION_STATUS, req.request_type() );
	assert_equal( "dog", req.session_id() );
}

void request_test_c::test_constructor_2()
{
	request_c req( RT_STORE_SESSION, "cat" );
	assert_equal( RT_STORE_SESSION, req.request_type() );
	assert_equal( "cat", req.session_id() );
}

