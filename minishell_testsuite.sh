#!/bin/bash

ERRORS_DIR="./erros"
ERRORS_LOG="$ERRORS_DIR/log_erros.log"
MINISHELL="./minishell"
MAKEFILE_FLAGS="-Wall -Wextra -Werror"
FLAGS=( "compilação inválida" "crash" "trabalho incompleto" )

RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

mkdir -p $ERRORS_DIR
rm -f $ERRORS_LOG

validate_output() {
	CMD="$1"
	TEMP_SCRIPT=$(mktemp)
	echo "$CMD" > $TEMP_SCRIPT
	TEMP_EXPECTED=$(mktemp)
	TEMP_OUTPUT=$(mktemp)
	bash $TEMP_SCRIPT > $TEMP_EXPECTED 2>&1
	./minishell $TEMP_SCRIPT > $TEMP_OUTPUT 2>&1
	if ! diff $TEMP_EXPECTED $TEMP_OUTPUT &> /dev/null; then
		EXPECTED_CONTENT=$(cat $TEMP_EXPECTED)
		OUTPUT_CONTENT=$(cat $TEMP_OUTPUT)
		echo -e "${RED}Erro: Comando [$CMD]\nEsperado:\n$EXPECTED_CONTENT\nObteve:\n$OUTPUT_CONTENT${RESET}\n" >> $ERRORS_LOG
	else
		echo -e "${GREEN}[ OK ]${RESET} $CMD\n"
	fi
	rm $TEMP_EXPECTED $TEMP_OUTPUT $TEMP_SCRIPT
}

run_with_valgrind() {
	CMD="$1"
	valgrind --log-file=log_valgrind.log --suppressions=readline.supp $MINISHELL "$CMD"
	if grep -q "ERROR SUMMARY: 0 errors" log_valgrind.log; then
		echo -e "${RED}Erro com o comando [$CMD] sob Valgrind.${RESET}\n" >> $ERRORS_LOG
	else
		echo -e "${GREEN}[ OK ]${RESET}\n"
	fi
}

run_test() {
	CMD="$1"
	echo "Executando teste: $CMD"
	validate_output "$CMD"
	run_with_valgrind "$CMD"
}

MAKE_OUTPUT=$(make -n)
if [[ $MAKE_OUTPUT != *"$MAKEFILE_FLAGS"* ]]; then
	echo ${FLAGS[0]} >> $ERRORS_LOG
else
	echo -e "${GREEN}[ OK ]${RESET} Flags de compilação"
fi

if ! make > /dev/null 2>>$ERRORS_LOG; then
	echo ${FLAGS[1]} >> $ERRORS_LOG
else
	echo -e "${GREEN}[ OK ]${RESET} Compilação"
fi

run_test "/bin/ls"
run_test " "
run_test "\t"
run_test "echo"
run_test "echo Hello"
run_test "echo -n Hello"
run_test "exit"
run_test "exit 0"
run_test "exit 1"
run_test "/bin/ls; echo $?"
run_test "bin/Is filethatdoesntexist; echo $?"
run_test "expr $? + $?"
run_test "echo -n ''; ctrl+C"
run_test "echo -n ''; ctrl+\\"
run_test "echo -n 'Some text'; ctrl+C"
run_test "echo -n 'Some text'; ctrl+\\"
run_test "echo \"Hello World\""
run_test "echo 'Hello World'"
run_test "env"
run_test "export NEW_VAR=value"
run_test "unset NEW_VAR"
run_test "env | grep NEW_VAR"
run_test "cd /tmp"
run_test "pwd"
run_test "cd ' '"
run_test "pwd"
run_test "cd ."
run_test "pwd"
run_test "./some-relative-command"
run_test "ls"
run_test "unset PATH"
run_test "ls"
run_test "export PATH=/usr/bin:/bin"
run_test "ls"
run_test "echo Hello > output.txt"
run_test "echo World >> output.txt"
run_test "cat < output.txt"
run_test "cat output.txt | grep Hello"
run_test "ls non_existent_file | grep error"
run_test "echo Previous command"
run_test "non_existent_command"
run_test "echo $USER"
run_test "echo \"Hello $USER\""
# echo "Teste a reação a ctrl+C enquanto cat está esperando input:"
# run_test "cat"

# echo "Teste a reação a ctrl+\\ enquanto cat está esperando input:"
# run_test "cat"

# echo "Teste a reação a ctrl+D enquanto cat está esperando input:"
# run_test "cat"

# echo "Teste a reação a ctrl+C enquanto grep está esperando input:"
# run_test "grep 'alguma coisa'"

echo "Testando comandos com aspas duplas que contêm espaços e variáveis de ambiente:"
run_test "echo \"Hello $USER World\""

echo "Testando comandos com aspas simples que contêm espaços:"
run_test "echo 'Hello World'"

echo "Testando variáveis de ambiente, espaços em branco, pipes e redirecionamentos dentro de aspas simples:"
run_test "echo 'Hello $USER | cat > output.txt'"

echo "Testando a interpretação da variável de ambiente com echo:"
run_test "echo $USER"

echo "Testando a interpretação de variáveis dentro de aspas duplas:"
run_test "echo \"Meu nome de usuário é $USER\""

echo "Testando a não-interpretação de variáveis dentro de aspas simples:"
run_test "echo 'Meu nome de usuário é $USER'"

echo "Testando um comando longo com muitos argumentos:"
long_command="echo "
for i in $(seq 1 1000); do
	long_command+="$i "
done
run_test "$long_command"

echo "Testando redirecionamento simples:"
run_test "echo 'teste' > temp_output.txt"

echo "Testando redirecionamento duplo (append):"
run_test "echo 'teste 2' >> temp_output.txt"

echo "Testando combinações de pipes e redirecionamentos:"
run_test "cat temp_output.txt | grep 'teste' | sort > sorted_output.txt"

echo "Testando o comando 'cat | cat | ls':"
run_test "echo 'teste' | cat | cat | ls"

echo "Criando um arquivo temporário lol.c para o teste:"
echo "#include <stdio.h>" > lol.c
echo "int main() { printf(\"Hello, World!\\n\"); return 0; }" >> lol.c

echo "Testando o comando 'echo \"cat lol.c | cat > lol.c\"':"
run_test "echo \"cat lol.c | cat > lol.c\""

echo "Criando diretórios e arquivos de teste para a checagem do PATH:"
mkdir -p dir1 dir2
echo "echo 'Estou na dir1'" > dir1/testpath.sh
echo "echo 'Estou na dir2'" > dir2/testpath.sh
chmod +x dir1/testpath.sh dir2/testpath.sh

echo "Testando a ordem de busca do PATH (deve mostrar 'Estou na dir1'):"
run_test "PATH=$(pwd)/dir1:$(pwd)/dir2 testpath.sh"

echo "Alterando a ordem de busca do PATH (deve mostrar 'Estou na dir2'):"
run_test "PATH=$(pwd)/dir2:$(pwd)/dir1 testpath.sh"

echo "Limpando arquivos e diretórios de teste:"
rm -rf dir1 dir2 lol.c temp_output.txt sorted_output.txt

echo "Testando um comando longo com muitos argumentos:"
long_command="echo "
for i in $(seq 1 1000); do
	long_command+="$i "
done
run_test "$long_command"

if [ -s $ERRORS_LOG ]; then
	echo "Houveram erros durante os testes. Verifique $ERRORS_LOG para detalhes."
else
	echo "Todos os testes passaram com sucesso!"
fi
