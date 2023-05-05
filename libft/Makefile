# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 15:52:20 by antthoma          #+#    #+#              #
#    Updated: 2023/02/21 00:54:42 by antthoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CC_FLAGS	= -Wall -Werror -Wextra -I . -c
NAME		= libft.a
FILES		= $(wildcard *.c)
OBJS		= $(patsubst %.c,%.o, $(FILES))

all: $(NAME)

%.o: %.c
	$(CC) $(CC_FLAGS) $< -o $@
	ar rsc $(NAME) $@

$(NAME): $(OBJS)

clean:
	rm -rf *.o

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re