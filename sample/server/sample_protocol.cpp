#include "sample_protocol.h"
#include "snapl/response.h"


get_service_c::get_service_c()
: service_c< request_c, response_c >()
{}

void get_service_c::execute( const request_c &req, response_c &resp )
{
	resp.ok( "get successful" );
}


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

