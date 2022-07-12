#ifndef PARSERUTIL_H
#define PARSERUTIL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "SymbolInfo.h"
using namespace std;

struct putil{
    string data;
    string type;
    vector<SymbolInfo*> sym_list;
    vector<string> param_list;

    putil(){}
    void print(){
        cout << "Data: " << data << endl;
        cout << "Printing symbol list: " << sym_list.size() << endl;
        for (auto sym: sym_list){
            cout << *sym << endl; 
        }
    }
    ~putil(){
        for (auto sym: sym_list){
            delete sym;
        }
    }
};
extern ofstream plo;
extern ofstream peo;
extern int yylineno;

void print_parser_grammar(const char* left, const char* right){
    plo << "Line " << yylineno << ": " << left << " : " << right << "\n" << endl;
}

void print_parser_text(string data){
    plo << data << "\n" << endl;
}

void print_undecl_var(string name){
        peo << "Error at line " << yylineno << ": " << "Undefined variable " << name << "\n" << endl;
}


#endif