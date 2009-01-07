#ifndef REQUEST_TEST_H
#define REQUEST_TEST_H

#include "request.h"


class mock_request_c
: public request_c
{
public:
	mock_request_c()
	: request_c( "mock" )
	, m_id()
	, m_number( 0 )
	{}

	mock_request_c( const std::string &id, int number )
	: request_c( "mock" )
	, m_id( id )
	, m_number( number )
	{}

	template < typename T >
	void copy( T &stream )
	{
		stream + m_id + m_number;
	}

	const std::string & id() const { return m_id; }
	int number() const { return m_number; }

private:
	std::string m_id;
	int m_number;
};


#endif

