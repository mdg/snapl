#include "sample_protocol.h"


dog_action_c::dog_action_c()
: action_i( "dog" )
{
}

void dog_action_c::execute( const request_c &req, response_c &resp )
{
}


cat_action_c::cat_action_c()
: action_i( "cat" )
{
}

void cat_action_c::execute( const request_c &req, response_c &resp )
{
}

