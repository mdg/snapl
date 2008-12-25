#include "sample_protocol.h"
#include "../../src/dispatcher.h"
#include "../../src/connection_acceptor.h"
#include "../../src/polling_server_queue.h"


int main( int argc, char **argv )
{
	short port( 9000 );

	sample_protocol_c sample_protocol( port );
	connection_acceptor_c acceptor;
	acceptor.open_listener( port );
	polling_server_queue_c queue( acceptor );
	dispatcher_c dispatch( queue );

	dispatch.add( sample_protocol );
	dispatch.main_loop();
	return 0;
}

