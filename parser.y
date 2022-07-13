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
vector<string> param_holder;

void yyerror(string s){
	plo << "Error at line "<< yylineno << ": " << s << "\n" << endl;
    peo << "Error at line "<< yylineno << ": " << s << "\n" << endl;
    err_count++;
}

int yylex(void);
int yyparse(void);

%}
%define parse.error verbose
%union {
    SymbolInfo* sym_info;
    struct putil* pt;
    char *op;
}

%token IF INT FLOAT VOID ELSE FOR WHILE DO BREAK CHAR DOUBLE RETURN SWITCH CASE DEFAULT CONTINUE PRINTLN INCOP DECOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON
%token <sym_info> ID CONST_INT CONST_FLOAT CONST_CHAR ERRFLT 
%token <op> ADDOP MULOP RELOP LOGICOP ASSIGNOP
%type <pt>  start program unit variable var_declaration type_specifier func_declaration func_definition parameter_list
%type <pt>  expression factor unary_expression term simple_expression rel_expression statement statements compound_statement logic_expression expression_statement
%type <pt> arguments argument_list declaration_list

%destructor{delete $$;} <pt>
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
    bool inserted = sym_tab.insert($2->getName(), $2->getType(), llo);
    if(inserted == false) {
        print_multidecl_func($2->getName());
    }
    else {
        print_parser_text($$->data);
        int param_decl_len = split($4->data, ',').size();
        SymbolInfo* sym = sym_tab.lookUp($2->getName());
        sym->param_decl_len = param_decl_len;
        sym->ret_type = $1->data;
        sym->func_declared = true;
    }
    delete $2;
    delete $4;
}
                    |   type_specifier ID LPAREN RPAREN SEMICOLON
{
    print_parser_grammar("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");
    $$ = new putil();
    $$->data = $1->data + " " + $2->getName() + "();";
    bool inserted = sym_tab.insert($2->getName(), $2->getType(), llo);
    if(inserted == false) {
        print_multidecl_func($2->getName());
    }
    else {
        print_parser_text($$->data);
        SymbolInfo* sym = sym_tab.lookUp($2->getName());
        sym->param_decl_len = 0;
        sym->ret_type = $1->data;
        sym->func_declared = true;
    }
    delete $1;
    delete $2;
}
                    ;
func_definition     :   type_specifier ID LPAREN parameter_list RPAREN compound_statement
{
    print_parser_grammar("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");
    $$ = new putil();
    $$->data = $1->data + " " + $2->getName() + "(" + $4->data + ")" + $6->data;
    print_parser_text($$->data);
    bool inserted = sym_tab.insert($2->getName(), $2->getType(), llo);
    SymbolInfo* sym = sym_tab.lookUp($2->getName());
    vector<string> param_list = parse_params($4->data);
    if(sym->func_declared == true){
        if(sym->func_defined == false){
            bool is_valid_def = ($1->data == sym->ret_type) && (param_list.size() == sym->param_decl_len);
            if (is_valid_def == false){
                print_invalid_fun_def($2->getName());
                //HANDLE ERROR
            }
        }else{
            print_multidef_func($2->getName());
            //HANDLE ERRORF
        }
    }
    sym->func_declared = true;
    sym->func_defined = true;
    sym->param_list = param_list;
    delete $1;
    delete $2;
    delete $4;
    delete $6;
}
                    |   type_specifier ID LPAREN RPAREN compound_statement
{
    print_parser_grammar("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
    $$ = new putil();
    $$->data = $1->data + " " + $2->getName() + "()" + $5->data;
    print_parser_text($$->data);
    delete $1;
    delete $2;
    delete $5;
}
                    ;

parameter_list      :   parameter_list COMMA type_specifier ID
{
    print_parser_grammar("parameter_list", "parameter_list COMMA type_specifier ID");
    $$ = new putil();
    $$->data = $1->data +"," + $3->data + " " + $4->getName();
    print_parser_text($$->data);
    delete $1;
    delete $3;
    delete $4;
}
                    |   parameter_list COMMA type_specifier
{
    print_parser_grammar("parameter_list", "parameter_list COMMA type_specifier");
    $$ = new putil();
    $$->data = $1->data + "," + $3->data;
    print_parser_text($$->data);
    delete $1;
    delete $3;
}
                    |   type_specifier ID
{
    print_parser_grammar("parameter_list", "type_specifier ID");
    $$ = new putil();
    $$->data = $1->data + " " + $2->getName();
    print_parser_text($$->data);
}
                    |   type_specifier
{
    print_parser_grammar("parameter_list", "type_specifier");
    $$ = new putil();
    $$->data = $1->data;
    print_parser_text($$->data);
}
                    ;
compound_statement  :   LCURL statements RCURL
{
    print_parser_grammar("compound_statement", "LCURL statements RCURL");
    $$ = new putil();
    $$->data = "{\n" + $2->data + "\n}";
    print_parser_text($$->data);
    delete $2;
}
                    |   LCURL RCURL
{
    print_parser_grammar("compound_statement", "LCURL RCURL");
    $$ = new putil();
    $$->data = "{}";
    print_parser_text($$->data);
}
                    ;
var_declaration     :   type_specifier declaration_list SEMICOLON
{
    print_parser_grammar("var_declaration", "type_specifier declaration_list SEMICOLON");
    $$ = new putil();
    $$->data = $1->data + " " + $2->data + ";";
    print_parser_text($$->data);
    delete $1;
    delete $2;
}
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
    print_parser_grammar("type_specifier", "VOID");
    $$ = new putil();
    $$->data = "void";
    print_parser_text($$->data);
}
                    ;
                    ;
declaration_list    :   declaration_list COMMA ID
{
    print_parser_grammar("declaration_list", "declaration_list COMMA ID");
    $$ = new putil();
    $$->data = $1->data + "," + $3->getName();
    //----Symbol table insertion
    bool inserted = sym_tab.insert($3->getName(), $3->getType(), llo);
    if(inserted==false){
        print_multidecl_var($3->getName());
    }else print_parser_text($$->data);
    //----Finished symbol table insertion
    delete $1;
}
                    |   declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
{
    print_parser_grammar("declaration_list", "declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
    $$ = new putil();
    $$->data = $1->data + "," + $3->getName() + "[" + $5->getName() + "]";
    //-----Symbol table insertion
    bool inserted = sym_tab.insert($3->getName(), $3->getType(), llo);
    if(inserted == false) {
        print_multidecl_var($3->getName());
    }
    else print_parser_text($$->data);
    //-----Finished SymbolTable insertion
    delete $1;
    delete $3;
    delete $5;
}
                    |   ID
{
    print_parser_grammar("declaration_list", "ID");
    $$ = new putil();
    $$->data = $1->getName();
    //-----SymbleTable insertion
    bool inserted = sym_tab.insert($1->getName(), $1->getType(), llo);
    console_log("LINE 271: inserted");
    if(inserted == false) {
        print_multidecl_var($1->getName());
    }
    else print_parser_text($$->data);
    //------Finished SymbolTable insertion
    delete $1;
}
                    |   ID LTHIRD CONST_INT RTHIRD
{
    print_parser_grammar("declaration_list", "ID LTHIRD CONST_INT RTHIRD");
    $$ = new putil();
    $$->data = $1->getName() + "[" + $3->getName() + "]";
    //-----SymbleTable insertion
    bool inserted = sym_tab.insert($1->getName(), $1->getType(), llo);
    if(inserted == false) {
        print_multidecl_var($1->getName());
    }
    else print_parser_text($$->data);
    //------Finished SymbolTable insertion
    delete $1;
    delete $3;
}
                    ;
statements          :   statement
{
    print_parser_grammar("statements", "statement");
    $$ = new putil();
    $$->data = $1->data;
    print_parser_text($$->data);
    delete $1;
}
                    |   statements statement
{
    print_parser_grammar("statements", "statements statement");
    $$ = new putil();
    $$->data = $1->data + "\n" + $2->data;
    print_parser_text($$->data);
    delete $1;
    delete $2;
}
                    ;
statement           :   var_declaration
{
    print_parser_grammar("statement", "var_declaration");
    $$ = new putil();
    $$->data = $1->data;
    print_parser_text($$->data);
    delete $1;
}
                    |   expression_statement
{
    print_parser_grammar("statement", "expression_statement");
    $$ = new putil();
    $$->data = $1->data;
    print_parser_text($$->data);
    delete $1;
}
                    |   compound_statement
{
    print_parser_grammar("statement", "compound_statement");
    $$ = new putil();
    $$->data = $1->data;
    print_parser_text($$->data);
    delete $1;
}
                    |   FOR LPAREN expression_statement expression_statement expression RPAREN statement
{
    print_parser_grammar("statement", "FOR LPAREN expression_statement expression_statement expression RPAREN statement");
    $$ = new putil();
    $$->data = "for(" + $3->data + ";" + $4->data + ";" + $5->data + ")" + $7->data;
    print_parser_text($$->data);
    delete $3;
    delete $4;
    delete $5;
    delete $7;
}
                    |   IF LPAREN expression RPAREN statement
{
    print_parser_grammar("statement", "IF LPAREN expression RPAREN statement");
    $$ = new putil();
    $$->data = "if(" + $3->data + ")" + $5->data;
    print_parser_text($$->data);
    delete $3;
    delete $5;
}
                    |   IF LPAREN expression RPAREN statement ELSE statement
{
    print_parser_grammar("statement", "IF LPAREN expression RPAREN statement ELSE statement");
    $$ = new putil();
    $$->data = "if(" + $3->data + ")" + $5->data + "else" + $7->data;
    print_parser_text($$->data);
    delete $3;
    delete $5;
    delete $7;
}
                    |   WHILE LPAREN expression RPAREN statement
{
    print_parser_grammar("statement", "WHILE LPAREN expression RPAREN statement");
    $$ = new putil();
    $$->data = "while(" + $3->data + ")" + $5->data;
    print_parser_text($$->data);
    delete $3;
    delete $5;
}
                    |   PRINTLN LPAREN ID RPAREN SEMICOLON
{
    print_parser_grammar("statement", "PRINTLN LPAREN ID RPAREN SEMICOLON");
    $$ = new putil();
    $$->data = "printf(" + $3->getName() + ");";
    print_parser_text($$->data);
    delete $3;
}
                    |   RETURN expression SEMICOLON
{
    print_parser_grammar("statement", "RETURN expression SEMICOLON");
    $$ = new putil();
    $$->data = "return " + $2->data + ";";
    print_parser_text($$->data);
    delete $2;
}
                    ;
expression_statement    :   SEMICOLON
{
    print_parser_grammar("expression_statement", "SEMICOLON");
    $$ = new putil();
    $$->data = ";";
    print_parser_text($$->data);
}
                    |   expression SEMICOLON
{
    print_parser_grammar("expression_statement", "expression SEMICOLON");
    $$ = new putil();
    $$->data = $1->data + ";";
    print_parser_text($$->data);
    delete $1;
}
                        ;
variable            :   ID
{
    print_parser_grammar("variable", "ID");
    $$ = new putil();
    $$->data = $1->getName();
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
    $$->data = $1->data + "=" + $3->data;
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
    $$->data = $1->data + $2 + $3->data;
    $$->type = "BOOL";
    print_parser_text($$->data);
    delete $1;
    delete $2;
    delete $3;
}
                    ;   
rel_expression      :   simple_expression
{
    print_parser_grammar("rel_expression", "simple_expression");
    $$ = new putil();
    $$->data = $1->data;
    $$->type = $1->type;
    print_parser_text($$->data);
    delete $1;
}
                    |   simple_expression RELOP simple_expression
{
    print_parser_grammar("rel_expression", "simple_expression RELOP simple_expression");
    $$ = new putil();
    $$->data = $1->data + $2 + $3->data;
    $$->type = "BOOL";
    print_parser_text($$->data);
    delete $1;
    delete $2;
    delete $3;
}
                    ;
simple_expression   :   term
{
    print_parser_grammar("simple_expression", "term");
    $$ = new putil();
    $$->data = $1->data;
    $$->type = $1->type;
    print_parser_text($$->data);
    delete $1;
}
                    |   simple_expression ADDOP term
{
    print_parser_grammar("simple_expression", "simple_expression ADDOP term");
    $$ = new putil();
    $$->data = $1->data + $2 + $3->data;
    $$->type = $1->type;
    print_parser_text($$->data);
    delete $1;
    delete $2;
    delete $3;
}
                    ;
term                :   unary_expression
{
    print_parser_grammar("term", "unary_expression");
    $$ = new putil();
    $$->data = $1->data;
    $$->type = $1->type;
    print_parser_text($$->data);
    delete $1;
}
                    |   term MULOP unary_expression
{
    print_parser_grammar("term", "term MULOP unary_expression");
    $$ = new putil();
    $$->data = $1->data  + $2 + $3->data;
    $$->type = $3->type;
    print_parser_text($$->data);
    delete $1;
    delete $2;
    delete $3;
}
                    ;
unary_expression    :   ADDOP unary_expression
{
    print_parser_grammar("unary_expression", "ADDOP unary_expression");
    $$ = new putil();
    $$->data = $1 + $2->data;
    print_parser_text($$->data);
    delete $1;
    delete $2;
}
                    |   NOT unary_expression
{
    print_parser_grammar("unary_expression", "NOT unary_expression");
    $$ = new putil();
    $$->data = "!"+$2->data;
    print_parser_text($$->data);
    delete $2;
}
                    |   factor
{
    print_parser_grammar("unary_expression", "factor");
    $$ = new putil();
    $$->data = $1->data;
    $$->type = $1->type;
    print_parser_text($$->data);
    delete $1;
}
                    ;
factor              :   variable
{
    print_parser_grammar("factor", "variable");
    $$ = new putil();
    $$->data = $1->data;
    $$->type = $1->type;
    print_parser_text($$->data);
    delete $1;
}
                    |   ID LPAREN argument_list RPAREN
{
    print_parser_grammar("factor", "ID LPAREN argument_list RPAREN");
    $$ = new putil();
    $$->data = $1->getName() + "(" + $3->data + ")";
    print_parser_text($$->data);
    delete $1;
    delete $3;
}
                    |   LPAREN expression RPAREN
{
    print_parser_grammar("factor", "LPAREN expression RPAREN");
    $$ = new putil();
    $$->data = "(" + $2->data + ")";
    $$->type = $2->type;
    print_parser_text($$->data);
    delete $2;
}
                    |   CONST_INT
{
    print_parser_grammar("factor", "CONST_INT");
    $$ = new putil();
    $$->data = $1->getName();
    $$->type = $1->getType();
    print_parser_text($$->data);
    delete $1;
}
                    |   CONST_FLOAT
{
    print_parser_grammar("factor", "CONST_FLOAT");
    $$ = new putil();
    $$->data = $1->getName();
    $$->type = $1->getType();
    print_parser_text($$->data);
    delete $1;
}
                    |   variable INCOP
{
    print_parser_grammar("factor", "variable INCOP");
    $$ = new putil();
    $$->data = $1->data + "++";
    $$->type = "INCOP";
    print_parser_text($$->data);
    delete $1;
}
                    |   variable DECOP
{
    print_parser_grammar("factor", "variable DECOP");
    $$ = new putil();
    $$->data = $1->data + "--";
    $$->type = "DECOP";
    print_parser_text($$->data);
    delete $1;
}
                    ;          
argument_list       :   arguments
{
    print_parser_grammar("argument_list", "arguments");
    $$ = new putil();
    $$->data = $1->data;
    print_parser_text($$->data);
    delete $1;
}
                    |
{
    print_parser_grammar("argument_list", "");
    $$ = new putil();
}
                    ;
arguments           :   arguments COMMA logic_expression
{
    print_parser_grammar("arguments", "arguments COMMA logic_expression");
    $$ = new putil();
    $$->data = $1->data + "," + $3->data;
    print_parser_text($$->data);
    delete $1;
    delete $3;
}
                    |   logic_expression
{
    print_parser_grammar("arguments", "logic_expression");
    $$ = new putil();
    $$->data = $1->data;
    print_parser_text($$->data);
    delete $1;
}
                    ;
%%

main(int argc, char* argv[])
{
    #ifdef YYDEBUG
    yydebug = 1;
    #endif
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
