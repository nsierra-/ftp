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

#include "libft.h"
#include "server.h"

void		handle_client_command(int fd, char **input)
{
	int		i;

	(void)fd;
	i = 0;
	while (input[i] != NULL)
		ft_putendl(input[i++]);
}
