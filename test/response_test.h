#ifndef RESPONSE_TEST_H
#define RESPONSE_TEST_H

#include "response.h"


class mock_response_c
: public response_c
{
public:
	mock_response_c()
	: response_c()
	, m_code()
	, m_message()
	{}

	template < typename T >
	void copy( T &stream )
	{
		stream + m_code + m_message;
	}

	const std::string & code() const { return m_code; }
	const std::string & message() const { return m_message; }

private:
	std::string m_code;
	std::string m_message;
};


#endif


