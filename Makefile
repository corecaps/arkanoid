# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 23:44:55 by jgarcia           #+#    #+#              #
#    Updated: 2023/02/15 23:49:47 by jgarcia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = arkanoid
CURRENT_DIR = $(shell pwd)
CC = gcc
CFLAGS = -Wall -Wextra -g -c
INC = -Iminilibx-linux/
LINK = -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz

SRC = main.c render.c hooks.c graphic_utils.c
OBJ = $(SRC:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LINK) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) $(INC) $< -o $@

$(CURRENT_DIR)/minilibx/libmlx.a:
	make -C minilibx-linux

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean all re