#include "shession_client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


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
		return false;
	}

	m_socket = socket( PF_INET, SOCK_STREAM, 0 );
	if ( m_socket < 0 ) {
		return false;
	}

	return 0 == connect( m_socket, (const sockaddr *) &addr
			, sizeof(addr) );
}

void shession_client_c::close()
{
	if ( m_socket ) {
		shutdown( m_socket, SHUT_RDWR );
		m_socket = 0;
	}
}

