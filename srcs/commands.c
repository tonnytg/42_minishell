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

void	organize_commands(t_cmds *cmds)
{
	t_cmd_node *actual;
	actual = cmds->cmd_list;
	while(actual != NULL)
	{
		printf("[%p] - %s \t %s\n", actual, actual->type, actual->phrase);
		actual = actual->next;
	}

	int fd[2];  // Descritores do pipe
	pid_t pid1, pid2;

	// Criar o pipe
	if (pipe(fd) == -1) {
		perror("Erro ao criar o pipe");
		exit(EXIT_FAILURE);
	}

	// Criar o primeiro processo filho
	pid1 = fork();
	if (pid1 == -1) {
		perror("Erro ao criar o primeiro processo filho");
		exit(EXIT_FAILURE);
	}

	if (pid1 == 0) {
		// Código do primeiro filho (executa 'echo "Name"')
		close(fd[0]);  // Fecha o descritor de leitura do pipe

		// Redireciona a saída padrão para o descritor de escrita do pipe
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		// Executa o comando 'echo "Name"'
		execlp("echo", "echo", "Name", NULL);
		perror("Erro ao executar o comando 'echo'");
		exit(EXIT_FAILURE);
	}

	// Criar o segundo processo filho
	pid2 = fork();
	if (pid2 == -1) {
		perror("Erro ao criar o segundo processo filho");
		exit(EXIT_FAILURE);
	}

	if (pid2 == 0) {
		// Código do segundo filho (executa 'tr [:lower:][:upper:]')
		close(fd[1]);  // Fecha o descritor de escrita do pipe

		// Redireciona a entrada padrão para o descritor de leitura do pipe
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);

		// Executa o comando 'tr [:lower:][:upper:]'
		execlp("tr", "tr", "[:lower:]", "[:upper:]", NULL);
		perror("Erro ao executar o comando 'tr'");
		exit(EXIT_FAILURE);
	}

	// Código do processo pai
	close(fd[0]);  // Fecha o descritor de leitura do pipe
	close(fd[1]);  // Fecha o descritor de escrita do pipe

	// Espera pela conclusão dos processos filhos
	wait(NULL);
	wait(NULL);


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
