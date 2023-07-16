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
char	*check_path(t_cmds *cmds)
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
		name = ft_strjoin("/", cmds->cmd_finded->name); // TODO: desacoplar do find_cmd
		pathComplete = ft_strjoin(path[i], name);
		return_access = access(pathComplete, F_OK);
		if (return_access == 0)
			return (pathComplete);
		i++;
	}
	return (NULL);
}

// https://github.com/LacrouxRaoni/minishell/blob/master/sources/execs/exec_child.c#L31
void	execute_child(t_cmd_node *node)
{
	// Executa o comando
	printf("Irei executar: %s\n", node->cmd_name);
	if (node->cmd_name != NULL) {
		execve(node->cmd_name, node->args, NULL);
		perror("execve error"); // TODO: Executa somente se der erro
		exit(1);
	}
	printf("End execute_child\n");
}

void	organize_commands(t_cmds *cmds)
{
//	t_cmd_node	*current = cmds->cmd_list;
	char		*result;
	int		wstatus;
	// https://github.com/LacrouxRaoni/minishell/blob/master/sources/execs/exec_cmds.c#L67C14-L67C14

	// TODO: Verificar se o primeiro comando é built-in

	// TODO: Se não for Built-in verificar se é um comando do sistema
	result = check_path(cmds);
	if (result == NULL) {
		printf("Command not found\n");
		return ;
	}
	/*

      HEAD (prev == NULL)      MID (prev && next != NULL)   TAIL (next == NULL)
	     echo "Name LastName" | cut -d " " -f1  |     tr [:lower:] [:upper:]
	     \				    /  \               /  \                       /
	      +---------+-------+   +-------+-----+    +-------------+-------+
	                |					  |                      |
	                v 			      	  v                      v
	         StdIn clone;			   StdIn open;				StdIn open;
	         StdOut open;			   StdOut open;			    StdOut close;
	 */

	t_cmd_node *actual;
	actual = cmds->cmd_list;
	int count = 0;
	while (actual != NULL)
	{
		printf("[2] Node Type: %s\n", actual->type);
		printf("[2] Node Command: %s\n", actual->cmd_name); // TODO: provalvelmente é NULL
		printf("[2] Node Pointer: %p\n", actual);
		actual->fd[0] = -1;
		actual->fd[1] = -1;
		actual->fd_in = -1;
		actual->fd_out = -1;
		if (actual->prev == NULL)
		{
			printf("[2] Node %p is Head\n", actual);
		}
		if (actual->next == NULL)
		{
			printf("[2] Node %p is Tail\n", actual);
		}
		if (actual->prev != NULL && actual->next != NULL)
		{
			printf("[2] Node %p is Mid\n", actual);
		}

		pipe(actual->fd);
		// fork: https://github.com/LacrouxRaoni/minishell/blob/master/sources/execs/exec_child.c#L98
		actual->pid = fork();
		if (actual->pid < 0)
		{
			perror("fork error");
			exit(1); // TODO: Solve this I can't exit here, create leak
		} else if (actual->pid == 0) {

			// exec: https://github.com/LacrouxRaoni/minishell/blob/master/sources/execs/exec_child.c#L102
			if (ft_strcmp(actual->type, "WORD") == 0) {
				printf("[%d] exec child\n", count);
				execute_child(actual);
			}
		}
		waitpid(actual->pid, &wstatus, 0);
		printf("Status PID: %d\n", WEXITSTATUS(wstatus));

		printf("---\n");
		count++;
		actual = actual->next;
	}

//
//
//	int prev_pipe[2] = {-1, -1}; // Descritores de arquivo do pipe anterior
//
//	int curr_pipe[2]; // Descritores de arquivo do pipe atual
//
//	// Cria um novo pipe
//	if (pipe(curr_pipe) == -1)
//	{
//		perror("pipe");
//		exit(1); // TODO: Da leak se acontecer
//	}
//
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("fork error");
//		exit(1); // TODO: Solve this I can't exit here, create leak
//	} else if (pid == 0)
//	{
//		printf("Eu sou o processo filho\n");
//		// Executa o comando do nó atual
//		char *command_path = "/usr/bin/ls";
//		char *my_args[] = {"ls","/app", NULL};
//
//		printf("[Start] Run comando execve:\n");
//		execve(command_path, my_args, NULL); // Só posso executar esse comando quando ele não é um builtin
//		// Se a execução chegar aqui, ocorreu um erro no execve
//		perror("execve falhou");
//		exit(1); // Deu erro
//	} else
//	{
//		// Aguarde o filho terminar
//		printf("Vou esperar o filho terminar\n");
//		wait(NULL); // TODO: Validar porque esperar o NULL
//		printf("Pronto, filho terminou\n");
//		int retorno = 1;
//		printf("retorno: %d\n", retorno);
//		if ( retorno < 0)
//		{
//			printf("Deu ruim ao chamar o execev!\n");
//			perror("execve falhou");
//		}
//		printf("[Finish] Run comando execve:\n");
//		// Fecha o descritor de arquivo de escrita do pipe atual
//		close(curr_pipe[1]);
//
//		// Fecha o descritor de arquivo de leitura do pipe anterior
//		if (prev_pipe[0] != -1)
//		{
//			close(prev_pipe[0]);
//		}
//
//		// Salva o descritor de arquivo de leitura do pipe atual para o próximo nó
//		current->fd_out = curr_pipe[0];
//		prev_pipe[0] = curr_pipe[0];
//	}
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
