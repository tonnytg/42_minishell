/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initialize_here_doc_data(t_cmds *cmds, t_here_doc *data)
{
	char	**words;

	words = ft_split(cmds->current->next->phrase, ' ');
	if (words != NULL)
		data->eof_keyword = ft_strdup(words[0]);
	else
		data->eof_keyword = ft_strdup("EOF\n");
	data->total_size = 0;
	data->buffer_size = 1024;
	data->content = ft_calloc(data->buffer_size, sizeof(char));
	if (!data->content)
	{
		perror("[initialize_here_doc_data] - Error allocating memory");
		exit(EXIT_FAILURE);
	}
	data->content[data->total_size] = '\0';
	free_arr(words);
}

void	read_here_doc(t_here_doc *data)
{
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		data->bytes_read = read(STDIN_FILENO,
				data->buffer, sizeof(data->buffer));
		if (strncmp(data->buffer, data->eof_keyword,
				ft_strlen(data->eof_keyword)) == 0)
			break ;
		if (data->total_size + data->bytes_read >= data->buffer_size)
		{
			data->buffer_size *= 2;
			data->content = ft_calloc(data->buffer_size, sizeof(char));
			if (!data->content)
				exit(EXIT_FAILURE);
		}
		ft_memcpy(data->content + data->total_size,
			data->buffer, data->bytes_read);
		data->total_size += data->bytes_read;
	}
	if (data->bytes_read == -1)
	{
		perror("[read_here_doc] - Error reading from stdin");
		exit(EXIT_FAILURE);
	}
	data->content[data->total_size] = '\0';
}

void	write_here_doc(t_here_doc *data, int file_descriptor)
{
	data->bytes_written = write(file_descriptor,
			data->content, ft_strlen(data->content));
	if (data->bytes_written == -1)
	{
		perror("[write_here_doc] - Error writing to file descriptor");
		exit(EXIT_FAILURE);
	}
}

void	cleanup_here_doc_data(t_here_doc *data)
{
	free(data->eof_keyword);
	free(data->content);
}

void	here_doc(t_cmds *cmds)
{
	t_here_doc	*data;

	data = ft_calloc(1, sizeof(t_here_doc));
	initialize_here_doc_data(cmds, data);
	read_here_doc(data);
	write_here_doc(data, cmds->current->fd[1]);
	close(cmds->current->fd[1]);
	cleanup_here_doc_data(data);
	cmds->exit_code.code = 0;
	free(data);
}
