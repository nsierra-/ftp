#ifndef SERVER_H
# define SERVER_H

# include <netinet/in.h>

# define SERVER_PORT	12345
# define BUF_SIZE		5


typedef struct				s_server_data
{
	int						socket_descriptor;
	struct sockaddr_in6		addr;

}							t_server_data;

t_server_data				g_server_data;

void						init_server(void);
void						handle_client(int fd);
void						handle_client_command(int fd, char **input);

#endif /* SERVER_H */
