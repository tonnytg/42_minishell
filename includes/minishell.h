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

/* Each Command */
typedef struct s_command{
	char	*name;
	int		(*execute)(const char*);
}	t_command;

/* Array of commands */
typedef struct s_commands{
	int			num_cmds;
	t_command	*cmd;
}	t_cmds;

/* Read Keyboard command and arguments */
typedef struct s_input{
	char		input[256];
	char		*cmd_name;
	char		*cmd_arg;
}	t_input;

/* Read Keyboard */
void		read_keyboard(t_input *data);
t_command	*find_command(t_cmds *cmds, const char *name);

/* Set commands */
void	set_commands(t_cmds *cmds);
void	free_commands(t_cmds *commands);

/* Commands */
int			echo_adapter(const char *arg);
int			pwd_adapter(const char *arg);
int			exit_adapter(const char *arg);

#endif