#!/bin/bash

ERRORS_DIR="./errors"
ERRORS_LOG="$ERRORS_DIR/errors.log"
MINISHELL="./minishell"
MAKEFILE_FLAGS="-Wall -Wextra -Werror"
FLAGS=( "invalid compilation" "crash" "incomplete work" )

mkdir -p $ERRORS_DIR
rm -f $ERRORS_LOG

validate_output() {
    CMD="$1"
    EXPECTED="$2"
    OUTPUT=$(./minishell -c "$CMD")
    if [[ "$OUTPUT" != "$EXPECTED" ]]; then
        echo "Error: Command [$CMD] Expected [$EXPECTED], Got [$OUTPUT]" >> $ERRORS_LOG
    fi
}

run_with_valgrind() {
    CMD="$1"
    valgrind --log-file=valgrind.log --suppressions=readline.supp $MINISHELL -c "$CMD"
    if grep -q "ERROR SUMMARY: 0 errors" valgrind.log; then
        echo "Error with command [$CMD] under Valgrind." >> $ERRORS_LOG
    fi
}

# Verificando flags de compilação
MAKE_OUTPUT=$(make -n)
if [[ $MAKE_OUTPUT != *"$MAKEFILE_FLAGS"* ]]; then
    echo ${FLAGS[0]} >> $ERRORS_LOG
fi

# Verificando se compila sem erros
if ! make > /dev/null 2>>$ERRORS_LOG; then
    echo ${FLAGS[1]} >> $ERRORS_LOG
fi

# Testes básicos
run_with_valgrind "/bin/ls"
run_with_valgrind " "
run_with_valgrind "\t"

# Testando echo com e sem argumentos
run_with_valgrind "echo"
run_with_valgrind "echo Hello"
run_with_valgrind "echo -n Hello"

# Testando o comando exit
run_with_valgrind "exit"
run_with_valgrind "exit 0"
run_with_valgrind "exit 1"

# Testando o valor de retorno com echo $?
run_with_valgrind "/bin/ls; echo $?"
run_with_valgrind "bin/Is filethatdoesntexist; echo $?"
run_with_valgrind "expr $? + $?"

# Testando ctrl+C, ctrl+\ e ctrl+D em prompt vazio e com texto

run_with_valgrind "echo -n ''; ctrl+C"
run_with_valgrind "echo -n ''; ctrl+\\"
run_with_valgrind "echo -n 'Some text'; ctrl+C"
run_with_valgrind "echo -n 'Some text'; ctrl+\\"

# Testando comandos com aspas duplas e simples
run_with_valgrind "echo \"Hello World\""
run_with_valgrind "echo 'Hello World'"

# Testando env e variáveis de ambiente
run_with_valgrind "env"
run_with_valgrind "export NEW_VAR=value"
run_with_valgrind "unset NEW_VAR"
run_with_valgrind "env | grep NEW_VAR"

# Testando cd e pwd
run_with_valgrind "cd /tmp"
run_with_valgrind "pwd"
run_with_valgrind "cd ' '"
run_with_valgrind "pwd"
run_with_valgrind "cd ."
run_with_valgrind "pwd"

# Testando comandos com caminho relativo
run_with_valgrind "./some-relative-command"

# Testando comandos sem path
run_with_valgrind "ls"
run_with_valgrind "unset PATH"
run_with_valgrind "ls"
run_with_valgrind "export PATH=/usr/bin:/bin"
run_with_valgrind "ls"

# Testando redirecionamentos
run_with_valgrind "echo Hello > output.txt"
run_with_valgrind "echo World >> output.txt"
run_with_valgrind "cat < output.txt"

# Testando pipes
run_with_valgrind "cat output.txt | grep Hello"
run_with_valgrind "ls non_existent_file | grep error"

# Testando histórico e buffer
run_with_valgrind "echo Previous command"

# Testando comandos inválidos
run_with_valgrind "non_existent_command"

# Testando variáveis de ambiente em echo
run_with_valgrind "echo $USER"
run_with_valgrind "echo \"Hello $USER\""

echo "Teste a reação a ctrl+C enquanto cat está esperando input:"
run_with_valgrind "cat"

echo "Teste a reação a ctrl+\\ enquanto cat está esperando input:"
run_with_valgrind "cat"

echo "Teste a reação a ctrl+D enquanto cat está esperando input:"
run_with_valgrind "cat"

echo "Teste a reação a ctrl+C enquanto grep está esperando input:"
run_with_valgrind "grep 'alguma coisa'"

echo "Testando comandos com aspas duplas que contêm espaços e variáveis de ambiente:"
run_with_valgrind "echo \"Hello $USER World\""

echo "Testando comandos com aspas simples que contêm espaços:"
run_with_valgrind "echo 'Hello World'"

echo "Testando variáveis de ambiente, espaços em branco, pipes e redirecionamentos dentro de aspas simples:"
run_with_valgrind "echo 'Hello $USER | cat > output.txt'"

echo "Testando a interpretação da variável de ambiente com echo:"
run_with_valgrind "echo $USER"

echo "Testando a interpretação de variáveis dentro de aspas duplas:"
run_with_valgrind "echo \"Meu nome de usuário é $USER\""

echo "Testando a não-interpretação de variáveis dentro de aspas simples:"
run_with_valgrind "echo 'Meu nome de usuário é $USER'"

echo "Testando um comando longo com muitos argumentos:"
long_command="echo "
for i in $(seq 1 1000); do
    long_command+="$i "
done
run_with_valgrind "$long_command"

echo "Testando redirecionamento simples:"
run_with_valgrind "echo 'teste' > temp_output.txt"

echo "Testando redirecionamento duplo (append):"
run_with_valgrind "echo 'teste 2' >> temp_output.txt"

echo "Testando combinações de pipes e redirecionamentos:"
run_with_valgrind "cat temp_output.txt | grep 'teste' | sort > sorted_output.txt"

echo "Testando o comando 'cat | cat | ls':"
run_with_valgrind "echo 'teste' | cat | cat | ls"

echo "Criando um arquivo temporário lol.c para o teste:"
echo "#include <stdio.h>" > lol.c
echo "int main() { printf(\"Hello, World!\\n\"); return 0; }" >> lol.c

echo "Testando o comando 'echo \"cat lol.c | cat > lol.c\"':"
run_with_valgrind "echo \"cat lol.c | cat > lol.c\""

echo "Criando diretórios e arquivos de teste para a checagem do PATH:"
mkdir -p dir1 dir2
echo "echo 'Estou na dir1'" > dir1/testpath.sh
echo "echo 'Estou na dir2'" > dir2/testpath.sh
chmod +x dir1/testpath.sh dir2/testpath.sh

echo "Testando a ordem de busca do PATH (deve mostrar 'Estou na dir1'):"
run_with_valgrind "PATH=$(pwd)/dir1:$(pwd)/dir2 testpath.sh"

echo "Alterando a ordem de busca do PATH (deve mostrar 'Estou na dir2'):"
run_with_valgrind "PATH=$(pwd)/dir2:$(pwd)/dir1 testpath.sh"

echo "Limpando arquivos e diretórios de teste:"
rm -rf dir1 dir2 lol.c temp_output.txt sorted_output.txt


# Verificando se há erros
if [ -s $ERRORS_LOG ]; then
    echo "Houve erros durante os testes. Verifique $ERRORS_LOG para detalhes."
else
    echo "Todos os testes passaram com sucesso!"
fi
