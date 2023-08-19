/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/08/11 00:50:37 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quote_phrase(char *phrase)
{
	int	i;

	i = 0;
	while (phrase[i] != '\0')
	{
		if (phrase[i] == '\"' || phrase[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	count_env(t_cmds *cmds, t_get_env	*t_g)
{
	t_g->trigger = 0;
	t_g->temp_var[t_g->j] = '\0';
	if (ft_strcmp(t_g->temp_var, "?") == 0)
		t_g->result = ft_itoa(cmds->exit_code.code);
	else
		t_g->result = getvarenv(cmds, t_g->temp_var);
	if (t_g->result == NULL || ft_strlen(t_g->result) == 0)
	{
		if (t_g->temp_var != NULL)
		{
			free(t_g->temp_var);
			t_g->temp_var = NULL;
		}
		return (0);
	}
	t_g->count = t_g->count + ft_strlen(t_g->result);
	if (t_g->result != NULL)
	{
		free(t_g->result);
		t_g->result = NULL;
	}
	t_g->j = 0;
	return (1);
}

int	search_env(t_cmds *cmds, t_get_env	*t_g, char *str)
{
	while (str[t_g->i] != '\0')
	{
		if (str[t_g->i] == '$')
			t_g->trigger = 1;
		if ((count_env(cmds, t_g)) == 0)
			return (0);
		if (t_g->trigger == 1 && str[t_g->i] != ' ')
		{
			t_g->temp_var[t_g->j] = str[t_g->i];
			t_g->j++;
		}
		t_g->i++;
	}
	return (1);
}

int	get_env_in_str(t_cmds *cmds, char *str)
{
	t_get_env	*t_g;
	int			count;

	t_g = ft_calloc(sizeof(t_get_env), 1);
	t_g->result = NULL;
	t_g->len_str = ft_strlen(str);
	t_g->temp_var = ft_calloc(sizeof(char), t_g->len_str + 1);
	search_env(cmds, t_g, str);
	if (t_g->trigger == 1)
	{
		t_g->temp_var[t_g->j] = '\0';
		if (ft_strcmp(t_g->temp_var, "?") == 0)
			t_g->result = ft_itoa(cmds->exit_code.code);
		else
			t_g->result = getvarenv(cmds, t_g->temp_var);
		if (t_g->result != NULL)
			t_g->count = t_g->count + ft_strlen(t_g->result);
	}
	if (t_g->temp_var != NULL)
		free(t_g->temp_var);
	if (t_g->result != NULL)
		free(t_g->result);
	count = t_g->count;
	free(t_g);
	return (count);
}

int	has_dolar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
