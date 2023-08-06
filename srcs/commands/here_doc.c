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

void	here_doc(t_cmds *cmds)
{
	char	buffer[1024];
	char	*eof_keyword;
	char	*content;
	char	*temp;
	ssize_t	bytes_read;
	size_t	total_size;
	size_t	buffer_size;
	ssize_t bytes_written;

	eof_keyword = ft_strdup("EOF\n");
	total_size = 0;
	buffer_size = 1024;
	content = malloc(buffer_size);
	while (1)
	{
		write(1, ">", 2);
		bytes_read = read(STDIN_FILENO, buffer, 1024);
		if (bytes_read == -1)
		{
			perror("[here_doc] - error to read default stdin");
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(buffer, eof_keyword, bytes_read) == 0)
			break;
		if (total_size + bytes_read >= buffer_size)
		{
			buffer_size *= 2;
			temp = realloc(content, buffer_size);
			if (!temp)
			{
				perror("[here_doc] - Erro ao alocar memória");
				exit(EXIT_FAILURE);
			}
			content = temp;
		}
		ft_memcpy(content + total_size, buffer, bytes_read);
		total_size += bytes_read;
	}
	content[total_size] = '\0';
	bytes_written = write(cmds->current->fd[1], content, total_size);
	if (bytes_written == -1)
	{
		perror("[here_doc] - Error to write in default stdout");
		exit(EXIT_FAILURE);
	}
	free(content);
	free(eof_keyword);
	return ;
}
