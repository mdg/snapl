#include "shession_client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>


shession_client_c::shession_client_c()
: m_socket( 0 )
{
}

shession_client_c::~shession_client_c()
{
	close();
}


bool shession_client_c::open( const std::string &url, short port )
{
	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );
	inet_aton( url.c_str(), &addr.sin_addr );
	if ( addr.sin_addr.s_addr == 0 ) {
		std::cerr << "Error identifying address for " << url
			<< std::endl;
		return false;
	}

	m_socket = socket( PF_INET, SOCK_STREAM, 0 );
	if ( m_socket < 0 ) {
		std::cerr << "Error creating socket.\n";
		return false;
	}

	if ( connect( m_socket, (const sockaddr *) &addr, sizeof(addr) ) ) {
		std::cerr << "Failure connecting to " << url << std::endl;
		return false;
	}

	std::cerr << "Connected to " << url << "!\n";
	return true;
}

void shession_client_c::close()
{
	if ( m_socket ) {
		shutdown( m_socket, SHUT_RDWR );
		m_socket = 0;
	}
}


void shession_client_c::create_session( const std::string &session_id )
{
	std::string msg( "create " );
	msg += session_id;
	write( m_socket, msg.c_str(), msg.length() );
}

bool shession_client_c::live_session( const std::string &session_id )
{
	std::string msg( "status " );
	msg += session_id;
	msg += "\n";
	write( m_socket, msg.c_str(), msg.length() );
	char response[5] = { 0 };
	read( m_socket, response, 5 );
	return strcmp( response, "live" ) == 0;
}

void shession_client_c::kill_session( const std::string &session_id )
{
	std::string msg( "kill " );
	msg += session_id;
	write( m_socket, msg.c_str(), msg.length() );
}

