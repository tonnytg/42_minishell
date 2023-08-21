/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envs(t_cmds *cmds)
{
	int	i;

	i = 0;
	if (cmds->envs == NULL)
		return ;
	while (cmds->envs[i] != NULL)
	{
		free(cmds->envs[i]);
		i++;
	}
	free(cmds->envs);
}

int	count_envp(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (0);
	while (envp[i] != NULL)
		i++;
	return (i);
}

char	*found_env_result(t_cmds *cmds, char *var)
{
	char	*result;

	if (ft_strcmp(var, "?") == 0)
		result = ft_itoa(cmds->exit_code.code);
	else if (ft_strcmp(var, "$") == 0)
		result = ft_itoa(cmds->current->c_pid);
	else if (ft_strcmp(var, "#") == 0)
		result = ft_itoa(count_arr(cmds->current->phrase_parsed + 1));
	else if (ft_strcmp(var, "*") == 0)
		result = ft_strdup(cmds->current->phrase);
	return (result);
}

char	*getvarenv(t_cmds *cmds, char *var)
{
	char	*found_env;
	char	**temp;
	int		i;

	i = 0;
	temp = NULL;
	if (cmds->envs == NULL || var == NULL || ft_strlen(var) == 0)
		return (NULL);
	while (cmds->envs[i] != NULL)
	{
		if (ft_strcmp(var, "?") == 0
			|| ft_strcmp(var, "$") == 0
			|| ft_strcmp(var, "#") == 0
			|| ft_strcmp(var, "*") == 0)
			return (found_env_result(cmds, var));
		else if (ft_strncmp(cmds->envs[i], var, ft_strlen(var)) == 0)
		{
			temp = ft_split(cmds->envs[i], '=');
			found_env = ft_strdup(temp[1]);
			free_arr(temp);
			return (found_env);
		}
		i++;
	}
	return (NULL);
}
