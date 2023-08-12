/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:16:46 by caalbert          #+#    #+#             */
/*   Updated: 2023/07/02 11:44:14 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_converted_word(t_cmds *cmds, t_env_convert *env_c)
{
	env_c->trigger = 0;
	env_c->word[env_c->w] = '\0';
	env_c->converted = get_env(cmds, env_c->word, 0);
	if (env_c->converted != NULL)
	{
		env_c->arr[env_c->a] = ft_strdup(env_c->converted);
		env_c->a++;
	}
	if (env_c->converted != NULL)
		free(env_c->converted);
	env_c->w = 0;
}

void	save_rest(t_env_convert *env_c)
{
	env_c->rest_active = 0;
	env_c->rest[env_c->r] = '\0';
	env_c->arr[env_c->a] = ft_strdup(env_c->rest);
	env_c->a++;
	env_c->r = 0;
}

void	search_for_word(t_cmds *cmds, t_env_convert *env_c, const char *value)
{
	if (value[env_c->i] == '$')
	{
		if (env_c->rest_active == 1)
			save_rest(env_c);
		env_c->trigger = 1;
		env_c->i++;
	}
	if (env_c->trigger == 1 && (value[env_c->i] == ':'
			|| value[env_c->i] == ' '))
		save_converted_word(cmds, env_c);
	if (env_c->trigger == 1)
	{
		env_c->word[env_c->w] = value[env_c->i];
		env_c->w++;
	}
}

void	search_for_rest(t_env_convert *env_c, const char *value)
{
	if (env_c->trigger == 0 && value[env_c->i] != '$')
	{
		if (value[env_c->i] != ':')
		{
			env_c->rest_active = 1;
			env_c->rest[env_c->r] = value[env_c->i];
			env_c->r++;
		}
		else if (value[env_c->i] == ':' && env_c->rest_active == 1)
			save_rest(env_c);
	}
}
