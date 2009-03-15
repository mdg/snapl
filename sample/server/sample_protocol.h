#ifndef SAMPLE_PROTOCOL_H
#define SAMPLE_PROTOCOL_H

#include "snapl/service.h"
#include "snapl/protocol.h"
#include "snapl/request.h"
#include "snapl/response.h"


class get_request_c
: public request_c
{
public:
	get_request_c()
	{
		m_args << m_value;
	}

	void set( const std::string &val )
	{
		m_value = val;
	}

	const std::string & value() const { return m_value; }

private:
	std::string m_value;
};

class get_response_c
: public response_c
{
public:
	get_response_c() {}

	void set_output( const std::string &output ) { m_output = output; }
	const std::string & output() const { return m_output; }

private:
	std::string m_output;
};

class get_command_c
: public command_c< get_request_c, get_response_c >
{
public:
	get_command_c( const std::string &value )
	{
		m_request.set( value );
	}
};

class get_service_c
: public service_c< get_request_c, get_response_c >
{
public:
	get_service_c();

	virtual void execute( const get_request_c &, get_response_c & );
};

class put_service_c
: public service_c< request_c, response_c >
{
public:
	put_service_c();

	virtual void execute( const request_c &, response_c & );
};

class add_service_c
: public service_c< request_c, response_c >
{
public:
	add_service_c();

	virtual void execute( const request_c &, response_c & );
};

class del_service_c
: public service_c< request_c, response_c >
{
public:
	del_service_c();

	virtual void execute( const request_c &, response_c & );
};


class sample_protocol_c
: public protocol_c
{
public:
	sample_protocol_c( short port )
	: protocol_c( port )
	{
		add( "get", m_get );
		add( "put", m_put );
		add( "add", m_add );
		add( "del", m_del );
	}

private:
	get_service_c m_get;
	put_service_c m_put;
	add_service_c m_add;
	del_service_c m_del;
};


#endif

