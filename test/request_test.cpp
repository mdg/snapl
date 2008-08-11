#include "request_test.h"
#include <iostream>
#include "request.h"
#include "request_type.h"


class failure_info_c
{
public:
	failure_info_c( const char *file, int line ) {}
private:
	const char *m_file;
	int m_line;
};


class failure_c
{
public:
	failure_c() {}
	failure_c( const failure_c& ) {}
	failure_c( failure_info_c * ) {}
	failure_c & operator = ( failure_info_c * ) {}

	operator bool () const { return m_info; }
	bool operator ! () const { return ! m_info; }

	operator failure_info_c * () { return release(); }
	failure_info_c * release() { return 0; }

private:
	failure_info_c *m_info;
};


class test_result_c
{
public:
	test_result_c();
};


void request_test_c::test_constructor_1()
{
	request_c req( RT_SESSION_STATUS, "dog" );
	assert_equal( RT_SESSION_STATUS, req.request_type() );
	assert_equal( "dog", req.session_id() );
}

void request_test_c::test_constructor_2()
{
	failure_c f;
	request_c req( RT_STORE_SESSION, "cat" );

	if ( RT_STORE_SESSION != req.request_type() ) {
		f = new failure_info_c( __FILE__, __LINE__ );
	}
	if ( "cat" != req.session_id() ) {
		f = new failure_info_c( __FILE__, __LINE__ );
	}
}

#define BEGIN_TEST( t ) \
bool t() \
{

#define END_TEST }

void request_test_c::test_constructor_3()
{
	request_c req( RT_SESSION_STATUS, "dog" );
	ASSERT_EQUAL( RT_SESSION_STATUS, req.request_type() );
	ASSERT_EQUAL( "dog", req.session_id() );
}

void request_test_c::assert_equal( int expected, int actual )
{
	if ( expected != actual ) {
		std::cerr << "expected != actual\n";
	}
}

void request_test_c::assert_equal( const std::string &expected
		, const std::string &actual )
{
	if ( expected != actual ) {
		std::cerr << "expected != actual\n";
	}
}

