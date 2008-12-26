#ifndef COMMAND_H
#define COMMAND_H


/**
 * Untyped interface for client commands.
 */
class command_i
{
public:
	const request_i & command_request() const { return m_request; }
	response_i & command_response() { return m_response; }

protected:
	command_i( const request_i &req, response_i &resp )
	: m_request( req )
	, m_response( resp )
	{}

private:
	const request_i &m_command_request;
	response_i &m_command_response;
};

/**
 * Typed class for client commands to the server.
 * Uses templated request & response that are shared w/ the
 * server-side service.
 */
template < typename ReqT, typename RespT >
class command_c
{
public:
	/**
	 * Get the template-typed request object.
	 */
	const ReqT & request() const { return m_request; }
	/**
	 * Get the template-typed const response object.
	 */
	const RespT & response() const { return m_response; }
	/**
	 * Get the template-typed response object.
	 */
	RespT & response() { return m_response; }

protected:
	command_c()
	: command_i( m_request, m_response )
	, m_request()
	, m_response()
	{}

	command_c( const Reqt &req )
	: command_i( m_request, m_response )
	, m_request( req )
	, m_response()
	{}

	ReqT m_request;
	RespT m_response;
};


#endif

