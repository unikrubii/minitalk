# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 00:44:18 by sthitiku          #+#    #+#              #
#    Updated: 2022/05/27 13:44:15 by sthitiku         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server client

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC_DIR = srcs/
OBJ_DIR = objs/

SRCS = server.c client.c

all: $(NAME)

