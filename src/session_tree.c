#include "session_tree.h"

struct session_node {
	struct rb_node node;
	char *session_name;
};

struct rb_root session_tree = RB_ROOT;

struct session_node * session_search( struct rb_root *root, char *session )
{
	struct rb_node *node = root->rb_node;

	while ( node ) {
		struct session_node *session = container_of( node
				, struct session_node, node );
		int result;

		result = strcmp( session, session_node, session_name );
		if ( result < 0 )
			node = node->rb_left;
		else if ( result > 0 )
			node = node->rb_right;
		else
			return session_node;
	}

	return NULL;
}

