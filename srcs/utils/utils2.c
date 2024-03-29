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

#include "../../includes/minishell.h"

int	count_all_len_in_arr(char **arr)
{
	int	letters;
	int	spaces;

	spaces = 0;
	letters = 0;
	while (arr[spaces] != NULL)
	{
		letters += ft_strlen(arr[spaces]);
		spaces++;
	}
	return (letters + spaces);
}

char	*concatenate_strings(char **arr, char c)
{
	char	*result;
	int		total_len;
	int		i;
	int		j;

	if (c == 0)
		c = ' ';
	total_len = count_all_len_in_arr((char **)arr);
	if (arr == NULL)
		return (NULL);
	result = ft_calloc(total_len + count_arr((char **)arr), sizeof(char));
	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		j += ft_strlcpy(&result[j], arr[i], total_len - j);
		result[j++] = c;
		i++;
	}
	result[--j] = '\0';
	return (result);
}

void	free_split(char **split_array)
{
	int	i;

	i = 0;
	if (split_array == NULL)
		return ;
	while (split_array[i] != NULL)
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}
