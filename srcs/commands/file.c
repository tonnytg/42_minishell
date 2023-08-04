/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void save_file(t_cmds *cmds)
{
	printf("[save_file] - File descriptor is %d\n", cmds->current->fd_file);
	ssize_t	bytes_escritos;
	char *msg = "Hello World\n";

	bytes_escritos = write(cmds->current->fd_file, msg, ft_strlen(msg));
	if (bytes_escritos == -1)
	{
		perror("Erro ao escrever no arquivo");
		close(cmds->current->fd_file);
		exit(EXIT_FAILURE);
	}
	close(cmds->current->fd_file);
}

void create_fd_file(t_cmds *cmds)
{
	char *file_name;
	char **temp = ft_split(cmds->current->next->phrase, ' ');
	file_name = ft_strdup(temp[0]);
	cmds->current->next->disabled = 1; // TODO: Desabilita o nó pq ele não é mais necessário
	printf("[create_fd_file] - Saving file name: '%s'\n", file_name);
	if (cmds->current->file_type == CREATE)
	{
		cmds->current->fd_file = open(file_name, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if (cmds->current->fd_file < 0) {
			perror("open");
			return ;
		}
	}
	if (cmds->current->file_type == APPEND)
	{
		cmds->current->fd_file = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cmds->current->fd_file < 0) {
			perror("open");
			return ;
		}
	}
	if (cmds->current->file_type == READ)
	{
		cmds->current->fd_file = open(file_name, O_RDONLY);
		if (cmds->current->fd_file < 0)
		{
			perror("open");
			return ;
		}
	}
	if (cmds->current->fd_file > 0)
		cmds->current->fd_file_is_active = 1;

	save_file(cmds);
}

void	open_file(t_cmds *cmds, char *type)
{
	printf("open file fd in node %p\n", cmds);

	if (ft_strcmp(type, "DGREAT") == 0)
	{
		printf("[open_file] - File type is DGREAT\n");
		cmds->current->file_type = APPEND;
		create_fd_file(cmds);
	}

	if (ft_strcmp(type, "GREAT") == 0)
	{
		printf("[open_file] - File type is GREAT\n");
		cmds->current->file_type = CREATE;
		create_fd_file(cmds);
	}

	if (ft_strcmp(type, "LESS") == 0)
	{
		printf("[open_file] - File type is LESS\n");
		cmds->current->file_type = READ;
		create_fd_file(cmds);
	}

	if (ft_strcmp(type, "DLESS") == 0)
	{
		printf("[open_file] - File type is DLESS\n");
		printf("[open_file] - HERE_DOC\n");
	}
	printf("[create_fd_file] - Meu File Descriptor do file: %d\n", cmds->current->fd_file);
	printf("[create_fd_file] - Type File Descriptor: %d\n", cmds->current->file_type);
}