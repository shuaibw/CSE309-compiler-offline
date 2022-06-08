/*
 * Created by 1805010
 * 27 May 2022
 * CSE310
 * Executable tested with valgrind-3.19.0 in WSL Ubuntu 20.04
 * g++ -g main.c -o main
 * valgrind --leak-check=yes ./main
 * */

//Comment/uncomment to toggle the effects
#define VERBOSE //Activate logs
#define FILEOUT //Redirect std::cout to file
#define FILEIN //Redirect std::cin to file

#include<iostream>
#include<fstream>
#include "SymbolTable.h"

int main() {
    #ifdef FILEIN
    std::ifstream in("../input.txt"); //remove ../ if executable is in same folder as input.txt
    std::cin.rdbuf(in.rdbuf());
    #endif

    #ifdef FILEOUT
    std::ofstream out("../output.txt"); //remove ../ if executable is in same folder as output.txt
    std::cout.rdbuf(out.rdbuf());
    #endif

    if (!std::cin) {
        std::cout << "Input stream ERROR" << std::endl;
        return 1;
    }
    size_t buckets;
    std::cin >> buckets;
    SymbolTable *symbolTable = new SymbolTable(buckets);
    std::string cmd, arg1, arg2;

    while (!std::cin.eof()) {
        std::cin >> cmd;
        if (cmd == "I") {
            std::cin >> arg1;
            std::cin >> arg2;
            symbolTable->insert(arg1, arg2);
        } else if (cmd == "L") {
            std::cin >> arg1;
            symbolTable->lookUp(arg1);
        } else if (cmd == "D") {
            std::cin >> arg1;
            symbolTable->remove(arg1);
        } else if (cmd == "P") {
            std::cin >> arg1;
            arg1 == "A" ? symbolTable->printAllScopes() : symbolTable->printCurrentScope();
        } else if (cmd == "S") {
            symbolTable->enterScope();
        } else if (cmd == "E") {
            symbolTable->exitScope();
        }
    }
    std::cout << "Done reading from user. Destroying all tables..." << std::endl;
    delete symbolTable;
    #ifdef FILEIN
    in.close();
    #endif
    #ifdef FILEOUT
    out.close();
    #endif
    return 0;
}