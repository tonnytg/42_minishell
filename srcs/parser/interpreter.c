/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/08/11 00:50:37 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (!s)
		return (NULL);
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

int	check_quote_phrase(char *phrase)
{
	int	i = 0;

	while (phrase[i] != '\0')
	{
		if (phrase[i] == '\"' || phrase[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	parse_values_args(t_cmds *cmds)
{
	int		i;
	char	**words;

	i = 0;
//	printf("[parse_values_args] - phrase: %s\n", cmds->current->phrase);
	int result = check_quote_phrase(cmds->current->phrase);
//	printf("[parse_values_args] - result: %d\n", result);
	if (result == 1)
	{
//		words = ft_split(cmds->current->phrase, '\0');
		char *new_word;
		new_word = malloc(sizeof(char) * 2);
		words = malloc(sizeof(char *) * 2);
		int k = 0;
		int i = 0;
		int j = 0;
		while (cmds->current->phrase[i] != '\0')
		{
			if (cmds->current->phrase[i] == ' ')
			{
				new_word[j] = '\0';
				i++;
				break ;
			}
			if (cmds->current->phrase[i] == '\"' || cmds->current->phrase[i] == '\'')
			{
				i++;
			}
			else
			{
				new_word[j] = cmds->current->phrase[i];
				j++;
				i++;
			}
		}
		words[k] = ft_strdup(new_word);
//		printf("NEW WORD: '%s'\n", new_word);
		k++;
		j = 0;
		while (cmds->current->phrase[i] != '\0')
		{
			if (cmds->current->phrase[i] == '\"' || cmds->current->phrase[i] == '\'')
			{
				i++;
			}
			else
			{
				new_word[j] = cmds->current->phrase[i];
				j++;
				i++;
			}
		}
		new_word[j] = '\0';
//		printf("NEW WORD: '%s'\n", new_word);
		words[k] = ft_strdup(new_word);
		k++;
		words[k] = NULL;
	}
	else
	{
		words = ft_split(cmds->current->phrase, ' ');
	}
	cmds->current->phrase_parsed = ft_calloc(sizeof(char *),
			count_arr(words) + 1);
	i = 0;
//	int j = 0;
	while (words[i] != NULL)
	{
//		printf("\n---\n");
//		printf("WORD CHEKING: '%s'\n", words[i]);
//		printf("WORD CHECKING SINGLE QUOTE: '%d'\n", is_single_quote(cmds->input->datacpy));
//		printf("WORD CHECKING DOUBLE QUOTE: '%d'\n", is_double_quote(cmds->input->datacpy));
//		printf("Word Parsed: '%s'\n", cmds->current->phrase_parsed[j]);
//		printf("\n---\n");
		if (ft_strncmp(words[i], "$", 1) == 0
			&& check_quote_phrase(words[i]) == 1)
		{
			printf("WORD MUST BE PARSED: '%s'\n", words[i]);
			if (ft_strncmp(words[i] + 1, "?", 1) == 0)
				cmds->current->phrase_parsed[i] = ft_itoa(cmds->exit_code.code);
			else
				cmds->current->phrase_parsed[i] = get_env(cmds, words[i], 1);
		}
		else if (ft_strncmp(words[i], ".", 1) == 0)
		{
			cmds->current->phrase_parsed[i] = parse_to_folder(cmds, words[i]);
			printf("1 - phrase_parsed: %s\n", cmds->current->phrase_parsed[i]);
		}
		else
		{
			cmds->current->phrase_parsed[i] = ft_strdup(words[i]);
//			printf("2 - phrase_parsed: %s\n", cmds->current->phrase_parsed[i]);
		}
		i++;
	}
//	free_arr(words);

//	t_cmd_node *temp3;
//	printf("---\n[3 prepare_phrase]---\n");
//	temp3 = cmds->cmd_list;
//	while (temp3 != NULL)
//	{
//		printf("phrase: %s\n", temp3->phrase);
//		printf("type: %s\n", temp3->type);
//		temp3 = temp3->next;
//	}

}

//void	prepare_phrase(t_cmds *cmds)
//{
//	char	**splited_phrase;
//	char	**temp;
//	char	*temp_str;
//	char	*temp_str1;
//	int		i;


//	t_cmd_node *temp1;
//	printf("---\n[1 prepare_phrase]---\n");
//	temp1 = cmds->cmd_list;
//	while (temp1 != NULL)
//	{
//		printf("phrase: %s\n", temp1->phrase);
//		printf("type: %s\n", temp1->type);
//		temp1 = temp1->next;
//	}

//	printf("Current Phrase: '%s'\n", cmds->current->phrase);
//	splited_phrase = ft_split(cmds->current->phrase, ' ');
//	temp = ft_calloc(sizeof(char *), count_arr(splited_phrase) + 1);
//	i = 0;
//	while (splited_phrase[i] != NULL)
//	{
//		temp_str = remove_string(splited_phrase[i], '\"');
//		temp[i] = remove_string(temp_str, '\'');
//		free(temp_str);
//		i++;
//	}
//	temp_str1 = concatenate_strings(temp, 0);
//	free(cmds->current->phrase);
//	cmds->current->phrase = ft_strdup(temp_str1);
//	free(temp_str1);
//	free_arr(temp);
//	free_arr(splited_phrase);

//	t_cmd_node *temp2;
//	printf("---\n[2 prepare_phrase]---\n");
//	temp2 = cmds->cmd_list;
//	while (temp2 != NULL)
//	{
//		printf("phrase: %s\n", temp2->phrase);
//		printf("type: %s\n", temp2->type);
//		temp2 = temp2->next;
//	}

//}

void	init_interpreter(t_cmds *cmds)
{
//	prepare_phrase(cmds);
	parse_values_args(cmds);
}
