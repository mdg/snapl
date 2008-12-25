#ifndef SAMPLE_PROTOCOL_H
#define SAMPLE_PROTOCOL_H

#include "../../src/action.h"
#include "../../src/protocol.h"


class get_action_c
: public action_i
{
public:
	get_action_c();

	virtual void execute( const request_c &, response_c & );
};

class put_action_c
: public action_i
{
public:
	put_action_c();

	virtual void execute( const request_c &, response_c & );
};

class add_action_c
: public action_i
{
public:
	add_action_c();

	virtual void execute( const request_c &, response_c & );
};

class delete_action_c
: public action_i
{
public:
	delete_action_c();

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
	get_action_c m_get;
	put_action_c m_put;
	add_action_c m_add;
	delete_action_c m_delete;
};


#endif

