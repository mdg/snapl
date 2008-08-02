#ifndef REQUEST_READER_H
#define REQUEST_READER_H

#include <sstream>

class request_c;


/**
 * A class to read requests from an existing connection.
 */
class request_reader_c
{
public:
	request_reader_c( int connection );
	~request_reader_c();

	request_c * create_request();

private:
	int m_connection;
};


#endif

