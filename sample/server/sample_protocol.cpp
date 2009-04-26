#include "sample_protocol.h"
#include "snapl/response.h"


get_service_c::get_service_c()
: snapl::service_c< get_command_c >()
{}

void get_service_c::execute( get_command_c &cmd )
{
	cmd.output = "got value";
	cmd.ok();
}


/*
put_service_c::put_service_c()
: service_c< request_c, response_c >()
{}

void put_service_c::execute( const request_c &req, response_c &resp )
{
	resp.ok( "put successful" );
}


add_service_c::add_service_c()
: service_c< request_c, response_c >()
{}

void add_service_c::execute( const request_c &req, response_c &resp )
{
	resp.ok( "add successful" );
}


del_service_c::del_service_c()
: service_c< request_c, response_c >()
{}

void del_service_c::execute( const request_c &req, response_c &resp )
{
	resp.ok( "delete successful" );
}
*/

