# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 22:19:58 by caalbert          #+#    #+#              #
#    Updated: 2023/07/23 22:20:02 by caalbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -lreadline -g3

PATH_LIBFT	= ./libft
LIBFT		= $(PATH_LIBFT)/libft.a

SRC_DIR		= srcs
PATH_OBJ	= objects

HEADERS		= includes/$(NAME).h

CYAN			:= \033[1;36m
YELLOW			:= \033[1;33m
GREEN			:= \033[1;32m
RED				:= \033[1;31m
GRAY			:= \033[1;30m
RESET			:= \033[0m

rwildcard=	$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRC_FILES := $(call rwildcard,$(SRC_DIR)/,*.c)

OBJ			= $(patsubst $(SRC_DIR)/%, $(PATH_OBJ)/%, $(SRC_FILES:.c=.o))

all: make_libft $(NAME)

$(NAME): $(OBJ)
	@echo ""
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "${GREEN}\nMinishell has been successfully compiled!${RESET}"
	@echo "$(CYAN)\n\tTo use Minishell, follow these steps in your terminal:$(RESET)"
	@echo "$(GRAY)\n\t1. Switch to the bash shell if you're currently using other:$(RESET)"
	@echo "\n\t\t > bash"
	@echo "$(GRAY)\n\t2. Then, run the Minishell executable:$(RESET)"
	@echo "\n\t\t > ./minishell"
	@echo ""

$(PATH_OBJ)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -I includes -I libft -o $@ $<


make_libft:
	@make -C $(PATH_LIBFT)

clean:
	@$(RM) $(PATH_OBJ)
	@make -C $(PATH_LIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(PATH_LIBFT) fclean

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re valgrind
