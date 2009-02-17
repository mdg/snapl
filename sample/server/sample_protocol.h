#ifndef SAMPLE_PROTOCOL_H
#define SAMPLE_PROTOCOL_H

#include "snapl/service.h"
#include "snapl/protocol.h"


class get_service_c
: public service_i
{
public:
	get_service_c();

	virtual void execute( const request_c &, response_c & );
};

class put_service_c
: public service_i
{
public:
	put_service_c();

	virtual void execute( const request_c &, response_c & );
};

class add_service_c
: public service_i
{
public:
	add_service_c();

	virtual void execute( const request_c &, response_c & );
};

class delete_service_c
: public service_i
{
public:
	delete_service_c();

	virtual void execute( const request_c &, response_c & );
};


class sample_protocol_c
: public protocol_c
{
public:
	sample_protocol_c( short port )
	: protocol_c( port )
	{
		add( m_get );
		add( m_put );
		add( m_add );
		add( m_delete );
	}

private:
	get_service_c m_get;
	put_service_c m_put;
	add_service_c m_add;
	delete_service_c m_delete;
};


#endif

