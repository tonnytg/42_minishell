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

void	echo_print_envs(char *word)
{
	char	*result;

	result = getenv(word);
	if (result != NULL)
		printf("%s ", result);
}

int	check_error(int open_bracket, char *result)
{
	if (open_bracket % 2 != 0)
	{
		printf(": bad substitution");
		free(result);
		return (1);
	}
	return (0);
}

char	*echo_extract_word(char *word)
{
	char	*result;
	int		open_bracket;
	int		i;
	int		j;

	i = 0;
	j = 0;
	open_bracket = 0;
	result = ft_calloc(ft_strlen(word) + 1, sizeof(char));
	while (word[i] != '\0')
	{
		if (word[i] == '{' || word[i] == '}')
			open_bracket++;
		if (word[i] != '$' && word[i] != '{' && word[i] != '}')
		{
			result[j] = word[i];
			j++;
		}
		i++;
	}
	result[i] = '\0';
	if (check_error(open_bracket, result))
		return (NULL);
	return (result);
}

int	echo_print_variables(t_cmds *cmds, char *word)
{
	int	exit_code;

	exit_code = 0;
	if (word != NULL)
	{
		if (ft_strcmp(word, "?") == 0)
			printf("%d ", cmds->exit_code.code);
		else
			echo_print_envs(word);
	}
	else
		exit_code = 1;
	return (exit_code);
}

int	echo_exec_print(t_cmds *cmds, int settings, char **words)
{
	int		i;
	char	*word;
	int		exit_code;

	i = 1;
	exit_code = 0;
	while (words[i] != NULL)
	{
		if (words[i][0] == '$')
		{
			word = echo_extract_word(words[i]);
			exit_code = echo_print_variables(cmds, word);
			free(word);
		}
		else
			printf("%s ", words[i]);
		i++;
	}
	if (settings != 1 && settings != 3)
		printf("\n");
	return (exit_code);
}
