/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 12:54:20 by nsierra-          #+#    #+#             */
/*   Updated: 2015/09/21 12:54:26 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "server.h"

static void				print_usage(void)
{
	ft_putendl("Usage : ./server port");
}

static int				check_port(const char *port_str)
{
	int					port;

	port = ft_atoi(port_str);
	if (port > 1023 && port < 65536)
		return (1);
	ft_putstr("The port argument must be a valid port number ");
	ft_putendl("(from 1024 to 65535)");
	return (0);
}

static void				accept_connection(void)
{
	struct sockaddr_in6 client_addr;
	unsigned int		client_addr_len;
	int					new_sock_fd;
	int					fd;
	int					pid;

	fd = g_server_data.socket_descriptor;
	client_addr_len = sizeof(client_addr);
	new_sock_fd = accept(fd, (struct sockaddr*)&client_addr, &client_addr_len);
	ft_putendl("New connection established");
	if ((pid = fork()) == 0)
		handle_client(new_sock_fd);
	else
		close(new_sock_fd);
}

int						main(int ac, const char **av)
{
	if (ac != 2 || !check_port(av[1]))
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	init_server(av[1]);
	while (42)
	{
		ft_putendl("Server is now waiting...");
		accept_connection();
	}
	return (0);
}
