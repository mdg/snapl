#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H


class message_queue_i
{
public:
	virtual ~message_queue_i() {}

	virtual void send( message_i * ) = 0;
	virtual void send( const message_i & ) = 0;
	virtual void receive( message_i * ) = 0;
};


#endif

