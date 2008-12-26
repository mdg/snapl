#include "application_message.h"
#include "client_queue.h"

                   -> request ------ request -
                  /                            \
client <-> command                             service
                  \                            /
                    <-response ---- response <-

void test_client_usage()
{
	dog_message_c dog( "cat" );
	m_queue.push( dog );

	m_queue.wait_for_response( dog );
}

void test_server_usage()
{
	dog_command_c dog( "cat" );
	m_queue.push( dog );
	m_queue.wait( dog );
}

action
command
message
transmission
transfer
request

class get_request_c
: public request_c
{
public:
	get_request_c( const std::string &user_id
			, const std::string &session_id );

	void copy( copy_stream_i &s )
	{
		s.copy( m_user_id );
		s.ocopy( m_session_id );
	}

private:
	std::string m_user_id;
	std::string m_session_id;
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

class get_service_c
: public service_c< get_request_c, get_response_c >
{
public:
	void execute( const get_request_c &req, get_rsponse_c &resp )
	{
		resp.ok( m_code );
	}
};

class command_i
{
public:
	const request_i & command_request() const { return m_request; }
	response_i & command_response() { return m_response; }

protected:
	command_i( const request_i &req, response_i &resp )
	: m_request( req )
	, m_response( resp )
	{}

private:
	const request_i &m_command_request;
	response_i &m_command_response;
};

template < typename ReqT, typename RespT >
class command_c
{
public:
	const ReqT & request() const { return m_request; }
	RespT & response() const { return m_response; }

protected:
	command_c()
	: command_i( m_request, m_response )
	, m_request()
	, m_response()
	{}

	command_c( const Reqt &req )
	: command_i( m_request, m_response )
	, m_request( req )
	, m_response()
	{}

	ReqT m_request;
	RespT m_response;
};

class get_command_c
: public command_c< get_request_c, get_response_c >
{
public:
	get_command_c( const std::string &user_id
			, const std::string &session_id )
	: command_c( get_request_c( user_id, session_id ) )
	{}
};

