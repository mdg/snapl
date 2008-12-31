#include "client_server_test.h"
#include <testpp/test.h>


mock_connection_c::mock_connection_c( std::queue< std::string > &read_queue,
			std::queue< std::string > &write_queue )
: m_read_queue( read_queue )
, m_write_queue( write_queue )
{}

void mock_connection_c::read_line( std::string &line )
{
	line = m_read_queue.front();
	m_read_queue.pop();
}

void mock_connection_c::write_line( const std::string &line )
{
	m_write_queue.push( line );
}

bool mock_connection_c::line_ready() const
{
	return ! m_read_queue.empty();
}

