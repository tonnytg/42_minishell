#!/bin/bash

function tests() {
  echo "Start Unit Commands Tests"
  make debug >> /dev/null

#------ Commands below ------
  export COMMAND="invalidCommand"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
laranja
pera
exit
EOF

  export COMMAND="exit1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
exit
EOF

  export COMMAND="exit2"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
exit
EOF

  export COMMAND="exit3"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
exit 1
EOF

  export COMMAND="exit4"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
exit  $PWD
EOF

  export COMMAND="exit5"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
exit a
EOF

  export COMMAND="exit6"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
mkdir p
mkdir p
exit $?
EOF

  export COMMAND="echo1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
echo a b
exit
EOF

  export COMMAND="echo2"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
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
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
mkdir p
exit
EOF

  export COMMAND="cd1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
cd p
exit
EOF

  export COMMAND="pwd1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
pwd
exit
EOF

  export COMMAND="rm1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
rm -r p
exit
EOF

  export COMMAND="env1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
env
exit
EOF

  export COMMAND="env2"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
env
unset
env
exit
EOF

  export COMMAND="export1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
export
exit
EOF

  export COMMAND="export2"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
export NAME="Antonio"
exit
EOF

  export COMMAND="export3"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
export NAME="Antonio"
export | grep NAME
exit
EOF

  export COMMAND="export4"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
export NAME
export
exit
EOF

  export COMMAND="export5"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
export
unset
export
exit
EOF

  export COMMAND="unset1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
export NAME="Antonio"
export | grep NAME
unset NAME
export | grep NAME
exit
EOF

  export COMMAND="unset2"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
export NAME="Antonio"
export NAME2="Antonio2"
export
unset NAME2
export
exit
EOF

  export COMMAND="unset3"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
unset
exit
EOF

  export COMMAND="unset4"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
unset
unset
exit
EOF

  export COMMAND="path1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
/bin/ls
exit
EOF

  export COMMAND="path2"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
/bin/ls
exit
EOF
}

  export COMMAND="Environment1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
env
mkdir p
unset PATH
mkdir
export PATH="/usr/bin"
mkdir p
env
exit
EOF

  export COMMAND="Redirect1"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF

EOF

  export COMMAND="Redirect2"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
cat file.txt | grep b
EOF

  export COMMAND="Redirect3"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
cat file.txt | grep b | tr [:lower:] [:upper:]
EOF

  export COMMAND="Redirect4"
  echo $COMMAND
  valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp srcs/minishell > valgrind_output_${COMMAND}.log 2>&1 << EOF
cat file.txt | grep b | wc -l
EOF


function deleteTests() {
  rm -rf valgrind_output_*
  rm -rf reports
  rm -rf report.log
}

function ReportMove() {
  mkdir -p reports
  mv -v valgrind_output_* reports
}

function reportTests() {
  deleteTests
  tests
  for FILE in valgrind_output_*; do
    result=$(cat $FILE | grep -e ' at ' -a2 | wc -l)
    if [ $result -gt 0 ]; then
      echo file ${FILE} has ${result} errors >> report.log
    else
      echo file ${FILE} has no errors
    fi
  done
  ReportMove
}

if [ "$1" = "test" ]; then
  tests
elif [ "$1" = "rm" ]; then
  deleteTests
else
  reportTests
fi
