# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 22:19:58 by caalbert          #+#    #+#              #
#    Updated: 2023/07/27 21:18:52 by caalbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
HEADER	= $(NAME).h
FILES	= \
			srcs/main.c								\
			srcs/minishell_utils.c					\
			srcs/minishell_utils2.c					\
			srcs/read_keyboard/input.c				\
			srcs/read_keyboard/check_data_input.c	\
			srcs/commands/commands.c				\
			srcs/commands/interpreter.c				\
			srcs/commands/nodes.c					\
			srcs/commands/type_commands.c 			\
			srcs/commands/exec_builtin_cmd.c 		\
			srcs/commands/exec_external_cmd.c 		\
			srcs/commands/pipes.c 					\
			srcs/path/path.c						\
			srcs/builtins/cd.c						\
			srcs/builtins/echo.c					\
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
			srcs/parser/redirects.c					\
			srcs/quotes/quotes.c					\
			srcs/quotes/quotes_utils.c

OBJS	= $(FILES:.c=.o)
CC		= gcc
CC_ARGS = -Wextra -Wall -Werror -g3
LIBS	= libft
CYAN			:= \033[1;36m
YELLOW			:= \033[1;33m
GREEN			:= \033[1;32m
RED				:= \033[1;31m
GRAY			:= \033[1;30m
RESET			:= \033[0m

all: $(LIBS) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CC_ARGS) $(OBJS) -L $(LIBS) -lft -lreadline -o $(NAME)
	ar rsc $(LIBS)/lib$(NAME).a $(OBJS)
	@echo "${GREEN}\nMinishell has been successfully compiled!${RESET}"
	@echo "$(CYAN)\n\tTo use Minishell, follow these steps in your terminal:$(RESET)"
	@echo "$(GRAY)\n\t1. Switch to the bash shell if you're currently using other:$(RESET)"
	@echo "\n\t\t > bash"
	@echo "$(GRAY)\n\t2. Then, run the Minishell executable:$(RESET)"
	@echo "\n\t\t > ./minishell"
	@echo ""

%.o: %.c
	$(CC) $(CC_ARGS) -I$(LIBS) -c $< -o $@

$(LIBS):
	make -C $(LIBS)

test: all
	make -C tests

debug:
	$(CC) $(CC_ARGS) -g $(FILES) -L $(LIBS) -lft -lreadline -o srcs/$(NAME)

valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/$(NAME)

va:
	valgrind -q --leak-check=full --show-leak-kinds=all --trace-children=yes \
                        --track-fds=yes --track-origins=yes --suppressions=readline.supp\
                        --trace-children-skip='/bin/,/sbin/'  ./minishell

v: all
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell

clean:
	make -C $(LIBS) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBS) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(LIBS)
