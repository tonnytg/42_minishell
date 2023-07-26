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

char	*concatenate_strings(const char **arr)
{
	char	*result;
	int		i;
	int		offset;

	if (arr == NULL)
		return (NULL);
	result = (char *)malloc(count_arr((char **)arr) + 1);
	if (result == NULL)
		return (NULL);
	offset = 0;
	i = 0;
	while (arr[i] != NULL)
	{
		ft_strlcpy(result + offset, arr[i], strlen(arr[i]) + 1);
		offset += strlen(arr[i]);
		result[offset] = ' ';
		offset++;
		i++;
	}
	result[offset - 1] = '\0';
	return (result);
}

char	*parse_string_to_envs(char *str)
{
	char	**temp_str;
	char	**converted_str;
	char	*value;
	char	*temp;
	int		i;
	int		j;

	temp_str = ft_split(str, ' ');
	converted_str = ft_calloc(count_arr(temp_str) + 1, sizeof(char *));
	temp = NULL;
	i = 0;
	j = 0;
	while (temp_str[i] != NULL)
	{
		temp = remove_string(temp_str[i], '$');
		if (getenv(temp) != NULL)
			converted_str[j++] = ft_strdup(
					getenv(temp));
		else
			converted_str[j++] = ft_strdup(temp_str[i]);
		i++;
		free(temp);
	}
	value = concatenate_strings((const char **)converted_str);
	free_arr(converted_str);
	free_arr(temp_str);
	return (value);
}

int	echo_arg_with_quotes(t_cmds *cmds)
{
	char	*new_arg;
	char	*temp_arg;

	if (is_single_quote(cmds->current->full_args))
	{
		new_arg = remove_single_quotes(cmds);
	}
	if (is_double_quote(cmds->current->full_args))
	{
		new_arg = remove_double_quotes(cmds);
		temp_arg = parse_string_to_envs(new_arg);
		free(new_arg);
		new_arg = temp_arg;
		free(temp_arg);
	}
	if (new_arg == NULL)
		return (1);
	printf("%s\n", new_arg);
	free(new_arg);
	return (0);
}
