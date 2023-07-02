/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:22:05 by caalbert          #+#    #+#             */
/*   Updated: 2023/07/02 19:25:16 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	iteractive_exit(t_cmds *cmds)
{
	if (cmds->exit)
	{
		printf("\n");
		return (1);
	}
	return (0);
}
