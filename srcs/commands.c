/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct Node {
	char *command;
	char **args;
	int input_fd;
	int output_fd;
	struct Node *next;
} Node;

void	organize_commands(t_cmds *cmds)
{
	t_cmd_node *current = cmds->cmd_list;

	int prev_pipe[2] = {-1, -1}; // Descritores de arquivo do pipe anterior

	while (current != NULL) {

		int curr_pipe[2]; // Descritores de arquivo do pipe atual

		// Cria um novo pipe
		if (pipe(curr_pipe) == -1) {
			perror("pipe");
			exit(1);
		}

		pid_t pid = fork();
		printf("pid: %d\n", pid);


		if (pid == -1) {
			perror("fork");
			exit(1);
		} else if (pid == 0) {
			// Fecha o descritor de arquivo de leitura do pipe atual
			close(curr_pipe[0]);

			// Redireciona o descritor de arquivo de leitura para o pipe anterior
			if (current->fd_in != -1) {
				dup2(current->fd_in, STDIN_FILENO);
				close(current->fd_in);
			}

			// Redireciona o descritor de arquivo de escrita para o pipe atual
			dup2(curr_pipe[1], STDOUT_FILENO);
			close(curr_pipe[1]);

			// Se o execve falhar, exibe o erro e sai
			perror("execve");
			exit(1);
		} else {

			// Executa o comando do nó atual
			char *command_path = "/usr/bin/ls";
			char *my_args[] = {"ls","/usr/sbin", NULL};
			printf("[Start] Run comando execve:\n");
			execve(command_path, my_args, NULL);
			printf("[Finish] Run comando execve:\n");

			printf("Else\n");
			// Fecha o descritor de arquivo de escrita do pipe atual
			close(curr_pipe[1]);

			// Fecha o descritor de arquivo de leitura do pipe anterior
			if (prev_pipe[0] != -1) {
				close(prev_pipe[0]);
			}

			// Salva o descritor de arquivo de leitura do pipe atual para o próximo nó
			current->fd_out = curr_pipe[0];
			prev_pipe[0] = curr_pipe[0];

			// Aguarde o filho terminar
			wait(NULL);

			current = current->next;
		}
	}
}

void	execute_cmd(t_cmds *cmds)
{
	//	if (cmds->cmd_finded->name) // value != NULL
	//	{
	//		cmds->exit_code.last_cmd = cmds->input->cmd_name; // what the last command ?
	//		cmds->exit_code.code = cmds->cmd_finded->execute(cmds); // run command and save return -> This line is the point!
	//	}
	organize_commands(cmds);
	cmds->exit_code.last_cmd = cmds->input->cmd_name;
	cmds->exit_code.code = 0;
	printf("Finish run command!\n");
}

void	set_commands(t_cmds *cmds)
{
	size_t		i;
	t_command	command_mapping[7];

	command_mapping[0] = (t_command){ECHO_BUILTIN, echo_adapter};
	command_mapping[1] = (t_command){CD_BUILTIN, cd_adapter};
	command_mapping[2] = (t_command){PWD_BUILTIN, pwd_adapter};
	command_mapping[3] = (t_command){EXPORT_BUILTIN, export_adapter};
	command_mapping[4] = (t_command){UNSET_BUILTIN, unset_adapter};
	command_mapping[5] = (t_command){ENV_BUILTIN, env_adapter};
	command_mapping[6] = (t_command){EXIT_BUILTIN, exit_adapter};
	cmds->num_cmds = sizeof(command_mapping) / sizeof(t_command);
	cmds->arr_cmds = malloc(sizeof(t_command) * cmds->num_cmds);
	i = 0;
	while (i < cmds->num_cmds)
	{
		cmds->arr_cmds[i].name = command_mapping[i].name;
		cmds->arr_cmds[i].execute = command_mapping[i].execute;
		i++;
	}
}
