#ifndef RESPONSE_TEST_H
#define RESPONSE_TEST_H

#include "snapl/response.h"

namespace snapl {


class mock_response_c
: public response_c
{
public:
	mock_response_c()
	: response_c()
	{}
};


} // namespace

#endif

