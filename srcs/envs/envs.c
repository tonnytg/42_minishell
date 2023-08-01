/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env(char *str)
{
	char	*env_1;
	char	*env_2;
	char	*temp;
	char	*result;

	env_1 = ft_strdup(str);
	env_2 = remove_string(env_1, '$');
	free(env_1);
	env_1 = remove_string(env_2, '{');
	free(env_2);
	env_2 = remove_string(env_1, '}');
	temp = getenv(env_2);
	free(env_1);
	free(env_2);
	if (temp == NULL)
	{
		result = ft_strdup("");
		return (result);
	}
	result = ft_strdup(temp);
	return (result);
}

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

void	set_envs(char **envp, t_cmds *cmds)
{
	int	i;
	int	shlvl;
	char *shlvl_str;
	char *temp_itoa;
	char **temp;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
		{
			temp = ft_split(envp[i], '=');
			shlvl = ft_atoi(temp[1]);
			temp_itoa = ft_itoa(shlvl + 1);
			shlvl_str = ft_strjoin("SHLVL=", temp_itoa);
			cmds->envs[i] = ft_strdup(shlvl_str);
			free_arr(temp);
			free(shlvl_str);
			free(temp_itoa);
		}
		else
			cmds->envs[i] = ft_strdup(envp[i]);
		i++;
	}
	cmds->envs[i] = NULL;
}

int	append_envs(t_cmds *cmds, char *name, char *value)
{
	int		i;
	char	*env;
	char	*name_equal;

	i = 0;
	while (cmds->envs[i] != NULL)
		i++;
	name_equal = ft_strjoin(name, "=");
	env = ft_strjoin(name_equal, value);
	cmds->envs[i] = env;
	free(name_equal);
	cmds->envs[i + 1] = NULL;
	return (0);
}
