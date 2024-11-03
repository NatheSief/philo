# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/02 09:45:51 by xlebecq           #+#    #+#              #
#    Updated: 2024/11/02 15:47:11 by xlebecq          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3

RM = rm -f

HEADER_DIR = ./header/

SRC_DIR = ./src/

SRC = $(addprefix $(SRC_DIR), $(C_FILES))

C_FILES = main.c utils.c

OBJ = $(C_FILES:.c=.o)

OBJS_DIR = objs/

OBJS = $(addprefix $(OBJS_DIR), $(OBJ))

INCLUDES = -I$(HEADER_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c 
	mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)
