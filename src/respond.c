#include "server.h"
#include "libft.h"
#include <sys/socket.h>

void		respond(int fd, t_cmd_status status, const char *msg)
{
	size_t	len;

	if (status == Success)
		send(fd, MSG_CMD_SUCCCESS, ft_strlen(MSG_CMD_SUCCCESS), 0);
	else if (status == Failure)
		send(fd, MSG_CMD_FAILURE, ft_strlen(MSG_CMD_FAILURE), 0);
	len = ft_strlen(msg);
	send(fd, msg, len, 0);
	if (*msg && msg[len - 1] != '\n')
		send(fd, "\n", 1, 0);
}
