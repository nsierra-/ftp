#include <unistd.h>
#include "server.h"
#include "libft.h"

int							change_directory(int fd, const char **input)
{
	if (!tokens_are_enough(input, 1))
	{
		respond(fd, Failure, "Too few arguments to cd command.\n");
		return (0);
	}
	else if (tokens_are_too_much(input, 1))
	{
		respond(fd, Failure, "Too much arguments to cd command.\n");
		return (0);
	}
	else if (chdir(input[0]) == -1)
	{
		respond(fd, Failure, "chdir() failed.\n");
		return (0);
	}
	respond(fd, Success, "");
	return (1);
}
