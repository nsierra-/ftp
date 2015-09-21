# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/02 08:22:33 by nsierra-          #+#    #+#              #
#    Updated: 2014/05/19 08:55:18 by nsierra-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	server

INC_FILES	=

SRC_FILES	=	main_server.c \
				init_server.c \
				handle_client.c \
				handle_client_command.c \
				list_files.c \
				change_directory.c \
				send_file.c \
				recieve_file.c \
				print_working_directory.c \
				close_client_connection.c \
				respond.c \
				utils.c

FTLST_DIR	=	./ftlst
LIBFT_DIR	=	./libft

SRC			=	$(addprefix src/, $(SRC_FILES))
INC			=	$(addprefix inc/, $(INC_FILES))
OBJ			=	$(SRC:.c=.o)

CC			=	gcc
MAKE		=	make

CFLAGS		=	-Wall -Wextra -Werror -pedantic -g3
IFLAGS		=	-I./inc/ -I$(LIBFT_DIR) -I$(FTLST_DIR)
LDFLAGS		=	-L$(LIBFT_DIR) -lft -L$(FTLST_DIR) -lftlst


$(NAME):		subm $(INC) $(OBJ)
				$(MAKE) -C ftlst/
				$(MAKE) -C libft/
				$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $@

all:			$(NAME)

%.o:			%.c
				$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
				$(MAKE) -C libft/ clean
				$(MAKE) -C ftlst/ clean
				rm -rf $(OBJ)

fclean:			clean
				$(MAKE) -C libft/ fclean
				$(MAKE) -C ftlst/ fclean
				rm -f $(NAME)

test:			all
				./$(NAME)

re:				fclean all

subm:
				test -d "./ftlst" || git submodule add -b 42 https://github.com/nsierra-/ftlst.git ftlst
				test -d "./libft" || git submodule add -b master https://github.com/nsierra-/libft.git libft
				git submodule update --init --remote --recursive

.PHONY:
