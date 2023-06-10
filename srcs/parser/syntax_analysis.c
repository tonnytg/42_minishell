/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *word)
{
	if (ft_strncmp(word, "PIPE", 4) == 0)
		printf("minishell: syntax error near unexpected token `|'\n");
	else if (ft_strncmp(word, "GREAT", 5) == 0)
		printf("minishell: syntax error near unexpected token `>'\n");
	else if (ft_strncmp(word, "DGREAT", 6) == 0)
		printf("minishell: syntax error near unexpected token `>>'\n");
	else if (ft_strncmp(word, "LESS", 2) == 0)
		printf("minishell: syntax error near unexpected token `<'\n");
	else if (ft_strncmp(word, "DLESS", 3) == 0)
		printf("minishell: syntax error near unexpected token `<<'\n");
	else
		printf("minishell: syntax error near unexpected token `newline'\n");
}

int	check_lexical_errors(char **lexical_line)
{
	int	i;

	i = 0;
	while (lexical_line[i])
		i++;
	if (ft_strncmp(lexical_line[0], "PIPE", 4) == 0)
	{
		print_error("PIPE");
		return (-1);
	}
	if (ft_strncmp(lexical_line[i - 1], "WORD", 4) != 0)
	{
		if (ft_strncmp(lexical_line[i - 1], "PIPE", 4) == 0)
			print_error(lexical_line[i - 1]);
		else
			print_error(lexical_line[i - 1]);
		return (-1);
	}
	return (0);
}

void	syntax_analysis(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds->lexical[i])
	{
		printf("lexical[%d]: %s\n", i, cmds->lexical[i]);
		i++;
	}
	if (check_lexical_errors(cmds->lexical) == -1)
	{
		cmds->exit_code.code = 258;
		return ;
	}
	i = 0;
	while (cmds->lexical[i])
	{
		free(cmds->lexical[i]);
		i++;
	}
	free(cmds->lexical);
}
