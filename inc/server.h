#ifndef SERVER_H
# define SERVER_H

# include <netinet/in.h>

typedef struct				s_server_data
{
	int						socket_descriptor;
	struct sockaddr_in6		addr;

}							t_server_data;

t_server_data				g_server_data;

#endif /* SERVER_H */
