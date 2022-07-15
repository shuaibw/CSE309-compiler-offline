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
    peo << "Error at line " << yylineno << ": " << "Undeclared variable " << name << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Undeclared variable " << name << "\n" << endl;
}
void print_undef_func(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Undefined function " << name << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Undefined function " << name << "\n" << endl;
}
void print_multidecl_param(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Multiple declaration of " << name << " in parameter\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Multiple declaration of " << name << " in parameter\n" << endl;
}
void print_multidecl_var(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Multiple declaration of " << name << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Multiple declaration of " << name << "\n" << endl;
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
void print_invalid_ara_idx(){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Expression inside third brackets not an integer" << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Expression inside third brackets not an integer" << "\n" << endl;
}
void print_type_mismatch(){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Type Mismatch" << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Type Mismatch" << "\n" << endl;
}
void print_mod_mismatch(){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Non-Integer operand on modulus operator" << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Non-Integer operand on modulus operator" << "\n" << endl;
}
void print_inv_ara_assignment(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Type mismatch, "<< name << " is an array\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Type mismatch, "<< name << " is an array\n" << endl;
}

bool match_types(string lhs, string rhs){
    bool lhs_int  = lhs == "int" || lhs == "ara_int";
    bool rhs_int = rhs == "CONST_INT" || rhs == "int" || rhs == "ara_int";

    if(lhs_int && rhs_int) return true;
    bool lhs_float = lhs == "float" || lhs == "ara_float";
    bool rhs_float = rhs == "CONST_FLOAT" || rhs == "float" || rhs == "ara_float";

    return (lhs_float && (rhs_int || rhs_float));
}

string upcast_type(string a, string b){
    bool aflt = a == "CONST_FLOAT" || a=="float" || a=="ara_float";
    bool bflt = b == "CONST_FLOAT" || b=="float" || b=="ara_float";
    if (aflt || bflt) return "CONST_FLOAT";
    bool aint = a == "CONST_INT" || a=="int" || a=="ara_int";
    bool bint = b == "CONST_INT" || b=="int" || b=="ara_int";
    if (aint && bint) return "CONST_INT";
    console_log(a);
    console_log(b);
    return "ERR";
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