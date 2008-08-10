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
	/**
	 * Construct a request reader object with a given
	 * connection.
	 */
	request_reader_c( int connection );
	/**
	 * Destroy the request reader object.
	 */
	~request_reader_c();

	/**
	 * Check if this request reader is still open.
	 */
	bool connected() const { return m_connection; }

	/**
	 * Close this request reader and it's associated
	 * resources, like the socket connection.
	 */
	void close();

	/**
	 * Create a request by parsing the input from
	 * the socket.
	 */
	request_c * create_request();

	/**
	 * Release the connection for this request reader.
	 */
	int release_connection();

private:
	std::string readline() const;

	static request_type_e get_request_type( const std::string& req_type );

	int m_connection;
};


#endif

