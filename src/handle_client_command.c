
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
