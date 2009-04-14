#include "application_message.h"
#include "client_queue.h"

                   -> request ------ request -
                  /                            \
client <-> command                             service
                  \                            /
                    <-response ---- response <-

void test_client_usage()
{
	dog_message_c dog( "cat" );
	m_queue.push( dog );

	m_queue.wait_for_response( dog );
}

void test_server_usage()
{
	dog_command_c dog( "cat" );
	m_queue.push( dog );
	m_queue.wait( dog );
}

action
command
message
transmission
transfer
request



class get_service_c
: public service_c< get_command_c >
{
public:
	void execute( const get_request_c &req, get_rsponse_c &resp )
	{
		resp.ok( m_code );
	}
};


class get_command_c
: public command_c
{
public:
	get_command_c( const std::string &user_id
			, const std::string &session_id )
	: command_c( "get" )
	{}
};

class protocol_mapping_i
{
public:
	virtual ~protocol_mapping() {}

	virtual const std::string & name() const = 0;
	virtual bool command_type( command_i & ) const = 0;
	virtual bool action_type( action_i & ) const = 0;
};


template < typename T >
void core_protocol( T &protocol )
{
	protocol.bind< get_command_c, get_action_c >( "get" );
	protocol.bind< add_command_c, add_action_c >( "add" );
	protocol.bind< up_command_c, up_action_c >( "up" );
	protocol.bind< del_command_c, del_action_c >( "del" );
}


class core_protocol_c
: public protocol_i
{
public:
	core_protocol_c()
	{
		add( m_get );
		add( m_add );
		add( m_up );
		add( m_del );
	}

	core_protocol_c()
	{
		bind< git_command_c >( m_get );
		bind< add_command_c >( m_add );
		bind< up_command_c >( m_up );
		bind< del_command_c >( m_del );
	}

	core_protocol_c( T &binder )
	{
		binder.bind< get_command_c, get_action_c >( "get" );
		binder.bind< add_command_c, add_action_c >( "add" );
	}

	void bind( T &binder )
	{
		binder.bind< get_command_c, get_action_c >( "get" );
		binder.bind< add_command_c, add_action_c >( "add" );
	}

	BIND_COMMAND( get );
	BIND_COMMAND( add );
	BIND_COMMAND( up );

	template < typename T >
	std::string name( const T & ) const { return std::string(); }


	void bind1( protocol_map_i &pmap )
	{
		pmap.bind< get_command_c, get_action_c >( "test" );
		pmap.bind< get_command_c >( "test" ).bind< get_action_c >();
		pmap("test").bind< get_command_c >().bind< get_action_c >();
		pmap("test").bind< get_command_c, get_action_c >();
		bind("test").to< get_command_c, get_action_c >();
	}

	void bind2( protocol_binding_i &binding )
	{
		pmap.bind< get_command_c, get_action_c >( "test" );
		pmap.bind< get_command_c >( "test" ).bind< get_action_c >();
		pmap("test").bind< get_command_c >().bind< get_action_c >();
		pmap("test").bind< get_command_c, get_action_c >();
		bind("test").to< get_command_c, get_action_c >();
		binding.bind< get_command_c, get_action_c >( "get" );
	}

	template < typename CommandT >
	const std::string & name() const;

};

