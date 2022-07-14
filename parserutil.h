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
    putil(){}
};
extern ofstream plo;
extern ofstream peo;
extern ofstream llo;
extern ofstream lto;
extern int yylineno;
extern int err_count;


void console_log(string s){
    cout<<"\033[1;31m"<<s<<"\033[0m"<<endl;
}

void print_parser_grammar(const char* left, const char* right){
    plo << "Line " << yylineno << ": " << left << " : " << right << "\n" << endl;
}

void print_parser_text(string data){
    plo << data << "\n" << endl;
}

void print_undecl_var(string name){
        err_count++;
        peo << "Error at line " << yylineno << ": " << "Undefined variable " << name << "\n" << endl;
        plo << "Error at line " << yylineno << ": " << "Undefined variable " << name << "\n" << endl;
}
void print_multidecl_var(string name){
        err_count++;
        peo << "Error at line " << yylineno << ": " << "Multiple declaration of variable " << name << "\n" << endl;
        plo << "Error at line " << yylineno << ": " << "Multiple declaration of variable " << name << "\n" << endl;
}

void print_multidecl_func(string name){
        err_count++;
        peo << "Error at line " << yylineno << ": " << "Multiple declaration of function " << name << "\n" << endl;
        plo << "Error at line " << yylineno << ": " << "Multiple declaration of function " << name << "\n" << endl;
}

void print_multidef_func(string name){
        err_count++;
        peo << "Error at line " << yylineno << ": " << "Multiple definition of function " << name << "\n" << endl;
        plo << "Error at line " << yylineno << ": " << "Multiple definition of function " << name << "\n" << endl;
}

void print_invalid_fun_def(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Invalid definition of function " << name << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Invalid definition of function " << name << "\n" << endl;
}

vector<string> split(string s, char c = ' '){
    vector<string> result;
    const char* str = s.c_str();
    do{
        const char *begin = str;
        while(*str != c && *str) str++;
        result.push_back(string(begin, str));
    } while (0 != *str++);
    return result;
}

vector<string> parse_params(string s){
    vector<string> result;
    vector<string> comma_sep = split(s, ',');
    for(const auto &str: comma_sep){
        vector<string> space_sep = split(str, ' ');
        if(space_sep.size()!=2){
            result.push_back("ERR");
            return result;
        }
        result.push_back(space_sep.back());
    }
    return result;
}

#endif