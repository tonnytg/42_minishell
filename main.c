#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Interface comum para todos os comandos, para um comando ser compátivel
// Ele deve atender essa premissa
typedef struct {
    const char* name;
    void (*execute)(const char*);
} Command;

// Adaptador para o comando "echo"
void echo_adapter(const char* arg)
{
    printf("%s\n", arg);
}

// Adaptador para o comando "pwd"
void pwd_adapter(const char* arg)
{
    char* dir = getcwd(NULL, 0);
    printf("%s\n", dir);
    free(dir);
}

// Lista de comandos suportados, sempre que adicionarmos um novo adaptador
// precisamos alimentar a lista e está pronto
Command commands[] = {
    {"echo", echo_adapter},
    {"pwd", pwd_adapter}
};

// Função para buscar o adaptador de um comando pelo nome
// função responsável por procurar qual foi o comando digitado e chamar suas funções
Command* find_command(const char* name)
{
    int i;
    int num_commands = sizeof(commands) / sizeof(Command);

    i = 0;
    while (i < num_commands)
    {
        if (strcmp(commands[i].name, name) == 0) {
            return &commands[i];
        }
        i++;
    }
    return NULL;
}

int main() {
    while (1)
    {
        printf("> ");
        char input[256];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // remove o caractere de nova linha

        char* command_name = strtok(input, " ");
        char* command_arg = strtok(NULL, "");

        Command* command = find_command(command_name);
        if (command == NULL) {
            printf("Comando não encontrado\n");
            continue;
        }

        command->execute(command_arg);
    }
    return 0;
}
