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

char	*get_env(t_cmds *cmds, char *str, int config)
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
	temp = getvarenv(cmds, env_2);
	free(env_1);
	free(env_2);
	if (temp == NULL)
	{
		if (config == 1)
			result = ft_strdup("");
		else
			result = NULL;
		return (result);
	}
	result = ft_strdup(temp);
	free(temp);
	return (result);
}

char	*get_shlvl(char *str)
{
	char	*temp_itoa;
	int		shlvl;
	char	*new_var;
	char	**temp;
	char	*shlvl_str;

	temp = ft_split(str, '=');
	shlvl = ft_atoi(temp[1]);
	temp_itoa = ft_itoa(shlvl + 1);
	shlvl_str = ft_strjoin("SHLVL=", temp_itoa);
	new_var = ft_strdup(shlvl_str);
	free_arr(temp);
	free(temp_itoa);
	free(shlvl_str);
	return (new_var);
}

void	set_envs(char **envp, t_cmds *cmds)
{
	int		i;
	int		j;
	char	*msg;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
		{
			cmds->envs[j] = get_shlvl(envp[i]);
			j++;
		}
		else
		{
			msg = ft_strnstr(envp[i], "WORKSPACE", ft_strlen("WORKSPACE") - 1);
			if (msg == NULL)
			{
				cmds->envs[j] = ft_strdup(envp[i]);
				j++;
			}
		}
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
