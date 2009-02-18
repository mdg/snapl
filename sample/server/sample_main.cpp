#include "sample_protocol.h"
#include "snapl/dispatcher.h"
#include "snapl/net/inbox.h"
#include "snapl/net/outbox.h"
#include "connection_acceptor.h"


int main( int argc, char **argv )
{
	short port( 9000 );

	sample_protocol_c sample_protocol( port );

	queue_c< server_message_c > request_queue;
	queue_c< server_message_c > response_queue;
	queue_c< server_message_c > complete_queue;

	connection_acceptor_c acceptor;
	inbox_c inbox( acceptor, request_queue, complete_queue );
	dispatcher_c dispatch( request_queue, response_queue );
	outbox_c outbox( response_queue, complete_queue );

	inbox.listen( port );

	dispatch.add( sample_protocol );

	for (;;) {
		inbox.iterate();
		dispatch.iterate();
		outbox.iterate();
	}

	return 0;
}

