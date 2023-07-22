/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c.                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_var(char *word)
{
	char	*result;

	result = getenv(word);
	if (result != NULL)
		ft_printf("%s ", result);
}

void	print_args(t_cmds *cmds, int index)
{
	int		i;
	char	*word;
	char	**args;

	i = index;
	args = ft_split(cmds->input->cmd_args, ' ');
	while (args[i] != NULL)
	{
		if (args[i][0] == '$')
		{
			word = ft_strtok(args[i], "$", 0);
			if (ft_strcmp(word, "?") == 0)
				ft_printf("%d ", cmds->exit_code.code);
			else
				print_env_var(word);
		}
		else
			ft_printf("%s ", args[i]);
		i++;
	}
	free_arr(args);
}

int	echo_adapter(t_cmds *cmds)
{
	char	**words;
	int		trigger;
	int		i;

	trigger = 0;
	i = 0;
	if (cmds->input->cmd_args == NULL)
	{
		ft_printf("\n");
		return (0);
	}
	words = ft_split(cmds->input->cmd_args, ' ');
	if (ft_strcmp(words[0], "-n") == 0)
	{
		i = 1;
		trigger = 1;
	}
	print_args(cmds, i);
	if (trigger == 0)
		ft_printf("\n");
	free_arr(words);
	return (0);
}
