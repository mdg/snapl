#ifndef REQUEST_TEST_H
#define REQUEST_TEST_H

#include <string>


class request_test_c
{
public:
	void test_constructor_1();

	void assert_equal( int expected, int actual );

	void assert_equal( const std::string &expected
			, const std::string &actual );
};


#endif

