#include "rbtree.h"

struct session_s {
	char name[40];
};

int session_exists( char *session_name );
void create_session( char *session_name );

