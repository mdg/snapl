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

	const T& value() const { return m_expected; }

	void operator == ( const T& actual )
	{
		if ( m_expected == actual )
			return;

		print_file_line();
		std::cout << "expected<" << m_expected;
		std::cout << "> == actual<" << actual << ">\n";
	}
	void within( const T& value, const T& delta );

	/*
	friend void operator == ( const expectation< T >&, const actual< T >& );
	friend void operator != ( const expectation< T >&, const actual< T >& );
	friend void operator < ( const expectation< T >&, const actual< T >& );
	friend void operator > ( const expectation< T >&, const actual< T >& );
	friend void operator <= ( const expectation< T >&, const actual< T >& );
	friend void operator >= ( const expectation< T >&, const actual< T >& );
	*/

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

template < typename T >
class actual_value
{
public:
	actual_value( const T& actual_val )
	: m_actual( actual_val )
	, m_file( NULL )
	, m_line( 0 )
	{}

	actual_value( const T& actual_val, const char *file, int line )
	: m_actual( actual_val )
	, m_file( file )
	, m_line( line )
	{}

	// const T& value() const { return m_actual; }
	template < typename T2 >
	friend void operator == ( const T2&, const actual_value< T2 >& );
	template < typename T2 >
	friend void operator != ( const T2&, const actual_value< T2 >& );
	/*
	template < typename T2 >
	friend void operator < ( const expectation< T2 >&, const actual< T2 >& );
	template < typename T2 >
	friend void operator > ( const expectation< T2 >&, const actual< T2 >& );
	template < typename T2 >
	friend void operator <= ( const expectation< T2 >&, const actual< T2 >& );
	template < typename T2 >
	friend void operator >= ( const expectation< T2 >&, const actual< T2 >& );
	*/
	void within( const T& value, const T& delta );

private:
	void print_error_prefix() const
	{
		std::cout << "\tfailure@ " << m_file << ":" << m_line << " -- ";
	}

	const T& m_actual;
	const char *m_file;
	int m_line;
	std::string m_message;
};


template < typename T >
void operator == ( const T& expected, const actual_value< T > &act )
{
	if ( expected == act.m_actual )
		return;

	act.print_error_prefix();
	std::cout << "expected<" << expected;
	std::cout << "> == actual<" << act.m_actual << ">\n";
}

template < typename T >
void operator != ( const T& expected, const actual_value< T > &act )
{
	if ( expected != act.m_actual )
		return;

	act.print_error_prefix();
	std::cout << "expected<" << expected;
	std::cout << "> != actual<" << act.m_actual << ">\n";
}

template < typename T >
actual_value< T > create_actual( const T& actual_val, const char *file, int line )
{
	return actual_value< T >( actual_val, file, line );
}

#define actual( val ) create_actual( val, __FILE__, __LINE__ )


// sample usage
#if 0
TESTPP( constructor_1 )
{
	int value( 10 );
	std::string text( "dog" );
	5 == actual( value ) ( "what about this?" );
	actual( value ).between( 1, 5 );
	actual( 3 ).within( 5, 1 );
	5 == actual( value );
	"cat" == actual( text );
}
#endif


#endif

