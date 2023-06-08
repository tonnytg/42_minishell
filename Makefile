NAME	= minishell
HEADER	= $(NAME).h
FILES	= \
			srcs/main.c				\
			srcs/input.c			\
			srcs/commands.c			\
			srcs/commands/cd.c		\
			srcs/commands/echo.c	\
			srcs/commands/env.c		\
			srcs/commands/exit.c	\
			srcs/commands/export.c	\
			srcs/commands/pwd.c		\
			srcs/commands/unset.c	\
			srcs/signals/signals.c	\
			srcs/envs.c

OBJS	= $(FILES:.c=.o)
CC		= gcc
CC_ARGS = -Wextra -Wall -Werror -g3
LIBS	= libs

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CC_ARGS) $(OBJS) -L $(LIBS) -lft -o $(NAME)
	ar rsc $(LIBS)/lib$(NAME).a $(OBJS)

%.o: %.c
	mkdir -p libs
	make -C libft
	cp -a libft/libft.h ./includes/
	cp -a libft/libft.a ./libs/
	gcc $(CC_ARGS) -c $< -o $@

test: all
	make -C tests

debug:
	$(CC) $(CC_ARGS) -g $(FILES) -L $(LIBS) -lft -o srcs/$(NAME)

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)
	rm -f includes/libft.h
	rm -rf $(LIBS)

re: fclean all

.PHONY: all clean fclean re
