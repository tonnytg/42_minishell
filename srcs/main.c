/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/03 22:55:44 by caalbert         ###   ########.fr       */
=======
/*   Updated: 2023/06/03 20:10:12 by caalbert         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_commands(t_cmds *cmds)
{
	size_t	i;

	i = 0;
	while (i < cmds->num_cmds)
	{
		free(cmds->arr_cmds[i].name);
		i++;
	}
	free(cmds->arr_cmds);
	free(cmds->cmd_finded);
	free(cmds->input);
	free(cmds);
}

int	is_exit(t_cmds *cmds)
{
	if (ft_strcmp(cmds->exit_code.last_cmd, "exit") == 0)
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
	int	exit_code;

	signals_handler();
	while (1)
	{
		read_keyboard(cmds);
		if (cmds->input->cmd_name == NULL)
			continue ;
		find_command(cmds);
		execute_cmd(cmds);
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
	cmds = malloc(sizeof(t_cmds) * 1);
	cmds->input = malloc(sizeof(t_input) * 1);
	cmds->cmd_finded = malloc(sizeof(t_command));
	cmds->exit_code.code = 0;
	cmds->envs = malloc(sizeof(char *) * (count_envp(envp) + 2));
	set_envs(envp, cmds);
	set_commands(cmds);
	exit_code = minishell(cmds);
	free_envs(cmds);
	free_commands(cmds);
	return (exit_code);
}
