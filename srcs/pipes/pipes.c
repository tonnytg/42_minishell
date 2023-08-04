/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(t_cmds *cmds, char *str)
{
	int	i;
	int	count_pipe;

	i = 0;
	count_pipe = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '\"')
			&& cmds->is_quote_opened == 0)
			cmds->is_quote_opened = 1;
		if ((str[i] == '\'' || str[i] == '\"')
			&& cmds->is_quote_opened == 1)
			cmds->is_quote_opened = 0;
		if (str[i] == '|' && cmds->is_quote_opened == 0)
			count_pipe++;
		i++;
	}
	return (count_pipe);
}

void	open_pipe(t_cmds *cmds)
{
	t_cmd_node	*current;

	current = cmds->cmd_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->type, "WORD") != 0)
		{
			if (pipe(current->fd) < 0)
				exit (write (1, "[open_pipe] - Pipe error\n", 12));
			current->fd_is_active = 1;
		}
		printf("[open_pipe] - Redirect has fd status: %d\n", current->fd_is_active);
		current = current->next;
	}
}

void	connect_nodes_with_pipes(t_cmds *cmds)
{
	t_cmd_node	*current;
	int			count;

	open_pipe(cmds);
	count = 0;
	current = cmds->cmd_list;
	cmds->current = current;
	printf("start redirect analysis\n");
	while (current != NULL)
	{
		printf("[%d] ----- Start -----\n", count);

		// [1] - HEAD - WORD
		if (current->prev == NULL
			&& current->next != NULL
			&& ft_strcmp(current->next->type, "WORD") != 0)
		{
			// Inicio saber quando é Nó antes do File Descriptor
			printf("[1] - Start Head Word\n");
			current->position = HEAD;
			current->fd_ptr_input = NULL;
			current->fd_ptr_output = current->next->fd;
			printf("[1] - Word fd is active: %d\n", current->fd_is_active);
			printf("[1] - Word file descriptor input ptr: %p\n", current->fd_ptr_input);
			printf("[1] - Word file descriptor output ptr: %p\n", current->fd_ptr_output);
			printf("[1] - Word file descriptor output val: %d\n", current->fd_ptr_output[1]);
		}

		// [2] - MIDDLE - REDIRECT
		// Configuração do Pipe e o próximo nó para receber os dados
		if (current->prev != NULL
			&& current->next != NULL
			&& ft_strcmp(current->type, "WORD") != 0)
		{
			printf("[2] - Start Middle Redirect\n");
			current->position = MID;
			if (ft_strcmp(current->type, "GREAT") == 0)
			{
				printf("[2] - Great\n");
				open_file(cmds, current->type);
			}
			if (ft_strcmp(current->type, "DGREAT") == 0)
			{
				printf("[2] - D Great\n");
				open_file(cmds, current->type);
			}
			if (ft_strcmp(current->type, "DLESS") == 0)
			{
				printf("[2] - DLESS\n");
				open_file(cmds, current->type);
			}
			if (ft_strcmp(current->type, "LESS") == 0)
			{
				printf("[2] - LESS\n");
				open_file(cmds, current->type);
			}
			printf("[2] - Redirect fd status: %d\n", current->fd_is_active);
			printf("[2] - Redirect Node Type: %s\n", current->type);
			printf("[2] - Redirect file descriptor input: %d\n", current->fd[0]);
			printf("[2] - Redirect file descriptor output: %d\n", current->fd[1]);
			printf("[2] - Redirect file descriptor file: %d\n", current->fd_file);
			printf("[2] - Redirect file descriptor file status: %d\n", current->fd_file_is_active);
			printf("[2] - Redirect file descriptor ptr: %p\n", current->fd);
			current->fd_ptr_input = NULL;
			current->fd_ptr_output = NULL;

			// [2] - MIDDLE - Redirect
			// Define o FD para o próximo nó que só pode ser WORD
			if (current->next->fd_is_active == 0
				&& ft_strcmp(current->next->type, "WORD") == 0)
			{
				printf("[2] - Next Node Settings ok\n");
				current->next->fd_ptr_input = current->fd;
				current->next->fd_ptr_output = NULL;
			}
		}

		// [3] - MIDDLE WORD
		// Configuração do Nó WORD somente MIDDLE // echo a b | grep b | tr -d " "
		if (current->prev != NULL
			&& ft_strcmp(current->prev->type, "WORD") == 0 // TODO: Verificar se tem erro
			&& current->next != NULL
			&& ft_strcmp(current->type, "WORD") == 0)
		{
			printf("[3] - Start Middle Word\n");
			current->position = MID;
			if (current->fd_ptr_output == NULL)
			{
				if (current->next != NULL
					&& ft_strcmp(current->next->type, "WORD") != 0)
				{
					printf("[3] - Next Pipe fd settings ok\n");
					current->fd_ptr_output = current->next->fd;
				}
			}
			printf("[3] - Word file descriptor input ptr: %p\n", current->fd_ptr_input);
			printf("[3] - Word file descriptor input val: %d\n", current->fd_ptr_input[0]);
			printf("[3] - Word file descriptor output ptr: %p\n", current->fd_ptr_output);
			printf("[3] - Word file descriptor output val: %d\n", current->fd_ptr_output[1]);
		}

		// [4] - TAIL - WORD
		if (current->next == NULL
			&& current->prev != NULL
			&& ft_strcmp(current->type, "WORD") == 0)
		{
			printf("[4] - Start Tail Word\n");
			current->position = TAIL;
			current->fd_ptr_output = NULL;
			printf("[4] - Word fd is active: %d\n", current->fd_is_active);
			printf("[4] - Word file descriptor input ptr: %p\n", current->fd_ptr_input);
			printf("[4] - Word file descriptor input val: %d\n", current->fd_ptr_input[0]);
			printf("[4] - Word file descriptor output ptr: %p\n", current->fd_ptr_output);
		}
		count++;
		current = current->next;
		cmds->current = current;
	}
}