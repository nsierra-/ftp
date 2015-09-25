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

#include <unistd.h>
#include "libft.h"
#include "server.h"

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

int						main(void)
{
	init_server();
	while (42)
	{
		ft_putendl("Server is now waiting...");
		accept_connection();
	}
	return (0);
}
