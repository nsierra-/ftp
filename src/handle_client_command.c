/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 12:50:03 by nsierra-          #+#    #+#             */
/*   Updated: 2015/09/21 12:50:05 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include "libft.h"
#include "server.h"

static int	(*get_cmd_function(const char *input))(int, const char **)
{
	int		i;

	i = 0;
	while (g_cmd_match[i].token && g_cmd_match[i].f)
	{
		if (!ft_strcmp(g_cmd_match[i].token, input))
			return (g_cmd_match[i].f);
		++i;
	}
	return (NULL);
}


void		handle_client_command(int fd, char **input)
{
	int		(*cmd_handler)(int, const char **);

	cmd_handler = get_cmd_function(*input);
	if (!cmd_handler)
		respond(fd, Failure, MSG_UNKNOWN_CMD);
	else
		respond(fd, Success, "Euker");
}
