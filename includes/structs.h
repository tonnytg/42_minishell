/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

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
	int		(*execute)(t_cmds *cmds);
}	t_command;

typedef struct s_envs{
	char	*name;
	char	*value;
}	t_envs;

#endif
