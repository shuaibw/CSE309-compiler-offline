%{
#include <iostream>
#include<string>
#include<fstream>
#include "SymbolInfo.h"
#include "SymbolTable.h"
#include "ScopeTable.h"
#include "parserutil.h"

extern int yylineno;
extern FILE* yyin;
const char* PARSER_LOG_FILE = "./parserlog.txt";
const char* PARSER_ERR_FILE = "./parsererr.txt";
const char* LEX_LOG_FILE = "./lexlog.txt";
const char* LEX_TOKEN_FILE = "./lextok.txt";
ofstream plo(PARSER_LOG_FILE, ios::out); // parser log out
ofstream peo(PARSER_ERR_FILE, ios::out); // parser error out
ofstream llo(LEX_LOG_FILE, ios::out); // lex log out
ofstream lto(LEX_TOKEN_FILE, ios::out); // lex token out
int err_count = 0;
SymbolTable sym_tab(7);


void yyerror(char *s){
	plo << "Error at line "<< yylineno << ": " << s << "\n" << endl;
    peo << "Error at line "<< yylineno << ": " << s << "\n" << endl;
    err_count++;
}

int yylex(void);
int yyparse(void);

%}

%union {
    SymbolInfo* sym_info;
    struct putil* pt;
}

%token IF INT FLOAT VOID ELSE FOR WHILE DO BREAK CHAR DOUBLE RETURN SWITCH CASE DEFAULT CONTINUE PRINTLN INCOP DECOP ASSIGNOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON
%token <sym_info> ID ADDOP MULOP RELOP LOGICOP CONST_INT CONST_FLOAT ERRFLT 
%type <pt>  start program unit variable var_declaration type_specifier func_declaration func_definition parameter_list
%type <pt>  expression factor unary_expression term simple_expression rel_expression statement statements compound_statement logic_expression expression_statement
%type <pt> arguments argument_list declaration_list


%%
start               :   program
{
    print_parser_grammar("start", "program");
    $$ = new putil();
    $$->data = $1->data;
    delete $1;
}
program             :   program unit
{
    $$ = new putil();
    $$->data = $1->data + "\n" + $2->data;
    print_parser_grammar("program", "program unit");
    print_parser_text($$->data);
    delete $1;
    delete $2;
}
                    |   unit
{
    $$ = new putil();
    $$->data = $1->data;
    print_parser_grammar("program", "unit");
    print_parser_text($$->data);
    delete $1;
}
                    ;
unit                :   var_declaration
{
    $$ = new putil();
    $$->data = $1->data;
    print_parser_grammar("unit", "var_declaration");
    print_parser_text($$->data);
    delete $1;
}
                    |   func_declaration
{
    $$ = new putil();
    $$->data = $1->data;
    print_parser_grammar("unit", "func_declaration");
    print_parser_text($$->data);
    delete $1;
}
                    |   func_definition
{
    $$ = new putil();
    $$->data = $1->data;
    print_parser_grammar("unit", "func_definition");
    print_parser_text($$->data);
    delete $1;
}
                    ;
func_declaration    :   type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
{
    print_parser_grammar("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
    $$ = new putil();
    $$->data = $1->data + " " + $2->getName() + "(" + $4->data + ");";
}
                    |   type_specifier ID LPAREN RPAREN SEMICOLON
                    ;
func_definition     :   type_specifier ID LPAREN parameter_list RPAREN compound_statement
                    |   type_specifier ID LPAREN RPAREN compound_statement
                    ;

parameter_list      :   parameter_list COMMA type_specifier ID
                    |   parameter_list COMMA type_specifier
                    |   type_specifier ID
                    |   type_specifier
                    ;
compound_statement  :   LCURL statements RCURL
                    |   LCURL RCURL
                    ;
var_declaration     :   type_specifier declaration_list SEMICOLON
                    ;
type_specifier      :   INT
{
    print_parser_grammar("type_specifier", "INT");
    $$ = new putil();
    $$->data = "int";
    print_parser_text($$->data);
}
                    |   FLOAT
{
    print_parser_grammar("type_specifier", "FLOAT");
    $$ = new putil();
    $$->data = "float";
    print_parser_text($$->data);
}
                    |   VOID
{
    print_parser_grammar("type_specifier", "VOID)");
    $$ = new putil();
    $$->data = "void";
    print_parser_text($$->data);
}
                    ;
                    ;
declaration_list    :   declaration_list COMMA ID
                    |   declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
                    |   ID
                    |   ID LTHIRD CONST_INT RTHIRD
                    ;
statements          :   statement
                    |   statements statement
                    ;
statement           :   var_declaration
                    |   expression_statement
                    |   compound_statement
                    |   FOR LPAREN expression_statement expression_statement expression RPAREN statement
                    |   IF LPAREN expression RPAREN statement
                    |   IF LPAREN expression RPAREN statement ELSE statement
                    |   WHILE LPAREN expression RPAREN statement
                    |   PRINTLN LPAREN ID RPAREN SEMICOLON
                    |   RETURN expression SEMICOLON
                    ;
expression_statement    :   SEMICOLON
                        |   expression SEMICOLON
                        ;
variable            :   ID
{
    print_parser_grammar("variable", "ID");
    $$ = new putil();
    $$->data = $1->getName();
    SymbolInfo *ret = sym_tab.lookUp($1->getName());
    if(ret == nullptr){
        err_count++;
        print_undecl_var($1->getName());
        $$->type="ERR";
    }else{
        $$->type = ret->getType();
    }
    print_parser_text($$->data);
    delete $1;
}
                    |   ID LTHIRD expression RTHIRD
{
    print_parser_grammar("variable", "ID LTHIRD expression RTHIRD");
    $$ = new putil();
    $$->data = $1->getName() + "[" + $3->data + "]";
    SymbolInfo *ret = sym_tab.lookUp($1->getName());
    if(ret == nullptr){
        err_count++;
        print_undecl_var($1->getName());
        $$->type="ERR";
    }else{
        $$->type = ret->getType();
    }
    print_parser_text($$->data);
    delete $1;
    delete $3;
}
                    ;
expression          :   logic_expression
{
    print_parser_grammar("expression", "logic_expression");
    $$ = new putil();
    $$->data = $1->data;
    $$->type = $1->type;
    print_parser_text($$->data);
    delete $1;
}
                    |   variable ASSIGNOP logic_expression
{
    print_parser_grammar("expression", "variable ASSIGNOP logic_expression");
    $$ = new putil();
    $$->data = $1->data + " = " + $3->data;
    $$->type = $3->type;
    print_parser_text($$->data);
    delete $1;
    delete $3;
}
                    ;
logic_expression    :   rel_expression
{
    print_parser_grammar("logic_expression", "rel_expression");
    $$ = new putil();
    $$->data = $1->data;
    $$->type = $1->type;
    print_parser_text($$->data);
    delete $1;
}
                    |   rel_expression LOGICOP rel_expression
{
    print_parser_grammar("logic_expression", "rel_expression LOGICOP rel_expression");
    $$ = new putil();
    $$->data = $1->data + " " + $2->getName() + " " + $3->data;
    $$->type = "BOOL";
    print_parser_text($$->data);
    delete $1;
    delete $2;
    delete $3;
}
                    ;   
rel_expression      :   simple_expression
                    |   simple_expression RELOP simple_expression
                    ;
simple_expression   :   term
                    |   simple_expression ADDOP term
                    ;
term                :   unary_expression
                    |   term MULOP unary_expression
                    ;
unary_expression    :   ADDOP unary_expression
                    |   NOT unary_expression
                    |   factor
                    ;
factor              :   variable
                    |   ID LPAREN argument_list RPAREN
                    |   LPAREN expression RPAREN
                    |   CONST_INT
                    |   CONST_FLOAT
                    |   variable INCOP
                    |   variable DECOP
                    ;          
argument_list       :   arguments
                    |
                    ;
arguments           :   arguments COMMA logic_expression
                    |   logic_expression
                    ;
%%

main(int argc, char* argv[])
{
    if(argc != 2){
        cout<<"No source file provided"<<endl;
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if(fin == NULL){
        cout<<"Error opening file"<<endl;
        return 1;
    }
    yyin = fin;
    yylineno = 1;
    yyparse();
    sym_tab.printAllScopes(plo);
    plo << "Total number of lines: " << yylineno << endl;
    plo << "Total number of errors: " << err_count << endl;
    fclose(fin);
    plo.close();
    peo.close();
    exit(0);
}
