#include <stdlib.h>
#include <strings.h>
#include "session_tree.h"

struct session_node {
	struct rb_node rb;
	struct session_s data;
};

static struct rb_root session_tree = RB_ROOT;

static struct session_node * session_node_create( char *session_name )
{
	struct session_node *session = (struct session_node *) malloc( sizeof( *session ) );
	bzero( session, sizeof( *session ) );
	return session;
}

static void session_node_delete( struct session_node **session )
{
	free( session );
	*session = NULL;
}

static struct session_node * session_node_search( struct rb_root *root, char *session_name )
{
	struct rb_node *search_node = root->rb_node;

	while ( search_node ) {
		struct session_node *session; 
		int result;

		// session = container_of( search_node, struct session_node, rb );
		session = (struct session_node *) search_node;
		result = strcmp( session_name, session->data.name );
		if ( result < 0 )
			search_node = search_node->rb_left;
		else if ( result > 0 )
			search_node = search_node->rb_right;
		else
			return session;
	}

	return NULL;
}

static int session_node_insert( struct rb_root *root, char *session_name )
{
	struct rb_node **new_node = &(root->rb_node);
	struct rb_node *parent = NULL;
	struct session_node* new_session = session_node_create( session_name );

	while ( *new_node ) {
		struct session_node *this = (struct session_node *) *new_node;
		int result = strcmp( new_session->data.name, this->data.name );

		parent = *new_node;
		if ( result < 0 ) {
			new_node = &( (*new_node)->rb_left );
		} else if ( result > 0 ) {
			new_node = &( (*new_node)->rb_right );
		} else {
			session_node_delete( &new_session );
			return 0;
		}
	}
	rb_link_node( &new_session->rb, parent, new_node );
	rb_insert_color( &new_session->rb, root );

	return 1;
}


int session_exists( char *session_name )
{
	return (int) session_node_search( &session_tree, session_name );
}

void create_session( char *session_name )
{
	session_node_insert( &session_tree, session_name );
}

