#ifndef SHESSION_CONTROL_H
#define SHESSION_CONTROL_H

#include <list>

class acceptor_c;
class request_reader_c;


/**
 * The controlling object for the overall
 * shession application.
 */
class shession_control_c
{
public:
	/**
	 * Construct the shession control
	 * object.
	 */
	shession_control_c();
	/**
	 * Destroy the shession_control_c
	 */
	~shession_control_c();

	/**
	 * Start the shession
	 */
	bool execute( short port );

private:
	void accept_connections();
	void process_requests();

	acceptor_c *m_acceptor;
	std::list< request_reader_c * > m_reader;
};


#endif

