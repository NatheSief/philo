# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xlebecq <xlebecq@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/02 09:45:51 by xlebecq           #+#    #+#              #
#    Updated: 2024/11/03 07:50:23 by xlebecq          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = clang
C_FLAGS = -Wall -Wextra -Werror
RM = rm -f



HEADER_DIR = ./header/
SRC_DIR = ./src/
OBJS_DIR = objs/



SRCS = $(addprefix $(SRC_DIR), $(C_FILES))
C_FILES = main.c utils.c
OBJ = $(C_FILES:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJ))
INCLUDES = -I$(HEADER_DIR)



all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) -o $(NAME) $(INCLUDES)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c 
	mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@ $(INCLUDES)

clean:
	$(RM) -r  $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

