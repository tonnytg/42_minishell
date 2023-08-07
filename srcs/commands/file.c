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

/* TODO: Read file */
void	read_file(t_cmds *cmds, char *file_name, int *write_in)
{
	char	*msg;
	char	buffer[1024];
	int		file;
	ssize_t	bytes_read;

	file = open(file_name, O_RDONLY);
	if (file < 1)
	{
		perror("error: file descriptor not opened!\n");
		cmds->exit_code.code = 1;
		exit(EXIT_FAILURE);
	}
	bytes_read = read(file, buffer, sizeof(buffer) - 1);
	if (bytes_read < 0)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	buffer[bytes_read] = '\0';
	msg = ft_strdup(buffer);
	if (!msg)
		return ;
	write(write_in[1], msg, ft_strlen(msg));
	free(msg);
}

/* TODO: Restore msg from fd */
char	*restore_msg_from_fd(t_cmds *cmds)
{
	char	*msg;
	char	buffer[1024];
	ssize_t	bytes_read;

	bytes_read = read(cmds->current->fd[0], buffer, sizeof(buffer) - 1);
	if (bytes_read < 0)
	{
		perror("read");
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	msg = ft_strdup(buffer);
	return (msg);
}

/* TODO: Save file */
void	save_file(t_cmds *cmds)
{
	ssize_t	bytes_escritos;
	char	*msg;

	msg = restore_msg_from_fd(cmds);
	if (!msg)
		return ;
	if (cmds->current->fd_file < 1)
	{
		perror("error: file descriptor not opened!\n");
		exit(EXIT_FAILURE);
	}
	bytes_escritos = write(cmds->current->fd_file, msg, ft_strlen(msg));
	if (bytes_escritos == -1)
	{
		perror("error: failed to write in file!\n");
		close(cmds->current->fd_file);
		exit(EXIT_FAILURE);
	}
	free(msg);
}

/* TODO: Maybe you can improve here */
void	open_file(t_cmds *cmds)
{
	char	*file_name;
	char	**temp;
	int		config_file;

	config_file = 0;
	temp = ft_split(cmds->current->next->phrase, ' ');
	file_name = ft_strdup(temp[0]);
	free_arr(temp);
	if (cmds->current->file_type == CREATE)
		config_file = O_TRUNC | O_WRONLY | O_CREAT;
	if (cmds->current->file_type == APPEND)
		config_file = O_APPEND | O_WRONLY | O_CREAT;
	if (config_file == 0)
		cmds->current->fd_file = open(file_name, O_RDONLY);
	else
		cmds->current->fd_file = open(file_name, config_file, 0644);
	if (cmds->current->fd_file < 0)
	{
		perror("open file");
		return ;
	}
	if (cmds->current->fd_file > 0)
		cmds->current->fd_file_is_active = 1;
	free(file_name);
}

/* TODO: Create file descriptor for file */
void	create_fd_file(t_cmds *cmds)
{
	if (ft_strcmp(cmds->current->type, "DGREAT") == 0)
	{
		cmds->current->file_type = APPEND;
	}
	else if (ft_strcmp(cmds->current->type, "GREAT") == 0)
	{
		cmds->current->file_type = CREATE;
	}
	else if (ft_strcmp(cmds->current->type, "LESS") == 0)
	{
		cmds->current->file_type = READ;
	}
	else if (ft_strcmp(cmds->current->type, "DLESS") == 0)
	{
		return ;
	}
	open_file(cmds);
}
