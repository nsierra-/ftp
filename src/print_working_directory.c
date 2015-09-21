#include <unistd.h>
#include <sys/param.h>
#include "libft.h"
#include "server.h"

int							print_working_directory(int fd, const char **input)
{
	char					buf[MAXPATHLEN + 2];

	if (tokens_are_too_much(input, 0))
	{
		respond(fd, Failure, "Too much arguments to pwd command.\n");
		return (0);
	}
	else if (!getcwd(buf, MAXPATHLEN))
	{
		respond(fd, Failure, "getcwd() failed.\n");
		return (0);
	}
	respond(fd, Success, buf);
	return (1);
}
