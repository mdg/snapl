#include "application_message.h"
#include "client_queue.h"


void test_client_usage()
{
	dog_message_c dog( "cat" );
	m_queue.push( dog );

	m_queue.wait_for_response( dog );
}

void test_server_usage()
{
	dog_action_c dog( "cat" );
	m_queue.push( dog );
	m_queue.wait( dog );
}

action
message
transmission
transfer
request

