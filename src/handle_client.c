/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 12:49:50 by nsierra-          #+#    #+#             */
/*   Updated: 2015/09/21 12:49:51 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "server.h"

static int			check_read_return(int fd, int ret)
{
	if (ret == 0)
		return (0);
	else if (ret < 0)
		close_and_die(fd, "Read error", EXIT_FAILURE);
	return (1);
}

static char			**retrieve_input(int fd, int read_size, const char *input)
{
	char			buf[BUF_SIZE + 1];
	char			*tmp;
	char			*tmp2;
	char			**ret;

	ret = NULL;
	if (read_size < BUF_SIZE)
		return (ft_split(input, FT_WHITESPACE));
	tmp = ft_strdup(input);
	while (read_size == BUF_SIZE)
	{
		ft_bzero(buf, BUF_SIZE + 1);
		read_size = read(fd, buf, BUF_SIZE);
		if (!check_read_return(fd, read_size))
		{
			ft_free_tab(ret);
			return (NULL);
		}
		tmp2 = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = tmp2;
	}
	ret = ft_split(tmp2, FT_WHITESPACE);
	free(tmp2);
	return (ret);
}

void				handle_client(int fd)
{
	unsigned int	n;
	size_t			prompt_size;
	char			buf[BUF_SIZE + 1];
	char			**usr_input;

	prompt_size = ft_strlen(PROMPT_STR);
	while (42)
	{
		usr_input = NULL;
		ft_bzero(buf, BUF_SIZE + 1);
		send(fd, PROMPT_STR, prompt_size, 0);
		n = read(fd, buf, BUF_SIZE);
		if (!check_read_return(fd, n)
			|| !(usr_input = retrieve_input(fd, n, buf)))
		{
			ft_free_tab(usr_input);
			break ;
		}
		if (usr_input[0])
			handle_client_command(fd, usr_input);
		ft_free_tab(usr_input);
	}
	close(fd);
	ft_putendl("Connection ended");
	exit(EXIT_SUCCESS);
}
