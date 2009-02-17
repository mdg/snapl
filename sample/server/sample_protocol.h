#ifndef SAMPLE_PROTOCOL_H
#define SAMPLE_PROTOCOL_H

#include "snapl/service.h"
#include "snapl/protocol.h"
#include "snapl/request.h"
#include "snapl/response.h"


class get_service_c
: public service_c< request_c, response_c >
{
public:
	get_service_c();

	virtual void execute( const request_c &, response_c & );
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
		add< get_service_c >( "get" );
		add< put_service_c >( "put" );
		add< add_service_c >( "add" );
		add< del_service_c >( "del" );
	}
};


#endif

