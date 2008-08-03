#ifndef REQUEST_READER_H
#define REQUEST_READER_H

#include <sstream>
#include "request_type.h"

class request_c;


/**
 * A class to read requests from an existing connection.
 */
class request_reader_c
{
public:
	request_reader_c( int connection );
	~request_reader_c();

	bool open() const { return m_connection; }
	void close();

	request_c * create_request();

private:
	static request_type_e get_request_type( const std::string& req_type );

	int m_connection;
};


#endif

