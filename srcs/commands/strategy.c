/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Redirect output to file */
void	run_strategy(t_cmds *cmds)
{
	printf("[run_strategy] - Started\n");
	if (ft_strcmp(cmds->current->type, "WORD") == 0)
	{
		printf("[run_strategy] - Strategy for word\n");
		if (cmds->current->next && cmds->current->strategy != S_RECEIVER)
		{
			printf("[run_strategy] - Set STDOUT_FILENO\n");
			dup2(cmds->current->fd_ptr_output[1], STDOUT_FILENO);
		}
		if (cmds->current->strategy == S_RECEIVER)
		{
			printf("[run_strategy] - S_RECEIVER\n");
			dup2(cmds->current->next->fd[0], STDIN_FILENO);
		}
	}
	else
		cmds->current->next->disabled = 1;
}

void here_doc(t_cmds *cmds)
{
	printf("[here_doc] - OK start get text from buffer and save in file\n");
	char buffer[1024];
	char *eof_keyword = ft_strdup("EOF\n");

	size_t totalSize = 0;
	size_t bufferSize = 1024;
	char *content = malloc(bufferSize); // Alocar memória inicial para o buffer

	while (1)
	{
		// Ler uma linha do teclado
		ssize_t bytesRead = read(STDIN_FILENO, buffer, 1024);
		if (bytesRead == -1)
		{
			perror("[here_doc] - Erro ao ler do teclado");
			exit(EXIT_FAILURE);
		}

		// Verificar se a palavra-chave foi digitada para encerrar a leitura
		if (ft_strncmp(buffer, eof_keyword, bytesRead) == 0)
		{
			break;
		}

		// Verificar se o buffer atual é suficiente para armazenar o novo conteúdo
		if (totalSize + bytesRead >= bufferSize)
		{
			bufferSize *= 2; // Dobrar o tamanho do buffer
			char *temp = realloc(content, bufferSize); // Realocar o buffer para o novo tamanho
			if (!temp)
			{
				perror("[here_doc] - Erro ao alocar memória");
				exit(EXIT_FAILURE);
			}
			content = temp;
		}

		// Copiar o conteúdo lido para o final do buffer acumulado
		memcpy(content + totalSize, buffer, bytesRead);
		totalSize += bytesRead;
	}

	// Adicionar o terminador de string ao final do conteúdo
	content[totalSize] = '\0';

	printf("[here_doc] - obtive:\n%s", content);

	// Escrever o conteúdo acumulado para o file descriptor
	ssize_t bytesWritten = write(cmds->current->fd[1], content, totalSize);
	if (bytesWritten == -1)
	{
		perror("[here_doc] - Erro ao escrever na saída padrão");
		exit(EXIT_FAILURE);
	}

	free(content); // Liberar a memória alocada dinamicamente

	cmds->current->prev->strategy = S_RECEIVER;
	cmds->current->disabled = 1;
	cmds->current->next->disabled = 1;
	printf("[here_doc] - END\n");
	return ;
}

void	set_strategy(t_cmds *cmds)
{
	t_strategy	*s;

	s = ft_calloc(1, sizeof(t_strategy));

	cmds->current = cmds->cmd_list;
	while (cmds->current != NULL)
	{

		if (ft_strcmp(cmds->current->type, "LESS") == 0)
		{
//			read_file(cmds, "file.txt", cmds->current->fd);
			char	*msg;
			char	buffer[1024];
			int		file;
			ssize_t	bytes_read;

			file = open("file.txt", O_RDONLY);
			if (file < 1)
			{
				perror("error: file descriptor not opened!\n");
				//exit(EXIT_FAILURE);
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
			write(cmds->current->fd[1], msg, ft_strlen(msg));
			close(cmds->current->fd[1]);
			free(msg);
			if (ft_strcmp(cmds->current->type, "WORD") != 0)
			{
				cmds->current->disabled = 1;
				cmds->current->next->disabled = 1;
			}
			cmds->current->prev->strategy = S_RECEIVER;
		}
		if (ft_strcmp(cmds->current->type, "DLESS") == 0)
		{
			printf("[set_strategy] - DLESS\n");
			here_doc(cmds);
			close(cmds->current->fd[1]);
		}
		cmds->current = cmds->current->next;
	}
	cmds->strategy = 0;
	free(s);
	printf("[set_strategy] - Saindo\n");
	return ;
}
