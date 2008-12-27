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


/**
 * Object that exports general values from a message class into a typed
 * object.
 */
class message_export_c
{
public:
	message_export_c( const message_c &msg )
	: m_message( msg )
	, m_arg( 0 )
	, m_error( false )
	{}

	template < typename T >
	message_export_c & operator + ( T &value )
	{
		// check that too many values haven't already been read
		if ( m_arg >= m_message.argc() ) {
			m_error = true;
			return *this;
		}

		copy( value, m_message.argv[ m_arg++ ] );
		return *this;
	}

	/**
	 * Copy a string value to a typed value.
	 */
	template < typename T >
	void copy( T &dest, const std::string &src )
	{
		std::istringstream in( src );
		in >> dest;
		if ( in.error() ) {
			m_error = true;
		}
	}

private:
	message_c &m_msg;
	int m_arg;
	bool m_error;
};


/**
 * Object that imports values from a typed object into a string-based message.
 */
class message_import_c
{
public:
	message_import_c( message_c &msg )
	: m_message( msg )
	, m_arg( 0 )
	, m_error( false )
	{}

	template < typename T >
	copy_ostream & operator + ( const T &value )
	{
		std::string arg;
		copy( arg, value );
		out >> value;
		return *this;
	}

	/**
	 * Copy a value into a string type.
	 */
	template < typename T >
	void copy( std::string &arg, const T &value )
	{
		std::ostringstream out;
		out << value;
		arg = out.str();
	}

private:
	std::ostream &m_out;
	int m_arg;
	bool m_error;
};


class get_request_c
: public request_c
{
public:
	/**
	 * Command constructor.
	 */
	get_request_c( const std::string &user_id
			, const std::string &session_id );
	: request_c( "get" )
	, m_user_id( user_id )
	, m_session_id( session_id )
	{}

	/**
	 * Service constructor.
	 */
	get_request_c( const request_c &req )
	: request_c( req )
	, m_user_id( req.argv< int >( 0 ) )
	, m_session_id( req.argv< std::string >( 1 ) )
	{}

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

