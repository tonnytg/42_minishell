/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_strategy(t_cmds *cmds)
{
	printf("[run_strategy] - run strategy: %d\n", cmds->strategy);
	printf("[run_strategy] - run my strategy: %s\n", cmds->current->type);
	if (cmds->current->position == HEAD)
	{
		printf("[run_strategy] - Head\n");
	}
	else if (cmds->current->position == MID)
	{
		printf("[run_strategy] - Mid\n");
	}
	else if (cmds->current->position == TAIL)
	{
		printf("[run_strategy] - Tail\n");
	}
	else
	{
		printf("[run_strategy] - Unknown\n");
	}

}

void print_report(t_cmds *cmds, t_strategy *s)
{
	printf("cmd_list: %p\n", cmds->cmd_list);
	printf("[set_strategy] - c_pipe: %d\n", s->c_pipe);
	printf("[set_strategy] - c_dgreat: %d\n", s->c_dgreat);
	printf("[set_strategy] - c_great: %d\n", s->c_great);
	printf("[set_strategy] - c_dless: %d\n", s->c_dless);
	printf("[set_strategy] - c_less: %d\n", s->c_less);
	printf("[set_strategy] - c_word: %d\n", s->c_words);
	printf("[set_strategy] - c_unknown: %d\n", s->c_unknown);
}

void report_cmd_types(t_cmds *cmds, t_strategy *s)
{
	t_cmd_node *actual;

	actual = cmds->cmd_list;
	while (actual != NULL)
	{
		if (ft_strcmp(actual->type, "PIPE") == 0)
			s->c_pipe++;
		else if (ft_strcmp(actual->type, "DGREAT") == 0)
			s->c_dgreat++;
		else if (ft_strcmp(actual->type, "GREAT") == 0)
			s->c_great++;
		else if (ft_strcmp(actual->type, "DLESS") == 0)
			s->c_dless++;
		else if (ft_strcmp(actual->type, "LESS") == 0)
			s->c_less++;
		else if (ft_strcmp(actual->type, "WORD") == 0)
			s->c_words++;
		else
			s->c_unknown++;
		actual = actual->next;
	}
}

void set_strategy(t_cmds *cmds)
{
	t_strategy *s;

	s = ft_calloc(1, sizeof(t_strategy));
	cmds->strategy = 0;

	report_cmd_types(cmds, s);

	cmds->strategy = 0;
	return ;
}