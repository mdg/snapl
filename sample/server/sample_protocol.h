#ifndef SAMPLE_PROTOCOL_H
#define SAMPLE_PROTOCOL_H

#include "snapl/service.h"
#include "snapl/protocol.h"
#include "snapl/command.h"


class get_command_c
: public snapl::command_c
{
public:
	std::string value;
	std::string output;

	get_command_c()
	: command_c( "get" )
	, value()
	, output()
	{
		m_request << value;
		m_response << output;
	}

	get_command_c( const std::string &val )
	: command_c( "get" )
	, value( val )
	, output()
	{
		m_request << value;
		m_response << output;
	}
};


class get_service_c
: public snapl::service_c< get_command_c >
{
public:
	get_service_c();

	virtual void execute( get_command_c & );
};

/*
class put_service_c
: public snapl::service_c< put_command_c >
{
public:
	put_service_c();

	virtual void execute( put_command_c & );
};

class add_service_c
: public snapl::service_c< add_command_c >
{
public:
	add_service_c();

	virtual void execute( add_command_c & );
};

class del_service_c
: public snapl::service_c< del_command_c >
{
public:
	del_service_c();

	virtual void execute( del_command_c & );
};
*/


class sample_protocol_c
: public snapl::protocol_c
{
public:
	sample_protocol_c( short port )
	: protocol_c( port )
	{
		add( "get", m_get );
		// add( "put", m_put );
		// add( "add", m_add );
		// add( "del", m_del );
	}

private:
	get_service_c m_get;
	// put_service_c m_put;
	// add_service_c m_add;
	// del_service_c m_del;
};


#endif

