#include "testpp.h"


/*
bool test_simple();
bool test_simple_result = test_simple();
bool test_simple()
*/
TESTPP( test_simple )
{
	int value( 5 );
	5 == actual( value );
	4 == actual( value );
}


int main( int argc, char **argv )
{
	return 0;
}

