#include "sample_protocol.h"
#include "snapl/response.h"


get_action_c::get_action_c()
: action_i( "get" )
{}

void get_action_c::execute( const request_c &req, response_c &resp )
{
	resp.ok( "get successful" );
}


put_action_c::put_action_c()
: action_i( "put" )
{}

void put_action_c::execute( const request_c &req, response_c &resp )
{
	resp.ok( "put successful" );
}


add_action_c::add_action_c()
: action_i( "add" )
{}

void add_action_c::execute( const request_c &req, response_c &resp )
{
	resp.ok( "add successful" );
}


delete_action_c::delete_action_c()
: action_i( "delete" )
{}

void delete_action_c::execute( const request_c &req, response_c &resp )
{
	resp.ok( "delete successful" );
}

