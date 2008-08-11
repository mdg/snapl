#ifndef TESTPP_H
#define TESTPP_H

#define TESTPP( test_func ) \
void test_func(); \
test_func(); \
void test_func( assertpp& assert )


class suitepp
{
protected:
	void assert( bool assertion );

	template < typename T >
	void assert_equal( const T&, const T& );
};

// sample usage

DEFINE_SUITEPP( request_test )
	DEFINE_TESTPP( test_constructor_1 )
		ASSERT( 1 == 4 );
	END_TESTPP
END_SUITEPP;

template < typename T >
class expectation
{
public:
	expectation( const T& expected_val )
	: m_expected( expected_val )
	, m_file( NULL )
	, m_line( 0 )
	{}

	expectation( const T& expected_val, const char *file, int line )
	: m_expected( expected_val )
	, m_file( file )
	, m_line( line )
	{}

	bool operator == ( const T& actual );
	bool operator != ( const T& actual );
	bool operator < ( const T& actual );
	bool operator > ( const T& actual );
	bool operator <= ( const T& actual );
	bool operator >= ( const T& actual );

private:
	const T& m_expected;
};

TESTPP( constructor_1 )
{
	int value( 10 );
	std::string text( "dog" );
	expect( 5 ) == value;
	expect( "cat" ) != text;
}


#endif

