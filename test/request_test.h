#ifndef REQUEST_TEST_H
#define REQUEST_TEST_H

#include <string>

#define DEFINE_TEST( t ) bool t()

class request_test_c
{
public:
	void test_constructor_1();
	void test_constructor_2();
	DEFINE_TEST( test_constructor_3 );

	void assert_equal( int expected, int actual );

	void assert_equal( const std::string &expected
			, const std::string &actual );
};


#endif

