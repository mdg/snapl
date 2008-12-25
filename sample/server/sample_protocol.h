#ifndef SAMPLE_PROTOCOL_H
#define SAMPLE_PROTOCOL_H

#include "../../src/action.h"
#include "../../src/protocol.h"


class dog_action_c
: public action_i
{
public:
	dog_action_c();

	virtual void execute( const request_c &, response_c & );
};

class cat_action_c
: public action_i
{
public:
	cat_action_c();

	virtual void execute( const request_c &, response_c & );
};


class sample_protocol_c
: public protocol_c
{
public:
	sample_protocol_c( short port )
	: protocol_c( port )
	{
		add( m_dog );
		add( m_cat );
	}

private:
	dog_action_c m_dog;
	cat_action_c m_cat;
};


#endif

