/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 13:39:58 by nsierra-          #+#    #+#             */
/*   Updated: 2015/09/21 13:39:59 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stddef.h>
# include <netinet/in.h>

# define SERVER_PORT	12345
# define BUF_SIZE		5

# define PROMPT_STR		"--> "

# define TOKEN_LS		"ls"
# define TOKEN_CD		"cd"
# define TOKEN_GET		"get"
# define TOKEN_PUT		"put"
# define TOKEN_PWD		"pwd"
# define TOKEN_QUIT		"quit"

# define MSG_UNKNOWN_CMD	"Unknown command.\n"
# define MSG_CMD_SUCCCESS	"SUCCESS\n"
# define MSG_CMD_FAILURE	"ERROR\n"

typedef enum				e_cmd_status
{
	Success,
	Failure
}							t_cmd_status;

typedef struct				s_server_data
{
	int						socket_descriptor;
	struct sockaddr_in6		addr;

}							t_server_data;

t_server_data				g_server_data;

typedef struct				s_cmd_match
{
	const char				*token;
	int						(*f)(int, const char **);
}							t_cmd_match;

int							list_files(int fd, const char **input);
int							change_directory(int fd, const char **input);
int							send_file(int fd, const char **input);
int							recieve_file(int fd, const char **input);
int							print_working_directory(int fd, const char **input);
int							close_client_connection(int fd, const char **input);

void						init_server(const char *port);
void						handle_client(int fd);
void						handle_client_command(int fd, char **input);
void						respond(int fd, t_cmd_status stat, const char *msg);

int							tokens_are_enough(const char **tokens, int qty);
int							tokens_are_too_much(const char **tokens, int qty);

static const t_cmd_match	g_cmd_match[] = {
	{ TOKEN_LS, list_files },
	{ TOKEN_CD, change_directory },
	{ TOKEN_GET, send_file },
	{ TOKEN_PUT, recieve_file },
	{ TOKEN_PWD, print_working_directory },
	{ TOKEN_QUIT, close_client_connection },
	{ NULL, NULL }
};

#endif
