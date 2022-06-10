%option noyywrap yylineno
%x CLT

%{
    #include<iostream>
    #include<string>
    #include<fstream>
    #include "SymbolTable.h"
    using namespace std;

    FILE* token_out;
    const int BUCKET = 7;
    const char* LOG_FILE = "./lexlog.txt";
    const char* TOKEN_FILE = "./lextok.txt";
    ofstream log_out(LOG_FILE, ios::out);
    ofstream tok_out(TOKEN_FILE, ios::out);
    SymbolTable sym_tab(BUCKET);
    
    void print_log(const char* TOK, const char* lex, int line_no ){
        log_out << "Line no " << line_no 
        << ": Token <" << TOK 
        << "> Lexeme " << lex 
        <<" found"<< endl <<endl;
        return;
    }

    void print_tok(const char* TOK, const char* lex=NULL){
        if(lex!=NULL)
            tok_out << "<" << TOK
                 << ", " << lex
                 << "> ";
        else
            tok_out << "<" << TOK <<"> "; 
        return;
    }

%}

WS          [ \t\v]+
NL          \n|\n\r|\r
LETTER      [a-zA-Z]
UND         [_]
DIGIT       [0-9]
ESCSEQ      \\[ntrbfarv0\\]
ID          ({LETTER}|{UND})({LETTER}|{UND}|{DIGIT})*
FLOAT       {DIGIT}*(\.{DIGIT}+)?([Ee][+-]?{DIGIT}+)?
INT         {DIGIT}+
CHAR        '{LETTER}'|'{DIGIT}'|'{ESCSEQ}'
STRING      "([^\"]|\\\")*"
ADDOP       [+-]
MULOP       [*/%]
INCOP       (++)|(--)
RELOP       (<=)|(>=)|(<)|(>)|(==)|(!=)
ASSIGNOP    (=)|(+=)|(-=)|(*=)|(/=)
LOGICOP     (&&)|(||)
NOT         (!)
LPAREN      "("
RPAREN      ")"
LCURL       "{"
RCURL       "}"
LTHIRD      "["
RTHIRD      "]"
COMMA       ","
SEMICOLON   ";"


%%
{WS}        {}
{NL}        {}

"if"        {
                print_tok("IF");
                print_log("IF", yytext, yylineno);
            }

"for"       {
                print_tok("FOR");
                print_log("FOR", yytext, yylineno);
            }

"do"        {
                print_tok("DO");
                print_log("DO", yytext, yylineno);
            }

"int"       {
                print_tok("INT");
                print_log("INT", yytext, yylineno);
            }

"float"     {
                print_tok("FLOAT");
                print_log("FLOAT", yytext, yylineno);
            }

"void"      {
                print_tok("VOID");
                print_log("VOID", yytext, yylineno);
            }

"switch"    {
                print_tok("SWITCH");
                print_log("SWITCH", yytext, yylineno);
            }

"default"   {
                print_tok("DEFAULT");
                print_log("DEFAULT", yytext, yylineno);
            }

"else"      {
                print_tok("ELSE");
                print_log("ELSE", yytext, yylineno);
            }

"while"     {
                print_tok("WHILE");
                print_log("WHILE", yytext, yylineno);
            }

"break"     {
                print_tok("BREAK");
                print_log("BREAK", yytext, yylineno);
            }

"char"      {
                print_tok("CHAR");
                print_log("CHAR", yytext, yylineno);
            }
        
"double"    {
                print_tok("DOUBLE");
                print_log("DOUBLE", yytext, yylineno);
            }

"return"    {
                print_tok("RETURN");
                print_log("RETURN", yytext, yylineno);
            }

"case"      {
                print_tok("CASE");
                print_log("CASE", yytext, yylineno);
            }

"continue"  {
                print_tok("CONTINUE");
                print_log("CONTINUE", yytext, yylineno);
            }

{INT}       {
                print_tok("CONST_INT", yytext);
                print_log("CONST_INT", yytext, yylineno);
                sym_tab.insert(yytext, "CONST_INT");
                sym_tab.printAllScopes(log_out);
            }

{FLOAT}     {
                print_tok("CONST_FLOAT", yytext);
                print_log("CONST_FLOAT", yytext, yylineno);
                sym_tab.insert(yytext, "CONST_FLOAT");
                sym_tab.printAllScopes(log_out);
            }

{CHAR}      {
                print_tok("CONST_CHAR", yytext);
                print_log("CONST_CHAR", yytext, yylineno);
                sym_tab.insert(yytext, "CONST_CHAR");
                sym_tab.printAllScopes(log_out);
            }

{ADDOP}     {
                print_tok("ADDOP", yytext);
                print_log("ADDOP", yytext, yylineno);
            }

{MULOP}     {
                print_tok("MULOP", yytext);
                print_log("MULOP", yytext, yylineno);
            }

{ID}        {
                print_tok("ID", yytext);
                print_log("ID", yytext, yylineno);
                sym_tab.insert(yytext, "ID");
                sym_tab.printAllScopes(log_out);
            }

{INCOP}     {
                print_tok("INCOP", yytext);
                print_log("INCOP", yytext, yylineno);
            }
%%

int main(int argc, char*argv[]){
    if(argc != 2){
        cout<<"No input file provided"<<endl;
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if(fin==NULL){
        cout<<"Error opening file"<<endl;
        return 1;
    }

    yyin = fin;
    yylineno = 1;
    yylex();
    fclose(fin);
    return 0;
}