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

char	*concatenate_strings(const char **arr)
{
	char	*result;
	int		i;

	if (arr == NULL)
		return (NULL);
	result = ft_calloc(count_all_len_in_arr((char **)arr) + 1, sizeof(char *));
	if (result == NULL) {
		return (NULL);
	}
	i = 0;
	while (arr[i] != NULL)
	{
		result = ft_strjoin(result, arr[i]);
		result = ft_strjoin(result, " ");
		printf("[%d] - concatenate_strings: '%s' - len: %ld\n", i, result, ft_strlen(result));
		i++;
	}
	result[i + 1] = '\0';
	printf("resultado final: '%s'\n", result);
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
	temp = ft_strdup(value);
	free(value);
	free_arr(temp_str);
	free_arr(converted_str);
	return (temp);
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
		new_arg = ft_strdup(temp_arg);
		free(temp_arg);
	}
	if (new_arg == NULL)
		return (1);
	printf("%s\n", new_arg);
	free(new_arg);
	return (0);
}
