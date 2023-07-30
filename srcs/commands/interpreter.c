/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	ft_free_arr(char **arr)
{
	char	**ptr;

	if (arr == NULL)
		return ;
	ptr = arr;
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(arr);
}

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

char	*concatenate_strings_old(const char **arr)
{
	char	*result;
	char	*temp;
	int		i;

	if (arr == NULL)
		return (NULL);
	result = ft_calloc(count_all_len_in_arr((char **)arr) + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		temp = ft_strjoin(result, arr[i]);
		result = ft_strjoin(temp, " ");
		i++;
	}
	result[ft_strlen(result) - 1] = '\0';
	free(temp);
	return (result);
}

char *concatenate_strings(const char **arr)
{
	char *result;
	int total_len;
	int i;
	int j;

	total_len = count_all_len_in_arr((char **)arr);
	if (arr == NULL)
		return NULL;
	result = ft_calloc(total_len + count_arr((char **)arr), sizeof(char));
	if (result == NULL)
		return NULL;
	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		j += ft_strlcpy(&result[j], arr[i], total_len - j);
		result[j++] = ' ';
		i++;
	}
	result[--j] = '\0';
	return (result);
}

int	parse_str_to_env(char **temp_str, char **converted_str, char *temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp_str[i] != NULL)
	{
		if (temp_str[i][0] == '$')
		{
			temp = remove_string(temp_str[i], '$');
			temp = remove_string(temp, '{');
			temp = remove_string(temp, '}');
			converted_str[j++] = ft_strdup(getenv(temp));
		}
		else
			converted_str[j++] = ft_strdup(temp_str[i]);
		i++;
		free(temp);
	}
	return (0);
}

char	*parse_string_to_envs(char *str)
{
	char	**temp_str;
	char	**converted_str;
	char	*value;
	char	*temp;

	temp_str = ft_split(str, ' ');
	converted_str = ft_calloc(count_arr(temp_str) + 1, sizeof(char *));
	temp = NULL;
	parse_str_to_env(temp_str, converted_str, temp);
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

char *get_env(char *str)
{
	char	*env_1;
	char	*env_2;
	char	*temp;
	char	*result;

	env_1 = ft_strdup(str);
	env_2 = remove_string(env_1, '$');
	free(env_1);
	env_1 = remove_string(env_2, '{');
	free(env_2);
	env_2 = remove_string(env_1, '}');

	temp = getenv(env_2);
	free(env_1);
	free(env_2);
	if (temp == NULL)
	{
		result = ft_strdup("");
		return (result);
	}
	result = ft_strdup(temp);
	return (result);
}

void	parse_values_args_old(t_cmds *cmds)
{
	char	**original_args;
	char	**args_ptr;
	int		i;

	original_args = ft_split(cmds->current->phrase, ' ');
	cmds->current->phrase_parsed = ft_calloc(sizeof(char *),
											 ft_count_arr(original_args) + 1);
	i = 0;
	args_ptr = original_args;
	while (*args_ptr != NULL)
	{
		if (ft_strncmp(*args_ptr, "$", 1) == 0)
		{
			if (ft_strncmp(*args_ptr + 1, "?", 1) == 0)
				cmds->current->phrase_parsed[i] = ft_itoa(cmds->exit_code.code);
			else
				cmds->current->phrase_parsed[i] = get_env(*args_ptr);
		}
		else
			cmds->current->phrase_parsed[i] = ft_strdup(*args_ptr);
		args_ptr++;
		i++;
	}
	ft_free_arr(original_args);
}

char *str_converted(char *str)
{
	char *temp;
	char *result;

	temp = ft_strdup(str);
	result = remove_string(temp, '\'');
	free(temp);
	return (result);
}

void	parse_values_args(t_cmds *cmds)
{
	int		i;
	char	**words;

	i = 0;
	words = ft_split(cmds->current->phrase, ' ');
	cmds->current->phrase_parsed = ft_calloc(sizeof(char *), count_arr(words) + 1);
	while (words[i] != NULL)
	{
		if (ft_strncmp(words[i], "$", 1) == 0 && is_single_quote(cmds->input->datacpy) == 0)
		{
			if (ft_strncmp(words[i] + 1, "?", 1) == 0)
				cmds->current->phrase_parsed[i] = ft_itoa(cmds->exit_code.code);
			else
				cmds->current->phrase_parsed[i] = get_env(words[i]);
		}
		else
			cmds->current->phrase_parsed[i] = ft_strdup(words[i]);
		i++;
	}
	free_arr(words);
}

void prepare_phrase(t_cmds *cmds)
{
	char **splited_phrase;
	char **temp;
	char *temp_str;

	splited_phrase = ft_split(cmds->current->phrase, ' ');
	temp = ft_calloc(sizeof(char *), count_arr(splited_phrase) + 1);
	int i = 0;
	while (splited_phrase[i] != NULL)
	{
		temp[i] = remove_string(splited_phrase[i], '\"');
		free(splited_phrase[i]);
		splited_phrase[i] = remove_string(temp[i], '\'');
		i++;
	}
	if (cmds->current->phrase != NULL)
	{
		free(cmds->current->phrase);
		cmds->current->phrase = NULL;
	}
	temp_str = concatenate_strings((const char **)splited_phrase);
	cmds->current->phrase = ft_strdup(temp_str);
	free(temp_str);
	free_arr(temp);
	free_arr(splited_phrase);
}

void	init_interpreter(t_cmds *cmds)
{
	if (cmds->current->phrase != NULL)
	{
		prepare_phrase(cmds);  // cmds->current->phrase
		parse_values_args(cmds); // cmds->current->phrase_parsed
	}
}

