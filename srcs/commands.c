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

char **split_path(char *path)
{
	char **array_path;
	int i = 0;

	array_path = ft_split(path, ':');
	while (array_path[i])
	{
		printf("%s\n", array_path[i]);
		i++;
	}
	return (array_path);
}

/* print variable PATH of envp
 https://github.com/LacrouxRaoni/minishell/blob/master/sources/execs/validate_path.c
*/
int	check_path(t_cmds *cmds)
{
	char	**path;
	int		i;
	char	*pathComplete;
	int		return_access;
	char	*name;

	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i])
	{
		name = ft_strjoin("/", cmds->cmd_finded->name); // TODO: desacoplar do finden_cmd
		pathComplete = ft_strjoin(path[i], name);
		return_access = access(pathComplete, F_OK);
		if (return_access == 0)
		{
			printf("Comando encontrado em: %s\n", pathComplete);
			return (0);
		}
		i++;
	}
	printf("Comando Não encontrado em: %s\n", pathComplete);
	return (-1);
}

void	organize_commands(t_cmds *cmds)
{
	t_cmd_node *current = cmds->cmd_list;

	check_path(cmds);

	int prev_pipe[2] = {-1, -1}; // Descritores de arquivo do pipe anterior

	while (current != NULL) {

		int curr_pipe[2]; // Descritores de arquivo do pipe atual

		// Cria um novo pipe
		if (pipe(curr_pipe) == -1)
		{
			perror("pipe");
			exit(1); // TODO: Da leak se acontecer
		}

		pid_t pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			exit(1); // TODO: Solve this I can't exit here, create leak
		} else if (pid == 0)
		{
			printf("Deu errado, entrou aqui!\n");
			printf("Não sei para que serve isso, dei exit!\n");
			exit(0); // TODO: Gera Leak
		} else
		{
			// Executa o comando do nó atual
			char *command_path = "/usr/bin/ls";
			char *my_args[] = {"ls","/app", NULL};

			printf("[Start] Run comando execve:\n");
			int retorno = execve(command_path, my_args, NULL); // Só posso executar esse comando quando ele não é um builtin
			printf("retorno: %d\n", retorno);
			if ( retorno < 0)
			{
				printf("Deu ruim ao chamar o execev!\n");
				perror("execve falhou");
			}
			printf("[Finish] Run comando execve:\n");
			// Fecha o descritor de arquivo de escrita do pipe atual
			close(curr_pipe[1]);

			// Fecha o descritor de arquivo de leitura do pipe anterior
			if (prev_pipe[0] != -1)
			{
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
