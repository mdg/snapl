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
	get_request_c()
	: request_c( "get" )
	, m_user_id()
	, m_session_id()
	{
		m_args << m_user_id << m_session_id;
	}

	void set( const std::string &user_id
			, const std::string &session_id );


	/**
	 * Command constructor.
	 */
	get_request_c( const std::string &user_id
			, const std::string &session_id );
	: request_c( "get" )
	, m_user_id( user_id )
	, m_session_id( session_id )
	{
		m_args << m_user_id << m_session_id;
	}

	/**
	 * Service constructor.
	 */
	get_request_c( const message_c &msg )
	: request_c( "get" )
	, m_user_id( req.argv< int >( 0 ) )
	, m_session_id( req.argv< std::string >( 1 ) )
	{
		m_args << m_user_id << m_session_id;
	}

	/**
	 * Copy values of the request.
	 */
	template < typename T >
	void copy( T &stream )
	{
		stream + m_user_id + m_session_id;
		// alternative usage.  are | better?
		// stream | m_user_id | m_session_id;
	}

private:
	std::string m_user_id;
	std::string m_session_id;
};

class get_response_c
: public response_c
{
public:
	template < typename T >
	void copy( T &stream )
	{
		stream + m_code + m_response;
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


class get_command_c
: public command_c< get_request_c, get_response_c >
{
public:
	get_command_c( const std::string &user_id
			, const std::string &session_id )
	: command_c( get_request_c( user_id, session_id ) )
	{}
};

