#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "request_type.h"


class request_c
{
public:
	request_c( const std::string & )
	{}

	request_c( request_type_e )
	{}

private:
	request_type_e m_request_type;
};


#endif

