#!/bin/bash

function tests() {
  echo "Start Unit Commands Tests"
  make debug
  COMMAND="exit1"
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
exit
EOF

  COMMAND="exit2"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
exit 1
EOF

  export COMMAND="exit3"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
EOF

  export COMMAND="exit4"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
EOF

  export COMMAND="exit5"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
exit teste
EOF

  export COMMAND="echo1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
echo a b
exit
EOF

  export COMMAND="echo2"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
echo a b
echo "a b"
echo 'a b'
echo $PWD
echo $PWD $PWD
echo $PWD $PWD $PWD
echo $HOME $PWD $SHLVL
echo '$HOME $PWD $SHLVL'
echo "$HOME $PWD $SHLVL"
EOF

  export COMMAND="mkdir1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
mkdir p
exit
EOF

  export COMMAND="cd1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
cd p
exit
EOF

  export COMMAND="pwd1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
pwd
exit
EOF

  export COMMAND="rm1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
rm -r p
exit
EOF

  export COMMAND="env1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
env
exit
EOF

  export COMMAND="export1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
export
exit
EOF

  export COMMAND="export2"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
export NAME="Antonio"
exit
EOF

  export COMMAND="export3"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
export NAME="Antonio"
export | grep NAME
exit
EOF

  export COMMAND="unset1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
export NAME="Antonio"
export | grep NAME
unset NAME
export | grep NAME
exit
EOF

  export COMMAND="path1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
/bin/ls
exit
EOF

  export COMMAND="path2"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.txt 2>&1 << EOF
/bin/ls
exit
EOF
}

function deleteTests() {
  rm -rf valgrind_output_*
}

if [ "$1" == "test" ]; then
  tests
elif [ "$1" == "rm" ]; then
  deleteTests
fi