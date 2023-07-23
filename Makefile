NAME	= minishell
HEADER	= $(NAME).h
FILES	= \
			srcs/main.c								\
			srcs/minishell_utils.c					\
			srcs/read_keyboard/input.c				\
			srcs/read_keyboard/check_data_input.c	\
			srcs/commands/commands.c				\
			srcs/commands/nodes.c					\
			srcs/commands/path.c					\
			srcs/commands/type_commands.c 			\
			srcs/commands/exec_builtin_cmd.c 		\
			srcs/commands/exec_external_cmd.c 		\
			srcs/commands/pipes.c 					\
			srcs/builtins/cd.c						\
			srcs/builtins/echo.c					\
			srcs/builtins/echo_utils.c				\
			srcs/builtins/env.c						\
			srcs/builtins/exit.c					\
			srcs/builtins/export.c					\
			srcs/builtins/pwd.c						\
			srcs/builtins/unset.c					\
			srcs/signals/signals.c					\
			srcs/envs/envs.c						\
			srcs/parser/token_analysis.c 			\
			srcs/parser/syntax_analysis.c 			\
			srcs/parser/build_struct_to_exec.c 		\
			srcs/parser/redirects.c

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

valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes srcs/$(NAME)

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
