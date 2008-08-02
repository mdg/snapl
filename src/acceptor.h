#ifndef ACCEPTOR_H
#define ACCEPTOR_H


/**
 * A class that accepts socket connections
 * and returns open sockets.
 */
class acceptor_c
{
	static const int DEFAULT_BACKLOG = 128;

public:
	/**
	 * Constructor for the acceptor class.
	 */
	acceptor_c();

	/**
	 * Destructor.  Calls close.
	 */
	~acceptor_c();

	/**
	 * Open the acceptor on the given port.
	 * @port The port on which connections should be accepted.
	 */
	bool open( int port, int backlog = DEFAULT_BACKLOG );

	/**
	 * Closes the acceptor.
	 */
	void close();

	/**
	 * Get an open connection from the listener.
	 * @return 
	 */
	int connection();

private:
	int m_port;
	int m_listener;
};


#endif

