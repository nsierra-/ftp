#include <stddef.h>
#include <dirent.h>
#include "server.h"
#include "libft.h"

static char					*build_file_list(DIR *directory)
{
	struct dirent			*entity;
	char					*answer;
	char					*tmp;

	entity = NULL;
	answer = ft_strnew(0);
	while ((entity = readdir(directory)))
	{
		tmp = answer;
		answer = ft_strjoin(answer, entity->d_name);
		ft_strdel(&tmp);
		tmp = answer;
		answer = ft_strjoin(answer, "\n");
		ft_strdel(&tmp);
	}
	return answer;
}

int							list_files(int fd, const char **input)
{
	DIR						*directory;
	char					*answer;

	(void)input;
	directory = NULL;
	if (!(directory = opendir(".")))
	{
		respond(fd, Failure, "opendir() failed.");
		return (0);
	}
	answer = build_file_list(directory);
	closedir(directory);
	respond(fd, Success, answer);
	ft_strdel(&answer);
	return (1);
}
