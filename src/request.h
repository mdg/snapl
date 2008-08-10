#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "request_type.h"


/**
 * An object to describe a request to the server to manage
 * the sessions.
 */
class request_c
{
public:
	/**
	 * Construct a request object with a given request type
	 * and a string parameter.
	 */
	request_c( request_type_e, const std::string& session_id )
	{}

	/**
	 * Set the token name.  This is only for token requests.
	 */
	void set_token_name( const std::string& token_name )
		{ m_token_name = token_name; }

	/**
	 * Set the token value.  This is optional.
	 */
	void set_token_value( const std::string& token_value )
		{ m_token_value = token_value; }

	/**
	 * Get the type of this request
	 */
	request_type_e request_type() const { return m_req_type; }

	/**
	 * Get the session_id for this request
	 */
	const std::string & session_id() const { return m_session_id; }

	/**
	 * Get the token name.
	 */
	const std::string & token_name() const { return m_token_name; }

	/**
	 * Get the token value.
	 */
	const std::string & token_value() const { return m_token_value; }

private:
	request_type_e m_req_type;
	std::string m_session_id;
	std::string m_token_name;
	std::string m_token_value;
};


#endif

