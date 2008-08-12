#include "request.h"


request_c::request_c( request_type_e request_type
		, const std::string& session_id )
: m_req_type( request_type )
, m_session_id( session_id )
{}

