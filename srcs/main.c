/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c.                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

// Interface comum para todos os comandos, para um comando ser compátivel
// Ele deve atender essa premissa
typedef struct {
    const char* name;
    void (*execute)(const char*);
} Command;

// Lista de comandos suportados, sempre que adicionarmos um novo adaptador
// precisamos alimentar a lista e está pronto
Command commands[] = {
    {"echo", echo_adapter},
    {"pwd", pwd_adapter}
};

// Função para buscar o adaptador de um comando pelo nome
// função responsável por procurar qual foi o comando digitado e chamar suas funções
Command*    find_command(const char* name)
{
    int i;
    int num_commands;
    
    num_commands = sizeof(commands) / sizeof(Command);

    i = 0;
    while (i < num_commands)
    {
        if (strcmp(commands[i].name, name) == 0)
        {
            return &commands[i];
        }
        i++;
    }
    return NULL;
}

int main()
{
    while (1)
    {
        char input[256];
        char* command_name;
        char* command_arg;

        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // remove o caractere de nova linha
        command_name = strtok(input, " ");
        command_arg = strtok(NULL, "");
        Command* command = find_command(command_name);
        if (command == NULL)
        {
            ft_printf("Comando não encontrado\n");
            continue ;
        }
        command->execute(command_arg);
    }
    return (0);
}
