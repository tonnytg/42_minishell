/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_exit_code {
	int		code;
	char	*msg;
	char	*last_cmd;
}	t_exit_code;

/* Read Keyboard command and arguments */
typedef struct s_input{
	char		data[256];
	char		*cmd_name;
	char		*cmd_args;
}	t_input;

/* Each Command */
typedef struct s_command{
	char	*name;
	int		(*execute)(const char*);
}	t_command;

/* Array of commands */
typedef struct s_commands{
	t_input		*input;
	t_command	*cmd_finded;
	int			num_cmds;
	t_command	*arr_cmds;
	t_exit_code	exit_code;
}	t_cmds;

/* Read Keyboard */
void		read_keyboard(t_cmds *cmds);
void		find_command(t_cmds *cmds);

/* Set commands */
void		set_commands(t_cmds *cmds);
void		free_commands(t_cmds *cmds);

/* Commands */
int			echo_adapter(const char *arg);
int			pwd_adapter(const char *arg);
int			exit_adapter(const char *arg);

#endif