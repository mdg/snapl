#ifndef REQUEST_TEST_H
#define REQUEST_TEST_H

#include "request.h"
#include "request_type.h"


class request_test_c
{
public:
	void test_constructor_1()
	{
		request_c req( RT_SESSION_STATUS, "dog" );
		assert_equal( RT_SESSION_STATUS, req.request_type() );
		assert_equal( "dog", req.session_id() );
	}

	void assert_equal( int expected, int actual )
	{
		if ( expected != actual ) {
			std::cerr << "expected != actual\n" );
		}
	}

	void assert_equal( const std::string &expected
			, const std::string &actual )
	{
		if ( expected != actual ) {
			std::cerr << "expected != actual\n" );
		}
	}
};


#endif

