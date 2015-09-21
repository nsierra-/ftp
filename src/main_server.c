/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/12 19:39:16 by                   #+#    #+#             */
/*   Updated: 2015/09/12 19:39:50 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include "libft.h"
#include "server.h"

#define SERVER_PORT  12345
#define MAXSZ 100

#define TRUE             1
#define FALSE            0

void		die(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void		close_and_die(int fd, const char *msg)
{
	close(fd);
	die(msg);
}

void		open_socket(void)
{
	g_server_data.socket_descriptor = socket(AF_INET6, SOCK_STREAM, 0);
	if (g_server_data.socket_descriptor < 0)
		die("socket() failed");
}

void		set_reusable_socket_property(void)
{
	int		on;
	int 	fd;

	fd = g_server_data.socket_descriptor;
	on = 1;
	if (setsockopt(fd, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
		close_and_die(fd, "setsockopt() failed");
}

void		set_listen_backlog()
{
	int fd = g_server_data.socket_descriptor;

	if (listen(fd, 32) < 0)
		close_and_die(fd, "listen() failed");
}

void		set_timeout_properties(struct timeval *timeout)
{
	timeout->tv_sec  = 3 * 60;
	timeout->tv_usec = 0;
}

void		bind_socket(void)
{
	int fd;
	struct sockaddr_in6	*addr;

	fd = g_server_data.socket_descriptor;
	addr = &g_server_data.addr;
	memset(addr, 0, sizeof(*addr));
	addr->sin6_family = AF_INET6;
	memcpy(&addr->sin6_addr, &in6addr_any, sizeof(in6addr_any));
	addr->sin6_port = htons(SERVER_PORT);
	if (bind(fd, (struct sockaddr *)addr, sizeof(*addr)) < 0)
		close_and_die(fd, "bind() failed");
}

void		handle_client(int fd)
{
	unsigned int	n;
	char			msg[MAXSZ];

	while (42)
	{
		n = read(fd, msg, MAXSZ);
		if(n == 0)
			break ;
		msg[n] = 0;
		send(fd, msg, n, 0);
		printf("Receive and set:%s\n", msg);
	}
	close(fd);
	puts("Connection ended");
	exit(EXIT_SUCCESS);
}

void		accept_connection()
{
	struct			sockaddr_in6 client_addr;
	unsigned int	client_addr_len;
	int				new_sock_fd;
	int				fd;
	int				pid;

	fd = g_server_data.socket_descriptor;
	client_addr_len = sizeof(client_addr);
	new_sock_fd = accept(fd, (struct sockaddr*)&client_addr, &client_addr_len);
	puts("New connection established");
	if ((pid = fork()) == 0)
		handle_client(new_sock_fd);
	else
		close(new_sock_fd);
}

int			main(void)
{
	open_socket();
	set_reusable_socket_property();
	bind_socket();
	set_listen_backlog();

	while (42)
	{
		puts("Server is now waiting...");
		accept_connection();
	}
	return (0);
}


// int main()
// {
//  int sockfd;//to create socket
//  int newsockfd;//to accept connection

//  struct sockaddr_in serverAddress;//server receive on this address
//  struct sockaddr_in clientAddress;//server sends to client on this address

//  int n;
//  char msg[MAXSZ];
//  unsigned int clientAddressLength;
//  int pid;

//  //create socket
//  sockfd=socket(AF_INET,SOCK_STREAM,0);
//  //initialize the socket addresses
//  memset(&serverAddress,0,sizeof(serverAddress));
//  serverAddress.sin_family=AF_INET;
//  serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
//  serverAddress.sin_port=htons(PORT);

//  //bind the socket with the server address and port
//  bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));

//  //listen for connection from client
//  listen(sockfd,5);

//  while(1)
//  {
//   //parent process waiting to accept a new connection
//  	printf("\n*****server waiting for new client connection:*****\n");
//  	clientAddressLength=sizeof(clientAddress);
//  	newsockfd=accept(sockfd,(struct sockaddr*)&clientAddress,&clientAddressLength);
//  	printf("connected to client: %s\n",inet_ntoa(clientAddress.sin_addr));

//   //child process is created for serving each new clients
//  	pid=fork();
//   if(pid==0)//child process rec and send
//   {
//    //rceive from client
//   	while(1)
//   	{
//   		n=recv(newsockfd,msg,MAXSZ,0);
//   		if(n==0)
//   		{
//   			close(newsockfd);
//   			break;
//   		}
//   		msg[n]=0;
//   		send(newsockfd,msg,n,0);

//   		printf("Receive and set:%s\n",msg);
//    }//close interior while
//  	printf("client %s disconnected\n",inet_ntoa(clientAddress.sin_addr));
//    exit(0);
// }
// else
// {
//    close(newsockfd);//sock is closed BY PARENT
// }
//  }//close exterior while

//  return 0;
// }
