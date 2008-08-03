#include <stdio.h>
#include <iostream>
#include "shession_control.h"


int main( int argc, char **argv )
{
	shession_control_c control;
	control.execute( 9000 );
	return 0;
}

