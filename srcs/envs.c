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

#include "../includes/minishell.h"

int	count_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

void	set_envs(char **envp, char **envs)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		envs[i] = ft_strdup(envp[i]);
		i++;
	}
	envs[i] = NULL;
}

int	append_envs(char **envs, char *name, char *value)
{
	int		i;
	char	*env;
	char	*name_equal;

	i = 0;
	while (envs[i] != NULL)
		i++;
	if (envs[i] == NULL)
	{
		name_equal = ft_strjoin(name, "=");
		env = ft_strjoin(name_equal, value);
		envs[i] = env;
	}
	envs[i + 1] = NULL;
	return (0);
}
