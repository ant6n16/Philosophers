# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 19:39:00 by antdelga          #+#    #+#              #
#    Updated: 2023/09/28 19:11:49 by antdelga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread

SRC = main.c \
	  check_input.c \
	  utils.c \
	  threads.c \
	  messages.c \
	  die.c \
	  
OBJ = $(SRC:.c=.o)

EXECUTABLE = philo

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean re
