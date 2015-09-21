#include "server.h"
#include "libft.h"
#include <sys/socket.h>

void	respond(int fd, t_cmd_status status, const char *msg)
{
	if (status == Success)
		send(fd, MSG_CMD_SUCCCESS, ft_strlen(MSG_CMD_SUCCCESS), 0);
	else if (status == Failure)
		send(fd, MSG_CMD_FAILURE, ft_strlen(MSG_CMD_FAILURE), 0);
	send(fd, msg, ft_strlen(msg), 0);
}
