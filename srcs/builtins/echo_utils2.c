/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c.                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo_arg_with_quotes(t_cmds *cmds)
{
	char	*new_arg;

	new_arg = NULL;
	if (is_single_quote(cmds->current->full_args))
	{
		new_arg = remove_single_quotes(cmds);
	}
	if (is_double_quote(cmds->current->full_args))
	{
		new_arg = remove_double_quotes(cmds);
	}
	if (new_arg == NULL)
		return (1);
	printf("%s\n", new_arg);
	free(new_arg);
	return (0);
}
