/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:14:04 by caalbert          #+#    #+#             */
/*   Updated: 2023/06/08 19:47:10 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_adapter(t_cmds *cmds)
{
	int i;

	i = 0;
	while (cmds->envs != NULL)
	{
		printf("%s\n", cmds->envs[i]);
		i++;
	}
	return (0);
}
