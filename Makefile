# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 00:44:18 by sthitiku          #+#    #+#              #
#    Updated: 2022/05/27 14:04:28 by sthitiku         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server client

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC_DIR = srcs/
OBJ_DIR = objs/

SRCS = server.c client.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):$(addprefix $(OBJ_DIR), $(OBJS))
	$(CC) $(addprefix $(OBJ_DIR), server.o) -o server
	$(CC) $(addprefix $(OBJ_DIR), client.o) -o client
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
