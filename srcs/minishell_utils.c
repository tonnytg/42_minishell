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

int	interactive_exit(t_cmds *cmds)
{
	if (cmds->exit)
	{
		printf("\n");
		return (1);
	}
	return (0);
}

void	free_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

int	count_string(char *str, char to_count)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == to_count)
			count++;
		i++;
	}
	return (count);
}

char	*remove_string(char *str, char to_remove)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (temp == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == to_remove)
			i++;
		else
		{
			temp[j] = str[i];
			j++;
			i++;
		}
	}
	temp[i] = '\0';
	return (temp);
}
