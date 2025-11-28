# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nwirtzbi <nwirtzbi@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/09 16:21:43 by nwirtzbi          #+#    #+#              #
#    Updated: 2025/11/28 09:44:17 by nwirtzbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library
NAME = get_next_line.a

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Source files list
SRC = \
get_next_line.c \
get_next_line_utils.c
# Object files generated from source files
OBJ = $(SRC:.c=.o)

# Main rule
all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o : %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

# Other rules
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) test

re: fclean all

test: all
	$(CC) $(CFLAGS) main_test.c $(NAME) -o test

.PHONY: all clean fclean re test



