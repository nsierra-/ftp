#include "libft.h"
#include "ftlst.h"
#include "server.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

static int					is_regular_file(const char *path)
{
    struct stat				path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

static int					open_and_send(int sockfd, int file_fd)
{
	char					buf[BUF_SIZE];
	ssize_t					nbytes;
	ssize_t					offset;
	ssize_t					sent;

	nbytes = 0;
	while ((nbytes = read(file_fd, buf, BUF_SIZE)) > 0)
	{
		offset = 0;
		sent = 0;
		while ((sent = send(sockfd, buf + offset, nbytes, 0)) > 0
			|| (sent == -1 && errno == EINTR))
		{
			if (sent > 0)
			{
				offset += sent;
				nbytes -= sent;
			}
		}
	}
	send(sockfd, "\n", 1, 0);
	return (1);
}

int							send_file(int fd, const char **input)
{
	int						file_fd;

	if (!tokens_are_enough(input, 1))
	{
		respond(fd, Failure, "Too few arguments to get command.");
		return (0);
	}
	else if (tokens_are_too_much(input, 1))
	{
		respond(fd, Failure, "Too much arguments to get command.");
		return (0);
	}
	if (!is_regular_file(*input))
	{
		respond(fd, Failure, "Argument is not a regular file.");
		return (0);
	}
	if ((file_fd = open(*input, O_RDONLY)) <= 0)
	{
		respond(fd, Failure, "open() failed. Input file may be invalid.");
		return (0);
	}
	return (open_and_send(fd, file_fd));
}
