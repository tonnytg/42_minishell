/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_pipe(t_cmd_node *current)
{
	printf("open pipe fd in node %p\n", current);
	if (pipe(current->fd) < 0)
		exit (write (1, "Pipe error\n", 12));
}

void	exec_builtin2(t_cmds *cmds, t_cmd_node *current)
{
	size_t i = 0;

	while (i < cmds->num_cmds)
	{
		if (ft_strcmp(current->cmd_name, cmds->arr_cmds[i].name) == 0)
		{
			current->cmd_builtin = &cmds->arr_cmds[i];
			break ;
		}
		i++;
	}
	printf("running %s\n", current->cmd_builtin->name);
	int result = current->cmd_builtin->execute(cmds, current);
}

//void	exec_builtin(t_cmds *cmds)
//{
//	find_command(cmds);
//	if (cmds->cmd_finded->name)
//	{
//		cmds->exit_code.last_cmd = cmds->input->cmd_name;
//		cmds->exit_code.code = cmds->cmd_finded->execute(cmds);
//	}
//	cmds->exit_code.last_cmd = cmds->input->cmd_name;
//	cmds->exit_code.code = 0;
//}

void	exec_external(t_cmds *cmds, t_cmd_node *current)
{
	printf("Run external commands %p\n", cmds);
	printf("phrase: %s\n", current->phrase);
}

void	load_commands(t_cmd_node *current)
{
	char *phrase_copy;

	phrase_copy = malloc(sizeof(char) * ft_strlen(current->phrase));
	ft_memcpy(phrase_copy, current->phrase, sizeof(char) * ft_strlen(current->phrase));
	current->cmd_name = ft_strtok(phrase_copy, " ", 1);
	current->args = ft_strtok(NULL, "", 0);
}

char	*get_fullpath(t_cmd_node *current)
{
	char	**paths;
	char	*temp;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin("/", current->cmd_name);
		if (access(ft_strjoin(paths[i], temp), F_OK) == 0)
			return (ft_strjoin(paths[i], temp));
		i++;
	}
	return (NULL);
}

int	check_type_command(t_cmds *cmds, t_cmd_node *current) // TODO: Estou com erro de segfault aqui
{
	int	i;

	i = 0;
	load_commands(current);
	while (cmds->arr_cmds[i].name != NULL)
	{
		if (ft_strcmp(current->cmd_name, cmds->arr_cmds[i].name) == 0)
		{
			return (0);
		}
		i++;
	}
	if (get_fullpath(current) != NULL)
		return (1);
	return (-1);
}

void	run_node(t_cmds *cmds, t_cmd_node *current)
{
	int	type_command;

	type_command = -1;
	if (ft_strcmp(current->type, "WORD") == 0)
	{
		type_command = check_type_command(cmds, current);
		if (type_command == 0)
			exec_builtin2(cmds, current);
		else if (type_command == 1)
			exec_external(cmds, current);
		else
			printf("minishell: %s: command not found\n", cmds->input->cmd_name);
	}
}

void	execute_cmd(t_cmds *cmds)
{
	t_cmd_node	*current;

	current = cmds->cmd_list;
	while (current != NULL)
	{
		run_node(cmds, current);
		current = current->next;
	}
}
