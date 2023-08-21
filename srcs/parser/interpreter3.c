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

void	get_dolar_env_result(t_parse_2	*p2, char c)
{
	p2->var_name[0] = c;
	p2->var_name[1] = '\0';
	p2->end++;
}

void	save_command_name(t_cmds *cmds, t_parse_1 *p1)
{
	p1->words[p1->k] = ft_strdup(p1->command_name);
	free(p1->command_name);
	p1->k++;
	cmds->t_quote = 0;
}

int	trigger_quote(t_cmds *cmds, char c)
{
	if ((c == '\'' || c == '\"') && cmds->t_quote == 0)
		cmds->t_quote = 1;
	else if ((c == '\'' || c == '\"') && cmds->t_quote == 1)
		cmds->t_quote = 0;
	return (0);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (!s)
		return (NULL);
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
