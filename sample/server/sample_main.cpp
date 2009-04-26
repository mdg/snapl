#include "sample_protocol.h"
#include "snapl/dispatcher.h"
#include "snapl/net/inbox.h"
#include "snapl/net/outbox.h"
#include "connection_acceptor.h"


int main( int argc, char **argv )
{
	short port( 9000 );

	sample_protocol_c sample_protocol( port );

	snapl::queue_c< snapl::server_message_c > request_queue;
	snapl::queue_c< snapl::server_message_c > response_queue;
	snapl::queue_c< snapl::server_message_c > complete_queue;

	snapl::connection_acceptor_c acceptor;
	snapl::inbox_c inbox( acceptor, request_queue, complete_queue );
	snapl::dispatcher_c dispatch( request_queue, response_queue );
	snapl::outbox_c outbox( response_queue, complete_queue );

	inbox.listen( port );

	dispatch.add( sample_protocol );

	for (;;) {
		inbox.iterate();
		dispatch.iterate();
		outbox.iterate();
	}

	return 0;
}

