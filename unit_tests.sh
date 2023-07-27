#!/bin/bash

clear;
echo "Start Test - `date`"

echo "[``]  - echo a b"
make va << EOF
echo a b
exit
EOF
echo $?

make va << EOF