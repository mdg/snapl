#ifndef COMMAND_TEST_H
#define COMMAND_TEST_H

#include "command.h"
#include "request_test.h"
#include "response_test.h"


class mock_command_c
: public command_c< mock_request_c, mock_response_c >
{
public:
	mock_command_c( const std::string &id, int number )
	: command_c< mock_request_c, mock_response_c >(
			mock_request_c( id, number ) )
	{}
};


#endif

