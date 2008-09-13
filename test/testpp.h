#ifndef TESTPP_H
#define TESTPP_H
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


#include <iostream>
#include <list>


/**
 * Create a testpp test function.
 */
#define TESTPP( test_func ) \
static void test_func(); \
static testpp_runner test_func##_runner( test_func, #test_func \
		, __FILE__, __LINE__ ); \
void test_func()



/**
 * The function to be run by the TESTPP macro
 */
typedef void (*testpp_func)();

/**
 * A class that takes a parameter as a testpp_func
 * and stores it to run later.
 */
class testpp_runner
{
public:
	testpp_runner( testpp_func, const char *test_name
		, const char *file_name, int line_number );
	~testpp_runner();

	/**
	 * Run the test.
	 */
	void run();

	static void run_all();

private:
	std::string m_test_name;
	const char *m_file_name;
	int m_line_number;
	testpp_func f_testpp;

	static std::list< testpp_runner * > *s_runners;
};


/**
 * Actual value class for giving sample syntax described below.
 */
template < typename T >
class actual_value
{
public:
	/**
	 * Construct an actual value without file and line.
	 * Don't do this in real tests.  Use the actual macro
	 * instead.
	 */
	actual_value( const T& actual_val )
	: m_actual( actual_val )
	, m_file( NULL )
	, m_line( 0 )
	{}

	/**
	 * Construct an actual value at a given file and line.
	 * Don't call this directly.  Use the actual macro
	 * instead.
	 */
	actual_value( const T& actual_val, const char *file, int line )
	: m_actual( actual_val )
	, m_file( file )
	, m_line( line )
	{}

	// const T& value() const { return m_actual; }
	template < typename T2 >
	friend void operator == ( const T2 &, const actual_value< T2 > & );
	template < typename T2 >
	friend void operator != ( const T2 &, const actual_value< T2 > & );
	/*
	template < typename T2 >
	friend void operator < ( const T2 &, const actual< T2 > & );
	template < typename T2 >
	friend void operator > ( const T2 &, const actual< T2 > & );
	template < typename T2 >
	friend void operator <= ( const T2 &, const actual< T2 > & );
	template < typename T2 >
	friend void operator >= ( const T2 &, const actual< T2 > & );
	*/
	void between( const T &val1, const T &val2 );
	void within( const T &value, const T &delta );

private:
	/**
	 * print the error prefix for a line when a comparison fails.
	 */
	void print_failure_prefix() const
	{
		std::cout << "\tfailure@ " << m_file << ":" << m_line << " -- ";
	}

	const T &m_actual;
	const char *m_file;
	int m_line;
	std::string m_message;
};

/**
 * Check if an expected value is
 * equal to an actual value.
 */
template < typename T >
void operator == ( const T& expected, const actual_value< T > &act )
{
	if ( expected == act.m_actual )
		return;

	act.print_failure_prefix();
	std::cout << "expected<" << expected;
	std::cout << "> == actual<" << act.m_actual << ">\n";
}

/**
 * Check if an expected value is
 * not equal to an actual value.
 */
template < typename T >
void operator != ( const T& expected, const actual_value< T > &act )
{
	if ( expected != act.m_actual )
		return;

	act.print_failure_prefix();
	std::cout << "expected<" << expected;
	std::cout << "> != actual<" << act.m_actual << ">\n";
}


/**
 * Helper function to let the actual macro create an actual_value
 * without having to specify the typename in the constructor.
 * This is not meant to be called directly.  Use the actual macro.
 */
template < typename T >
actual_value< T > create_actual( const T& actual_val, const char *file, int line )
{
	return actual_value< T >( actual_val, file, line );
}


/**
 * The basic way to create an actual_value with the given file
 * and line.  This should be used instead of the create_actual
 * function or the actual_value constructor.
 */
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

