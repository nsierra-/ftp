#include <unistd.h>
#include <stdlib.h>
#include "server.h"
#include "libft.h"

int							close_client_connection(int fd, const char **input)
{
	(void)input;
	respond(fd, Success, "Bye bye.");
	close(fd);
	ft_putendl("Connection ended.");
	exit(EXIT_SUCCESS);
	return (1);
}
