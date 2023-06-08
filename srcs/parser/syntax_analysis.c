/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_analysis(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds->lexical[i])
	{
		printf("lexical[%d]: %s\n", i, cmds->lexical[i]);
		i++;
	}
	i = 0;
	while (cmds->lexical[i])
	{
		free(cmds->lexical[i]);
		i++;
	}
	free(cmds->lexical);
}
