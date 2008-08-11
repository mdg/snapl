#ifndef TESTPP_H
#define TESTPP_H

#include <iostream>


#define TESTPP( test_func ) \
void test_func(); \
int test_func##_result = testpp_wrapper( test_func, #test_func ); \
void test_func()

int testpp_wrapper( void (*func)(), const char *test_name )
{
	std::cout << "testpp( " << test_name << " )\n";
	func();
	return 0;
}

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

	void operator == ( const T& actual )
	{
		if ( m_expected == actual )
			return;

		print_file_line();
		std::cout << "expected<" << m_expected;
		std::cout << "> == actual<" << actual << ">\n";
	}

	bool operator != ( const T& actual );
	bool operator < ( const T& actual );
	bool operator > ( const T& actual );
	bool operator <= ( const T& actual );
	bool operator >= ( const T& actual );
	void between( const T& lesser, const T& greater );
	void within( const T& value, const T& delta );

private:
	void print_file_line()
	{
		std::cout << "\tfailure@ " << m_file << ":" << m_line << " -- ";
	}

	const T& m_expected;
	const char *m_file;
	int m_line;
	std::string m_message;
};

template < typename T >
expectation< T > create_expectation( const T& expected_val, const char *file, int line )
{
	return expectation< T >( expected_val, file, line );
}

#define expect( val ) create_expectation( val, __FILE__, __LINE__ )

// sample usage
#if 0
TESTPP( constructor_1 )
{
	int value( 10 );
	std::string text( "dog" );
	expect( 5 ) == value;
	expect( "cat" ) != text;
	expect( 5 ).within( 5, 1 );
}
#endif


#endif

