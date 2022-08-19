#!/bin/bash

./cleaner.sh
bison -v --debug --defines=y.tab.h -Wconflicts-sr 1805010.y
echo 'Cooked bison 😵‍💫'
g++ -w -c -o y.o 1805010.tab.c
echo 'Bison object file compiled 😍'
flex 1805010.l
echo 'Lexxer cooked 🍪'
g++ -w -c -o l.o lex.yy.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Lexer object file compiled ╰(*°▽°*)╯'
g++ y.o l.o -lfl -o scanner
echo 'Scanner compiled! Generating code... 🚀'
./scanner input.c
echo "Code generation complete! Running optimization...⚙️"
g++ optimize.cpp -o optimize
./optimize
echo "Optimization complete! Cleaning up...🧹"
rm -f optimize
./cleaner.sh
echo "Please refer to code.asm and optimized_code.asm 🍔"
