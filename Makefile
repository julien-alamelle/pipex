# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalamell <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 13:18:09 by jalamell          #+#    #+#              #
#    Updated: 2022/01/28 17:54:08 by jalamell         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror
INCLUDE=
HFILE=pipex.h
FILES=pipex ft_str ft_file ft_secure
SRC=$(addsuffix .c,$(FILES))
OBJ=$(addsuffix .o,$(FILES))
BFILES=pipex_bonus ft_str ft_file ft_secure
BSRC=$(addsuffix .c,$(BFILES))
BOBJ=$(addsuffix .o,$(BFILES))
NAME=pipex
BONUS=pipex_bonus
all: mandatory bonus

mandatory: $(NAME)

bonus: $(BONUS)

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

%.o: %.c Makefile $(HFILE)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BONUS): $(BOBJ)
	$(CC) $(CFLAGS) $(BOBJ) -o $(BONUS)

.PHONY: all clean fclean re mandatory bonus
