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

class get_request_c
: public request_c
{
public:
	void copy( copy_stream_i &s )
	{
		s.copy( m_user_id );
		s.ocopy( m_session_id );
	}
};

class get_response_c
: public response_c
{
public:
	void copy( copy_stream_i &s )
	{
		s.copy( m_code );
		s.copy( m_response );
	}
};

class service_i
{
	virtual void execute() = 0;
};

template < typename ReqT, typename Respt >
class service_c
{
public:
	virtual void execute()
	{
		execute( m_request, m_response );
	}
};

class get_service_c
: service_c< get_request_c, get_response_c >
{
public:
	void execute( const get_request_c &req, get_rsponse_c &resp )
	{
		resp.ok( m_code );
	}
};

template < get_request_c, get_response_c >
class get_command_c
{
public:
	get_command_c( const std::string &user_id
			, const std::string &session_id );
};

