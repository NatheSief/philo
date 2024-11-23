# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/02 09:45:51 by xlebecq           #+#    #+#              #
#    Updated: 2024/11/23 15:12:54 by xlebecq          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = clang

C_FLAGS = -Wall -Wextra -Werror -g 
C_FLAGS += -fsanitize=thread

RM = rm -f

LDFLAGS = -pthread



HEADER_DIR = ./header/

SRCS_DIR = ./srcs/

OBJS_DIR = objs/



C_FILES = main.c utils.c

SRCS = $(addprefix $(SRCS_DIR), $(C_FILES))

OBJS = $(addprefix $(OBJS_DIR), $(C_FILES:.c=.o))

INCLUDES = -I$(HEADER_DIR)



all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) -o $(NAME) $(INCLUDES) $(LDFLAGS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@ $(INCLUDES) 

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	$(RM) -r  $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

