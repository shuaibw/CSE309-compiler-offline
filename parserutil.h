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
    string code;
    putil(){}
};
extern ofstream plo;
extern ofstream peo;
extern ofstream llo;
extern ofstream lto;
extern ofstream aco;
extern const char* ASM_CODE_OPTIM;
extern const char* ASM_CODE_OUT;
extern SymbolTable sym_tab;
extern int yylineno;
extern int err_count;
extern int temp_count;
extern int label_count;
extern void yyerror(string s);

string newLabel(){
    return "@L"+to_string(label_count++);
}

string newTemp(){
    return "t"+to_string(temp_count++);
}

void init_asm_file(){
    aco << 
".MODEL SMALL\n\
.STACK 400H\n\
.DATA\n";
}
void console_log(string s){
    cout<<"\033[1;31m"<<s<<"\033[0m"<<endl;
}

SymbolInfo* parse_var(string data){
    int lthird=data.find("[");
    if(lthird!=string::npos){ //is an array
        string var_name = data.substr(0, lthird);
        return sym_tab.lookUp(var_name);
    }
    return sym_tab.lookUp(data); 
}

void print_parser_grammar(const char* left, const char* right){
    plo << "Line " << yylineno << ": " << left << " : " << right << "\n" << endl;
}

void print_parser_text(string data){
    plo << data << "\n" << endl;
}

void print_void_var(){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Variable type cannot be void" << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Variable type cannot be void" << "\n" << endl;
}
void print_void_func_in_expr(){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Void function used in expression" << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Void function used in expression" << "\n" << endl;
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
void print_not_a_func(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Not a function " << name << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Not a function " << name << "\n" << endl;    
}
void print_invalid_return(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Invalid value returned from function " << name << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Invalid value returned from function " << name << "\n" << endl;
}
void print_void_return(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Cannot return value from function " << name << " with void return type \n" << endl;
    plo << "Error at line " << yylineno << ": " << "Cannot return value from function " << name << " with void return type \n" << endl;
}
void print_param_len_mismatch(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Total number of arguments mismatch with declaration in function " << name << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Total number of arguments mismatch with declaration in function " << name << "\n" << endl;
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
void print_ret_type_mismatch(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Return type mismatch of " << name << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Return type mismatch of " << name << "\n" << endl;
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
void print_mod_by_zero(){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Modulus by Zero" << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Modulus by Zero" << "\n" << endl;
}
void print_div_by_zero(){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Divide by Zero" << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Divide by Zero" << "\n" << endl;
}
void print_inv_ara_assignment(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << "Type mismatch, "<< name << " is an array\n" << endl;
    plo << "Error at line " << yylineno << ": " << "Type mismatch, "<< name << " is an array\n" << endl;
}
void print_not_an_ara(string name){
    err_count++;
    peo << "Error at line " << yylineno << ": " << name << " not an array\n" << endl;
    plo << "Error at line " << yylineno << ": " << name << " not an array\n" << endl;
}

bool match_types(string lhs, string rhs){
    if(rhs=="ERR") return true; //already err caught, don't check
    bool lhs_int  = lhs == "int" || lhs == "ara_int";
    bool rhs_int = rhs == "CONST_INT" || rhs == "int" || rhs == "ara_int";

    if(lhs_int && rhs_int) return true;
    bool lhs_float = lhs == "float" || lhs == "ara_float";
    bool rhs_float = rhs == "CONST_FLOAT" || rhs == "float" || rhs == "ara_float";

    return (lhs_float && (rhs_int || rhs_float));
}

void match_func_ret_type(vector<string> &vec, string ret_type, string func){
    if(ret_type=="void"){ //cannot return anything if void
        if(!vec.size()==0) print_void_return(func);
        vec.clear();
        return;
    }
    for (const auto &s: vec){ //must match all return statements if not void
        if(!match_types(ret_type, s)) {
            print_invalid_return(func);
            vec.clear();
            return;
        }
    }
    vec.clear(); //all matched, clear return type holder
}
string upcast_type(string a, string b){
    bool aflt = a == "CONST_FLOAT" || a=="float" || a=="ara_float";
    bool bflt = b == "CONST_FLOAT" || b=="float" || b=="ara_float";
    if (aflt || bflt) return "CONST_FLOAT";
    bool aint = a == "CONST_INT" || a=="int" || a=="ara_int";
    bool bint = b == "CONST_INT" || b=="int" || b=="ara_int";
    if (aint && bint) return "CONST_INT";
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
bool find_param_by_name(vector<SymbolInfo> vec, string name){
    for(const auto &s: vec){
        if(s.getName()==name) return true;
    }
    return false;
}
void print_param_def_mismatch(string name, int sn){
    err_count++;
    peo << "Error at line " << yylineno << ": Parameter no. " << sn << " does not match in function " << name << "\n" << endl;
    plo << "Error at line " << yylineno << ": Parameter no. " << sn << " does not match in function " << name << "\n" << endl;
}
void print_arg_mismatch(string name, int sn){
    err_count++;
    peo << "Error at line " << yylineno << ": " << sn << "th" << " argument mismatch in function " << name << "\n" << endl;
    plo << "Error at line " << yylineno << ": " << sn << "th" << " argument mismatch in function " << name << "\n" << endl;
}
bool match_param_type(string declared, string defined){
    if(declared == "int") return defined == "int";
    else if(declared == "float") return defined == "float";
    // else throw runtime_error("Invalid param type: " + declared +", "+ defined);
    else return false;
}
bool match_arg_type(string defined, string passed){
    bool pint = (passed == "CONST_INT" || passed == "int" || passed == "ara_int");
    bool pflt = (passed == "float" || passed == "CONST_FLOAT" || passed == "ara_float");
    if(defined == "int") return pint;
    else if(defined == "float") return pint || pflt;
    // else throw runtime_error("Invalid arg type: " + defined +", "+ defined);
    else return false;
}
void validate_param_type(SymbolInfo* sym, vector<SymbolInfo> param_holder){
    for(int i=0;i<param_holder.size();i++){
        if(!match_param_type(sym->param_list.at(i).getType(), param_holder.at(i).getType())){
            print_param_def_mismatch(sym->getName(), i+1);
        }
    }
}
void validate_arg_type(SymbolInfo* sym, vector<string> arg_type_holder){
    vector<SymbolInfo>& params = sym->param_list;
    for(int i=0;i<arg_type_holder.size();i++){
        if(!match_arg_type(params.at(i).getType(), arg_type_holder.at(i))){
            print_arg_mismatch(sym->getName(), i+1);
            return; //sampleio matha kharap >_<
        }
    }
}
#endif