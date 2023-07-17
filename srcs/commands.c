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

void	open_pipe(t_cmds *cmds)
{
	printf("Abrindo o Pipe\n");
	if (pipe(cmds->fd) < 0)
		exit (write (1, "Pipe error\n", 12));
}

void	organize_commands(t_cmds *cmds)
{
	t_cmd_node	*actual;
	int			wstatus;
	char		*cp_phrase;
	char		*path;

	actual = cmds->cmd_list;
	if (actual->next != NULL)
		open_pipe(cmds); // cmds.fd[2];
	if (cmds->redirects_count > 0)
	{
		printf("Redirecionando\n"); // >> > << <
	}
	while(actual != NULL)
	{
		printf("[%p] - %s \t %s\n", actual, actual->type, actual->phrase); // WORD, PIPE, DLESS, LESS, DGREAT, GREAT
		if (ft_strcmp(actual->type, "WORD") == 0)
		{
			// Prepara as informações para executar o comando
			cp_phrase = malloc(sizeof(actual->phrase) + 1);		// prepara cp_phrase para receber o conteúdo
			ft_strlcpy(cp_phrase, actual->phrase, 100);			// Copia a frase para não se perder ao executar o ft_strtok
			actual->cmd_name = ft_strtok(cp_phrase, " ", 1);	// O comando que será executado
			actual->args = ft_split(actual->phrase, ' ');		// Todos os argumentos
			path = check_path(actual);							// Verifica se o comando existe no PATH

			actual->pid = fork();								// Cria um novo processo
			if (actual->pid == -1)								// Valda se ve algum erro
			{
				write(1, "Erro ao criar o processo filho\n", 31);
				printf("Erro ao criar o processo filho\n");
				perror("Erro ao criar o processo filho");
				exit(EXIT_FAILURE);
			}
			if (actual->pid == 0)								// Se for o processo filho execute o contexto
			{
				if (actual->prev == NULL)						// Se o processo é o primeiro, logo não recebe input
				{
					close(cmds->fd[0]);							// fecha o stdin
					dup2(cmds->fd[1], STDOUT_FILENO);			// copia o stdout
					close(cmds->fd[1]);							// fecha o stdout original
				}
				else if (actual->next == NULL)					// Se o processo é o ultimo, logo não emite output
				{
					close(cmds->fd[1]);							// fecha o stdout
					dup2(cmds->fd[0], STDIN_FILENO);			// copia o stdin
					close(cmds->fd[0]);							// fecha o stdin original
				}
				else											// Se o processo é o do meio, logo recebe e emite output
				{
					dup2(cmds->fd[0], STDIN_FILENO);			// copia o stdin
					close(cmds->fd[0]);							// fecha o stdin original
					dup2(cmds->fd[1], STDOUT_FILENO);			// copia o stdout
					close(cmds->fd[1]);							// fecha o stdout original
				}
				if (execve(path, actual->args, NULL) == -1)
				{
					perror("Erro ao executar o comando 'echo'");
					exit(EXIT_FAILURE);
				}
			}
			printf("pid: %d\n", actual->pid);
		}
		waitpid(actual->pid, &wstatus, 0);
		printf("status waitpid: %d\n", WEXITSTATUS(wstatus));
		actual = actual->next;

	}
	close(cmds->fd[0]);
	close(cmds->fd[1]);
	free(cp_phrase);
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
