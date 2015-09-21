#include <stdlib.h>
#include "server.h"
#include "libft.h"

static void		open_socket(void)
{
	g_server_data.socket_descriptor = socket(AF_INET6, SOCK_STREAM, 0);
	if (g_server_data.socket_descriptor < 0)
		die("socket() failed", EXIT_FAILURE);
}

static void		set_reusable_socket_property(void)
{
	int		on;
	int 	fd;

	fd = g_server_data.socket_descriptor;
	on = 1;
	if (setsockopt(fd, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
		close_and_die(fd, "setsockopt() failed", EXIT_FAILURE);
}

static void		set_listen_backlog(void)
{
	int fd = g_server_data.socket_descriptor;

	if (listen(fd, 32) < 0)
		close_and_die(fd, "listen() failed", EXIT_FAILURE);
}

static void		bind_socket(void)
{
	int fd;
	struct sockaddr_in6	*addr;

	fd = g_server_data.socket_descriptor;
	addr = &g_server_data.addr;
	ft_memset(addr, 0, sizeof(*addr));
	addr->sin6_family = AF_INET6;
	ft_memcpy(&addr->sin6_addr, &in6addr_any, sizeof(in6addr_any));
	addr->sin6_port = htons(SERVER_PORT);
	if (bind(fd, (struct sockaddr *)addr, sizeof(*addr)) < 0)
		close_and_die(fd, "bind() failed", EXIT_FAILURE);
}

void			init_server(void)
{
	open_socket();
	set_reusable_socket_property();
	bind_socket();
	set_listen_backlog();
}
