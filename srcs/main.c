/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/07/02 19:21:17 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_commands(t_cmds *cmds)
{
	if (cmds->input->datacpy != NULL)
		free(cmds->input->datacpy);
	free(cmds->input);
	free(cmds->exit_code.last_cmd);
	free(cmds->arr_cmds);
	free(cmds->cmd_finded);
	free(cmds);
}

int	is_exit(t_cmds *cmds)
{
	if (cmds->signal_exit == 1)
		return (1);
	return (0);
}

void	check_args(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_printf("minishell: %s: too many arguments\n", argv[1]);
		exit(1);
	}
}

int	minishell(t_cmds *cmds)
{
	int			exit_code;

	while (1)
	{
		if (read_keyboard(cmds))
			continue ;
		token_analysis(cmds);
		syntax_analysis(cmds);
		execute_cmd(cmds);
		free_cmd_nodes(cmds->cmd_list);
		exit_code = cmds->exit_code.code;
		if (is_exit(cmds))
			break ;
	}
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmds	*cmds;
	int		exit_code;

	check_args(argc, argv);
	cmds = ft_calloc(1, sizeof(t_cmds));
	cmds->input = ft_calloc(1, sizeof(t_input));
	cmds->cmd_finded = ft_calloc(1, sizeof(t_command));
	cmds->exit_code.code = 0;
	cmds->exit_code.last_cmd = NULL;
	cmds->signal_exit = -1;
	cmds->envs = ft_calloc(count_envp(envp) + 2, sizeof(char *));
	cmds->has_quote = 0;
	cmds->is_quote_opened = 0;
	set_envs(envp, cmds);
	set_commands(cmds);
	exit_code = minishell(cmds);
	free_envs(cmds);
	free_commands(cmds);
	return (exit_code);
}
