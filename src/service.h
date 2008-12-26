#ifndef SERVICE_H
#define SERVICE_H


/**
 * Untyped service interface.  This gets passed around the server and is
 * what gets called by the type-agnostic framework.
 */
class service_i
{
	virtual ~service_i() {}

	/**
	 * Execute this untyped service.
	 */
	virtual void execute() = 0;

	virtual const response_c & response() const = 0;
};


/**
 * Typed service class.
 * This transfers untyped data into typed objects, calls the service
 * execution and transfers the typed response into untyped data.
 */
template < typename ReqT, typename RespT >
class service_c
{
public:
	service_c( const std::string &req )
	: m_request( req )
	, m_response()
	{}

	virtual const response_c & response() const { return m_response; }

protected:
	const ReqT m_request;
	RespT m_response;
};


#endif

