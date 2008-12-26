#include "client_message.h"
#include "request.h"
#include "response.h"
#include <testpp/test.h>


TESTPP( client_message_constructor )
{
	request_c req( "get dog" );
	client_message_c msg( req );

	assertpp( msg.has_response() ).f();
}

