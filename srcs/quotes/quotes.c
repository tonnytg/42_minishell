/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/07/02 12:43:45 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_single_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	is_double_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_single_quotes(t_cmds *cmds)
{
	t_cmd_node	*node;
	char		*new_value;

	node = cmds->current;
	new_value = remove_string(node->full_args, '\'');
	return (new_value);
}

char	*remove_double_quotes(t_cmds *cmds)
{
	t_cmd_node	*node;
	char		*new_value;

	node = cmds->current;
	new_value = remove_string(node->full_args, '\"');
	return (new_value);
}

int	check_quotes(t_cmds *cmds)
{
	int	i;
	int	count_simple_quotes;
	int	count_double_quotes;

	i = 0;
	count_simple_quotes = 0;
	count_double_quotes = 0;
	if (cmds->input->datacpy == NULL)
		return (0);
	while (cmds->input->datacpy[i] != '\0')
	{
		if (cmds->input->datacpy[i] == '\'')
			count_simple_quotes++;
		if (cmds->input->datacpy[i] == '\"')
			count_double_quotes++;
		i++;
	}
	if (count_simple_quotes % 2 != 0 || count_double_quotes % 2 != 0)
	{
		printf("Error: quotes not closed\n");
		return (1);
	}
	if (count_simple_quotes > 0 || count_double_quotes > 0)
		cmds->has_quote = 1;
	return (0);
}
