#include "client_message.h"
#include "request.h"
#include "response.h"
#include <testpp/test.h>


TESTPP( client_message_constructor )
{
	client_message_c< request_c, response_c > msg;

	assertpp( msg.has_response() ).f();

	msg.set_response();

	assertpp( msg.has_response() ).t();
}

