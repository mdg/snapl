#include "request_reader.h"
#include <iostream>
#include <sys/socket.h>
#include "request.h"


request_reader_c::request_reader_c( int connection )
{
	m_connection = connection;
}

request_reader_c::~request_reader_c()
{
	close();
}


void request_reader_c::close()
{
	if ( m_connection ) {
		shutdown( m_connection, SHUT_RDWR );
		m_connection = 0;
	}
}


request_c * request_reader_c::create_request()
{
	std::istringstream stream( readline() );
	std::string request;
	std::string session_id;
	stream >> request;
	stream >> session_id;

	request_type_e req_type = get_request_type( request );
	std::cerr << "req_type = " << (int) req_type << std::endl;
	request_c *req = new request_c( req_type, session_id );
	std::string token_name;

	// check if this is a close request
	if ( req_type == RT_CLOSE ) {
		std::cerr << "close!\n";
		close();
		return NULL;
	} else if ( req_type == RT_NULL ) {
		return NULL;
	} else if ( req_type == RT_STORE_TOKEN ) {
		stream >> token_name;
		req->set_token_name( token_name );
		req->set_token_value( readline() );
	} else if ( req_type == RT_REQUEST_TOKEN ) {
		stream >> token_name;
		req->set_token_name( token_name );
	}

	return req;
}

std::string request_reader_c::readline() const
{
	char buffer[256];
	read( m_connection, buffer, sizeof( buffer ) );

	// remove the new lines
	char *nl = strchr( buffer, '\n' );
	if ( nl ) {
		*nl = '\0';
	}
	nl = strchr( buffer, '\r' );
	if ( nl ) {
		*nl = '\0';
	}

	return buffer;
}

request_type_e request_reader_c::get_request_type( const std::string& req_type )
{
	std::cerr << "request = '" << req_type << "'\n";

	request_type_e rt( RT_NULL );
	if ( req_type == "store" ) {
		return RT_STORE_SESSION;
	} else if ( req_type == "store_token" ) {
		return RT_STORE_TOKEN;
	} else if ( req_type == "kill" ) {
		return RT_KILL_SESSION;
	} else if ( req_type == "status" ) {
		return RT_SESSION_STATUS;
	} else if ( req_type == "token" ) {
		return RT_REQUEST_TOKEN;
	} else if ( req_type == "close" ) {
		return RT_CLOSE;
	} else {
		return RT_NULL;
	}
}
