/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/07/02 12:43:45 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_keyboard_old(t_cmds *cmds)
{
	printf("\033[0;32mminishell: > \033[0;0m");
	if (fgets(cmds->input->data, sizeof(cmds->input->data), stdin) == NULL)
	{
		cmds->exit = 1;
		return ;
	}
	cmds->input->data[strcspn(cmds->input->data, "\n")] = 0;
	if (cmds->input->data[0] == '\0')
	{
		cmds->input->cmd_name = NULL;
		return ;
	}
	if (cmds->input->datacpy != NULL)
		free(cmds->input->datacpy);
	cmds->input->datacpy = ft_strdup(cmds->input->data);
	cmds->input->cmd_name = ft_strtok(cmds->input->data, " ", 1);
	cmds->input->cmd_args = ft_strtok(NULL, "", 0);
}

void	remove_empty(t_cmds *cmds)
{
	char	*clean_phrase;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean_phrase = ft_calloc(ft_strlen(cmds->input->datacpy) + 1, sizeof(char));
	while (cmds->input->datacpy[i] != '\0')
	{
		if (cmds->input->datacpy[i] != ' ')
		{
			clean_phrase[j] = cmds->input->datacpy[i];
			j++;
		}
		i++;
	}
	clean_phrase[j] = '\0';
	free(clean_phrase);
}

char	*remove_duplicate_spaces(char *input_string)
{
	int		i;
	int		j;
	char	*clean_phrase;

	i = 0;
	j = 0;
	clean_phrase = (char *)malloc(strlen(input_string) + 1);
	while (input_string[i] != '\0')
	{
		if (input_string[i] != ' ')
		{
			clean_phrase[j] = input_string[i];
			j++;
		}
		else if (input_string[i + 1] != ' ')
		{
			clean_phrase[j] = input_string[i];
			j++;
		}
		i++;
	}
	clean_phrase[j] = '\0';
	return (clean_phrase);
}

int	read_keyboard(t_cmds *cmds)
{
	printf("\033[0;32mminishell: > \033[0;0m");
	if (fgets(cmds->input->data, sizeof(cmds->input->data), stdin) == NULL)
	{
		cmds->exit = 1;
		return (1);
	}
	if (check_data_input(cmds) == NULL)
	{
		return (1);
	}
	cmds->input->data[strcspn(cmds->input->data, "\n")] = 0;
	if (cmds->input->data[0] == '\0')
	{
		cmds->input->cmd_name = NULL;
		return (1);
	}
	cmds->input->datacpy = remove_duplicate_spaces(cmds->input->data);
	cmds->input->cmd_name = ft_strtok(cmds->input->data, " ", 1);
	cmds->input->cmd_args = ft_strtok(NULL, "", 0);
	return (0);
}
