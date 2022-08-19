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
const char* PARSER_LOG_FILE = "./log.txt";
const char* PARSER_ERR_FILE = "./error.txt";
const char* LEX_LOG_FILE = "./lexlog.txt";
const char* LEX_TOKEN_FILE = "./lextok.txt";
const char* ASM_CODE_OUT = "./code.asm";
const char* ASM_CODE_IN = "./asmlib.asm";
const char* ASM_CODE_OPTIM = "./optimized_code.asm";
ofstream plo(PARSER_LOG_FILE, ios::out); // parser log out
ofstream peo(PARSER_ERR_FILE, ios::out); // parser error out
ofstream llo(LEX_LOG_FILE, ios::out); // lex log out
ofstream lto(LEX_TOKEN_FILE, ios::out); // lex token out
ofstream aco(ASM_CODE_OUT, ios::out); //assemble code out
ifstream aci(ASM_CODE_IN, ios::in); //read utility func
int err_count = 0;
int temp_count=0;
int label_count=0;
int stack_offset=0;
// for loop labels
string for_check;
string for_update;
string for_body;
string for_exit;
//while loop labels
string while_check;
string while_body;
string while_exit;
//if else labels
string elselabel;
vector<string> exitlabels;
//return jump for recursion
string retlabel;

SymbolTable sym_tab(7);
vector<SymbolInfo> param_holder;
vector<string> arg_type_holder;
vector<string> ret_type_holder;

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

%token IF INT FLOAT VOID ELSE FOR WHILE DO BREAK SWITCH CASE DEFAULT CONTINUE CHAR DOUBLE RETURN PRINTLN
%token INCOP DECOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON
%token <sym_info> ID CONST_INT CONST_FLOAT CONST_CHAR 
%token <op> ADDOP MULOP RELOP LOGICOP ASSIGNOP
%type <pt> start program unit func_definition parameter_list func_declaration variable var_declaration type_specifier
%type <pt> logic_expression expression_statement expression term simple_expression compound_statement factor unary_expression
%type <pt> arguments argument_list declaration_list rel_expression statement statements dummy

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%destructor{delete $$;} <pt>
%%
start               :   program
{
    print_parser_grammar("start", "program");
    $$ = new putil();
    $$->data = $1->data;
    string str;
    aco << "\n\n";
    aco << "; HELPER MODULES\n";
    while(getline(aci, str)){
        aco << str << "\n";
    }
    aci.close();
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
        SymbolInfo* sym = sym_tab.lookUp($2->getName());
        sym->ret_type = $1->data;
        sym->param_list = param_holder;
        sym->is_func = true;
    }
    param_holder.clear();
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
        sym->ret_type = $1->data;
        sym->is_func = true;
    }
    delete $1;
    delete $2;
}
                    ;
func_definition     :   type_specifier ID LPAREN parameter_list RPAREN 
{   //Function scope not entered yet, insert function to global scope
    retlabel=newLabel();
    bool inserted = sym_tab.insert($2->getName(), $2->getType(), llo);
    SymbolInfo* sym = sym_tab.lookUp($2->getName());
    if(inserted){ //first time definition
        sym->param_list = param_holder;
        sym->func_defined = true;
        sym->is_func = true;
        sym->ret_type = $1->data;
    }
    else if(sym->is_func){ //in current scope, sym points to previously declared ID. Now validate
        if(!sym->func_defined){ //was not defined previously, but declared with ret_type, param_list
            sym->func_defined = true;
            bool param_len_match = sym->param_list.size()==param_holder.size();
            bool ret_type_match = sym->ret_type == $1->data;
            if(!ret_type_match){
                print_ret_type_mismatch($2->getName());
            }
            if(!param_len_match){
                print_param_len_mismatch($2->getName());
            }
            else{
                validate_param_type(sym, param_holder);
            }
        }else{ //was defined already
            print_multidef_func($2->getName());
        }
    }else{ // something other than func exists with same name
        print_multidecl_var($2->getName());
    }
    // Don't clear params, to be inserted in function scope by compound_statement
    //ICG func
    stack_offset=0;
    aco << $2->getName() << " PROC\n";
    if($2->getName() == "main"){
        aco << "MOV AX, @DATA\nMOV DS, AX ; load data segment\n"
            << "MOV BP, SP ; save stack pointer in BP\n";
    }else{
        aco << "PUSH AX\nPUSH BX\nPUSH CX ; save gprs\n"
            << "PUSH BP\nMOV BP, SP ; save stack pointer\n";
    }
}
                        compound_statement
{
    match_func_ret_type(ret_type_holder, $1->data, $2->getName());
    print_parser_grammar("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");
    $$ = new putil();
    $$->data = $1->data + " " + $2->getName() + "(" + $4->data + ")" + $7->data;
    print_parser_text($$->data);
    //ICG func end
    SymbolInfo* sym = sym_tab.lookUp($2->getName());
    aco << retlabel << ": ; to handle recursion\n";
    retlabel.clear();
    if($2->getName()=="main"){
        aco << "MOV AH, 004CH\nINT 21H\nmain ENDP\n";
    }else{
        aco << "MOV SP, BP ; restore stack pointer\n"
            << "POP BP\nPOP CX\nPOP BX\nPOP AX ; restore registers \n"
            << "RET " << sym->param_list.size()*2 << " ; offset stack to clean up parameters\n"
            << $2->getName() << " ENDP\n\n";
    }
    delete $1;
    delete $2;
    delete $4;
    delete $7;
}                   |   type_specifier ID LPAREN parameter_list error RPAREN
{
    param_holder.clear();
    bool inserted = sym_tab.insert($2->getName(), $2->getType(), llo);
    SymbolInfo* sym = sym_tab.lookUp($2->getName());
    if(inserted){
        sym->func_defined = true;
        sym->is_func = true;
        sym->ret_type = $1->data;
    }
    else if(sym->is_func){ //in current scope, sym points to previously declared ID. Now validate
        if(!sym->func_defined){
            sym->func_defined = true;
            bool ret_type_match = sym->ret_type == $1->data;
            if(!ret_type_match){
                print_ret_type_mismatch($2->getName());
            }
        }else{
            print_multidef_func($2->getName());
        }
    }else{
        print_multidecl_var($2->getName());
    }    
}

                        compound_statement
{
    match_func_ret_type(ret_type_holder, $1->data, $2->getName());
    print_parser_grammar("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
    $$ = new putil();
    $$->data = $1->data + " " + $2->getName() + "(" + $4->data + ")" + $8->data;
    print_parser_text($$->data);
    delete $1;
    delete $2;
    delete $8;
}
                    |   type_specifier ID LPAREN RPAREN
{
    retlabel=newLabel();
    bool inserted = sym_tab.insert($2->getName(), $2->getType(), llo);
    SymbolInfo* sym = sym_tab.lookUp($2->getName());
    if(inserted){
        sym->func_defined = true;
        sym->is_func = true;
        sym->ret_type = $1->data;
        param_holder.clear();
    }
    else if(sym->is_func){ //in current scope, sym points to previously declared ID. Now validate
        if(!sym->func_defined){
            sym->func_defined = true;
            bool ret_type_match = sym->ret_type == $1->data;
            if(!ret_type_match){
                print_ret_type_mismatch($2->getName());
            }
        }else{
            print_multidef_func($2->getName());
        }
    }else{
        print_multidecl_var($2->getName());
    }
    //ICG func no param
    stack_offset=0;
    aco << $2->getName() << " PROC\n";
    if($2->getName() == "main"){
        aco << "MOV AX, @DATA\nMOV DS, AX ; load data segment\n"
            << "MOV BP, SP ; save stack pointer\n";
    }else{
        aco << "PUSH AX\nPUSH BX\nPUSH CX ; save gprs\n"
            << "PUSH BP ; save bp\nMOV BP, SP\n"  ;
    }
}
                        compound_statement
{
    match_func_ret_type(ret_type_holder, $1->data, $2->getName());
    print_parser_grammar("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
    $$ = new putil();
    $$->data = $1->data + " " + $2->getName() + "()" + $6->data;
    print_parser_text($$->data);

    //ICG
    aco << retlabel << ": ; to handle recursion\n";
    retlabel.clear();
    if($2->getName()=="main"){
        aco << "MOV AH, 004CH\nINT 21H\nmain ENDP\n";
    }else{
        aco << "MOV SP, BP ; restore stack pointer\n"
            << "POP BP\nPOP CX\nPOP BX\nPOP AX ; restore registers \n"
            << "RET\n" << $2->getName()<< " ENDP\n\n";
    }

    delete $1;
    delete $2;
    delete $6;
}
                    ;

parameter_list      :   parameter_list COMMA type_specifier ID
{
    if(find_param_by_name(param_holder, $4->getName())){
        print_multidecl_param($4->getName());
    }
    param_holder.emplace_back($4->getName(), $3->data);
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
    param_holder.emplace_back("-1", $3->data);
    $$ = new putil();
    $$->data = $1->data + "," + $3->data;
    print_parser_text($$->data);
    delete $1;
    delete $3;
}
                    |   type_specifier ID
{
    if(find_param_by_name(param_holder, $2->getName())){
        print_multidecl_param($2->getName());
    }
    param_holder.emplace_back($2->getName(), $1->data);
    print_parser_grammar("parameter_list", "type_specifier ID");
    $$ = new putil();
    $$->data = $1->data + " " + $2->getName();

    print_parser_text($$->data);
}
                    |   type_specifier
{
    print_parser_grammar("parameter_list", "type_specifier");
    param_holder.emplace_back("-1", $1->data);
    $$ = new putil();
    $$->data = $1->data;
    print_parser_text($$->data);
}
                    ;
compound_statement  :   LCURL 
{ //Now insert function parameters to scope table if they exist
    sym_tab.enterScope();
    if(!param_holder.empty()){ //param holder contains function
        int offset= -8 - param_holder.size() * 2;
        for(const auto &sym: param_holder) {
            bool inserted = sym_tab.insert(sym.getName(), "ID", llo);
            SymbolInfo* p = sym_tab.lookUp(sym.getName());
            p->data_type = sym.getType();
            p->offset=offset;
            offset+=2;
        }
    }
    param_holder.clear();
}
                        statements RCURL
{
    print_parser_grammar("compound_statement", "LCURL statements RCURL");
    $$ = new putil();
    $$->data = "{\n" + $3->data + "\n}";
    print_parser_text($$->data);
    sym_tab.printAllScopes(plo);
    sym_tab.exitScope();
    delete $3;
}
                    |   LCURL
{
    sym_tab.enterScope();
}
                        RCURL
{
    print_parser_grammar("compound_statement", "LCURL RCURL");
    $$ = new putil();
    $$->data = "{}";
    print_parser_text($$->data);
    sym_tab.printAllScopes(plo);
    sym_tab.exitScope();
}
                    ;
var_declaration     :   type_specifier declaration_list SEMICOLON
{
    print_parser_grammar("var_declaration", "type_specifier declaration_list SEMICOLON");
    if($1->data == "void"){
        print_void_var();
    }
    $$ = new putil();
    $$->data = $1->data + " " + $2->data + ";";
    print_parser_text($$->data);
    //set data types in symbol info
    vector<string> vars = split($2->data, ',');
    for(const auto &s: vars){
        size_t loc = s.find("[");
        string name;
        string dtype;
        //ICG var
        bool is_ara = false;
        if(loc==string::npos) {
            name=s;
            dtype=$1->data;
        }
        else {
            name=s.substr(0, loc);
            dtype="ara_"+$1->data;
            is_ara = true; //ara_len already set in decl_list
        }
        SymbolInfo* sym = sym_tab.lookUp(name);
        if(!sym->data_type.empty()) continue; // if second time declaration do nothing (error already printed)
        sym->data_type = dtype;
        string code;
        // 4 cases: global ara, global var, local ara, local var
        if(sym->is_global){
            sym->global_name = newTemp();
            if (is_ara) code = sym->global_name + " DW " + sym->ara_len 
            + " DUP (0) ; declare variable " + name + "\n";
            else code = sym->global_name + " DW 0 ; declare variable " + name + "\n";
            
        }else if(is_ara){
            stack_offset+=2;
            code="PUSH 0 ; line " + to_string(yylineno)+ 
            " declare array " + name + ", offset: " + 
            to_string(stack_offset) +"\n";
            sym->offset = stack_offset;
            for(int i=0; i< (stoi(sym->ara_len)-1);i++){
                stack_offset+=2;
                code+="PUSH 0\n";
            }
        }else{
            stack_offset+=2;
            code="PUSH 0 ; line " + to_string(yylineno) + 
            " declare variable " + name + ", offset: "+ 
            to_string(stack_offset)+ "\n";
            sym->offset = stack_offset;
        }
        aco << code;
    }
    delete $1;
    delete $2;
}
                    ;
type_specifier      :   INT
{
    print_parser_grammar("type_specifier", "INT");
    $$ = new putil();
    $$->data = "int";
    $$->type = "int";
    print_parser_text($$->data);
}
                    |   FLOAT
{
    print_parser_grammar("type_specifier", "FLOAT");
    $$ = new putil();
    $$->data = "float";
    $$->type = "float";
    print_parser_text($$->data);
}
                    |   VOID
{
    print_parser_grammar("type_specifier", "VOID");
    $$ = new putil();
    $$->data = "void";
    $$->type = "void";
    print_parser_text($$->data);
}
                    ;
                    ;
declaration_list    :   declaration_list COMMA ID
{
    $$ = new putil();
    $$->data = $1->data + "," + $3->getName();
    //----Symbol table insertion
    bool inserted = sym_tab.insert($3->getName(), $3->getType(), llo);
    if(inserted == false){
        print_multidecl_var($3->getName());
    }
    print_parser_grammar("declaration_list", "declaration_list COMMA ID");
    print_parser_text($$->data);
    //----Finished symbol table insertion
    delete $1;
    delete $3;
}                   |   declaration_list error COMMA ID
{
    $$ = new putil();
    $$->data = $1->data + "," + $4->getName();
    //----Symbol table insertion
    bool inserted = sym_tab.insert($4->getName(), $4->getType(), llo);
    if(inserted == false){
        print_multidecl_var($4->getName());
    }
    print_parser_grammar("declaration_list", "declaration_list COMMA ID");
    print_parser_text($$->data);
    //----Finished symbol table insertion
    delete $1;
    delete $4;
}
                    |   declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
{
    $$ = new putil();
    $$->data = $1->data + "," + $3->getName() + "[" + $5->getName() + "]";
    //-----Symbol table insertion
    bool inserted = sym_tab.insert($3->getName(), $3->getType(), llo);
    if(inserted == false) {
        print_multidecl_var($3->getName());
    }
    print_parser_grammar("declaration_list", "declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
    print_parser_text($$->data);
    //-----Finished SymbolTable insertion

    //ICG ara_len
    SymbolInfo* sym = sym_tab.lookUp($3->getName());
    sym->ara_len = $5->getName();
    delete $1;
    delete $3;
    delete $5;
}
                    |   ID
{
    $$ = new putil();
    $$->data = $1->getName();
    //-----SymbleTable insertion
    bool inserted = sym_tab.insert($1->getName(), $1->getType(), llo);
    if(inserted == false) {
        print_multidecl_var($1->getName());
    }
    print_parser_grammar("declaration_list", "ID");
    print_parser_text($$->data);
    //------Finished SymbolTable insertion
    delete $1;
}
                    |   ID LTHIRD CONST_INT RTHIRD
{
    $$ = new putil();
    $$->data = $1->getName() + "[" + $3->getName() + "]";
    //-----SymbleTable insertion
    bool inserted = sym_tab.insert($1->getName(), $1->getType(), llo);
    if(inserted == false) {
        print_multidecl_var($1->getName());
    }
    print_parser_grammar("declaration_list", "ID LTHIRD CONST_INT RTHIRD");
    print_parser_text($$->data);
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
                    |   statements error statement
{
    print_parser_grammar("statements", "statements statement");
    $$ = new putil();
    $$->data = $1->data + "\n" + $3->data;
    print_parser_text($$->data);
    delete $1;
    delete $3;
}
                    ;
dummy               :   IF LPAREN expression
{
    elselabel=newLabel();
    aco << "POP AX\n"
        << "CMP AX, 0\n"
        << "JE " << elselabel << "\n";
}
                        RPAREN statement
{
    $$=new putil();
    $$->data="if(" + $3->data + ")" + $6->data;
    string exitlabel=newLabel();
    exitlabels.push_back(exitlabel);
    aco << "JMP " << exitlabel <<"\n";
    delete $3;
    delete $6;
}
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
                    |   FOR LPAREN expression_statement
{
    for_check=newLabel();
    for_body=newLabel();
    for_update=newLabel();
    for_exit=newLabel();
    aco << for_check << ": ; condition check label\n";
}
                        expression_statement
{
    aco << "CMP AX, 0\n" // expression_statement popped in AX
        << "JNE " << for_body << " ; if true then enter body\n"
        << "JMP " << for_exit << " ; else exit\n"
        << for_update << ": ; update label\n";
} 
                        expression
{
    aco << "POP AX ; pop update expression\n"; //since no semicolon
    aco << "JMP " << for_check <<" ; check if condition holds\n";
}
                        RPAREN
{
    aco << for_body << ": ; for body label\n";
} 
                        statement
{
    print_parser_grammar("statement", "FOR LPAREN expression_statement expression_statement expression RPAREN statement");
    $$ = new putil();
    $$->data = "for(" + $3->data + $5->data + $7->data + ")" + $11->data;
    print_parser_text($$->data);
    //ICG for
    aco << "JMP " << for_update <<"\n"
        << for_exit << ":\n";
    delete $3;
    delete $5;
    delete $7;
    delete $11;
}
                    |   dummy %prec LOWER_THAN_ELSE
{
    print_parser_grammar("statement", "IF LPAREN expression RPAREN statement");
    $$ = new putil();
    $$->data = $1->data;
    print_parser_text($$->data);
    aco << exitlabels.back() << ": ; if condition false\n";
    if(!elselabel.empty()){
        aco<<elselabel<<":\n";
        elselabel.clear();
    }
    exitlabels.pop_back();
    delete $1;
}
                    |   dummy ELSE
{
    aco << elselabel <<": ; else block \n";
    elselabel.clear();
}
                        statement
{
    print_parser_grammar("statement", "IF LPAREN expression RPAREN statement ELSE statement");
    $$ = new putil();
    $$->data = $1->data + "else " + $4->data;
    print_parser_text($$->data);
    aco  << exitlabels.back() <<":\n";
    exitlabels.pop_back();
    delete $1;
    delete $4;
}
                    |   WHILE LPAREN
{
    while_check=newLabel();
    while_body=newLabel();
    while_exit=newLabel();
    aco << while_check << ": ; while condition check label\n";
}
                        expression
{
    aco << "POP AX ; pop condition value\n"; // since no semicolon, expression remains in stack
    aco << "CMP AX, 0\n"
        << "JNE " << while_body<<"\n"
        << "JMP " << while_exit <<"\n";
} 
                        RPAREN
{
    aco << while_body << ": ; while body label\n";
}
                        statement
{
    print_parser_grammar("statement", "WHILE LPAREN expression RPAREN statement");
    $$ = new putil();
    $$->data = "while(" + $4->data + ")" + $8->data;
    print_parser_text($$->data);
    aco << "JMP " << while_check << "\n"
        << while_exit << ": ; while exit label\n";
    delete $4;
    delete $8;
}
                    |   PRINTLN LPAREN ID RPAREN SEMICOLON
{
    print_parser_grammar("statement", "PRINTLN LPAREN ID RPAREN SEMICOLON");
    $$ = new putil();
    $$->data = "printf(" + $3->getName() + ");";
    SymbolInfo* sym = sym_tab.lookUp($3->getName());
    if(sym==nullptr){
        print_undecl_var($3->getName());
    }
    print_parser_text($$->data);
    //ICG PRINTLN

    if(sym->is_global){
        aco << "MOV AX, " << sym->global_name << "\n";
    }else{
        aco << "MOV AX, [BP-" << sym->offset << "]" << "\n";
    }
    aco << "CALL DAX" << " ; line " << yylineno 
        << ": printf("<< $3->getName() << ")\n"; 
    delete $3;
}
                    |   RETURN expression SEMICOLON
{
    print_parser_grammar("statement", "RETURN expression SEMICOLON");
    $$ = new putil();
    $$->data = "return " + $2->data + ";";
    ret_type_holder.push_back($2->type);
    print_parser_text($$->data);
    //ICG return
    aco << "POP DX ; save return value in dx\n"
        << "JMP " << retlabel <<"\n";
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
    //ICG
    aco << "POP AX ; expression end\n";
    delete $1;
}
                        ;
variable            :   ID
{
    print_parser_grammar("variable", "ID");
    $$ = new putil();
    $$->data = $1->getName();
    SymbolInfo* ret = sym_tab.lookUp($1->getName());
    if(ret == nullptr){
        print_undecl_var($1->getName());
        $$->type = "ERR";
    }else{
        if(ret->data_type.find("ara")==0){ //if data type starts with ara (ara_int, ara_float)
            print_inv_ara_assignment(ret->getName()); //must contain []
        }
        $$->type = ret->data_type;
    }
    // //ICG var
    // aco << "MOV AX, [BP-"<<ret->offset<<"]\n"<<"PUSH AX\n";
    // print_parser_text($$->data);
    delete $1;
}
                    |   ID LTHIRD expression RTHIRD
{
    print_parser_grammar("variable", "ID LTHIRD expression RTHIRD");
    $$ = new putil();
    $$->data = $1->getName() + "[" + $3->data + "]";
    SymbolInfo *ret = sym_tab.lookUp($1->getName());
    bool is_idx_int = $3->type == "CONST_INT" ||  $3->type == "int";
    if(ret == nullptr){ //not declared yet
        print_undecl_var($1->getName());
        $$->type="ERR";
    }else if (ret->data_type.find("ara")!=0){//data_type doesn't begin with ara_, so not an ara
        print_not_an_ara($1->getName());
    } else if(!is_idx_int){ //Invalid index
        print_invalid_ara_idx();
    }
    $$->type = ret->data_type;
    print_parser_text($$->data);
    //ICG ara
    // int start_offset = ret->offset;
    // aco <<"POP AX\n" //contains expression
    //     <<"MOV BX, 2"<<"\n"
    //     <<"CWD\nMUL AX\n" //ax contains 2*expression
    //     <<"MOV BX, "<<start_offset<<"\n"
    //     <<"ADD AX, BX\n" //ax contains proper offset
    //     <<"PUSH [BP-AX]\n";

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
    string v = $1->data;
    SymbolInfo* sym = parse_var($1->data);
    if($3->type=="void") print_void_func_in_expr(); //don't check anything else
    else if(sym!=nullptr && !match_types(sym->data_type, $3->type)){ //was declared before, but type mismatch
        print_type_mismatch();
    }
    $$ = new putil();
    $$->data = $1->data + "=" + $3->data;
    $$->type = $3->type;
    print_parser_text($$->data);
    //ICG ASSIGNOP
    bool is_ara = sym->data_type.find("ara")!=string::npos;
    if(is_ara){ // ID[expr] = logic_expr
        aco << "POP CX ; line " << yylineno << " cx = rhs\n"
            << "POP AX ; ax = ara index for " << $1->data << "\n"
            << "SHL AX, 1 ; ax = 2*ara idx\n";

        if(sym->is_global){
            aco << "MOV BX, AX\n"
            << "MOV ["<<sym->global_name<<"+BX], CX\n";
        }else{
            aco << "MOV SI, " << sym->offset << " ; si = ara base offset\n"
            << "ADD SI, AX ; SI = proper offset for " << $1->data <<"\n"
            << "NEG SI\n"
            << "MOV [BP+SI], CX ; " << $1->data << " assigned\n";
        }
            aco << "PUSH CX ; "<< $$->data <<" expression stored\n";
            //won't work with sub bx, ax; mov [bx], cx!
            //bx has ds as segment address, bp has ss
    }else{
        aco << "POP AX\n";
        if(sym->is_global){
            aco << "MOV " << sym->global_name << ", AX ; line " << yylineno << ": "<< $1->data << " assigned\n";   
        }else{
            aco << "MOV [BP-"<<sym->offset<<"], AX ; line " << yylineno << ": "<< $1->data << " assigned\n";
        }
        aco << "PUSH AX ; " << $$->data << " expression stored\n";
    }
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
{   //short circuit baki
    print_parser_grammar("logic_expression", "rel_expression LOGICOP rel_expression");
    $$ = new putil();
    $$->data = $1->data + $2 + $3->data;
    $$->type = "CONST_INT";
    print_parser_text($$->data);
    //ICG logicop
    aco << "POP BX ; line " << yylineno << " logicop\n"
        << "POP AX\n";
    string exit_label = newLabel();
    string logic_label = newLabel();
    string logicop($2);
    if(logicop=="&&"){
        aco << "CMP AX, 0\n"
            << "JE " << logic_label <<"\n"
            << "CMP BX, 0\n"
            << "JE " << logic_label <<"\n"
            << "PUSH 1\n" // true
            << "JMP " << exit_label << "\n"
            << logic_label << ":\n"
            << "PUSH 0\n"
            << exit_label <<": ; " << $$->data << " parsed \n";
    }else{
        aco << "CMP AX, 0\n"
            << "JNE " << logic_label <<"\n"
            << "CMP BX, 0\n"
            << "JNE " << logic_label <<"\n"
            << "PUSH 0\n" //false
            << "JMP " << exit_label << "\n"
            << logic_label <<":\n"
            << "PUSH 1\n"
            << exit_label <<": ; " << $$->data << " parsed \n";
    }
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
    $$->type = "CONST_INT";
    print_parser_text($$->data);
    string relop($2);
    //ICG relop
    aco << "POP BX ; line " << yylineno << " relop \n" << "POP AX\n"
        << "CMP AX, BX\n";
    string true_label = newLabel();
    string false_label = newLabel();
    if(relop=="<="){ //ZF=1 || SF!=OF
        aco << "JLE " << true_label << "\n";
    }else if(relop==">="){ // SF=OF
        aco << "JGE " << true_label << "\n";
    }else if(relop=="<"){ // SF!=OF
        aco << "JL " << true_label << "\n";
    }else if(relop==">"){ // ZF=0 && SF=OF
        aco << "JG " << true_label << "\n";
    }else if(relop=="=="){ // ZF=1
        aco << "JE " << true_label << "\n";
    }else if(relop=="!="){ //ZF=0
        aco << "JNE " << true_label << "\n";
    }
    aco << "PUSH 0\n" << "JMP " << false_label << "\n"
    << true_label << ":\nPUSH 1\n" << false_label <<": ; "
    << $$->data <<" parsed\n";
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
    $$->type = upcast_type($1->type, $3->type);
    print_parser_text($$->data);
    //ICG ADDOP
    aco << "POP BX\nPOP AX\n";
    if($2[0]=='+'){
        aco <<"ADD AX, BX\nPUSH AX\n";
    }else{
        aco <<"SUB AX, BX\nPUSH AX\n";
    }
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
    //div/mod by zero check
    if($3->data=="0"){
        if($2[0]=='%') print_mod_by_zero();
        else if($2[0]=='*') print_div_by_zero();
    }
    //void func check
    if($3->type=="void") print_void_func_in_expr();
    if($2[0]=='%'){
        $$->type="CONST_INT"; 
        bool lint = $1->type=="CONST_INT"||$1->type=="int"||$1->type=="ara_int";
        bool rint = $3->type=="CONST_INT"||$3->type=="int"||$3->type=="ara_int";
        if (!lint || !rint) {
            print_mod_mismatch();
        }
    }else{
        $$->type = upcast_type($1->type, $3->type);
    }
    print_parser_text($$->data);
    //ICG MUL
    aco << "POP BX\nPOP AX\nCWD ; line " << yylineno << " MULOP\n";
    switch($2[0]){
        case '*':
            aco << "MUL BX\nPUSH AX\n";
            break;
        case '/':
            aco << "DIV BX\nPUSH AX\n";
            break;
        case '%':
            aco << "DIV BX\nPUSH DX\n";
            break;
    }
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
    $$->type = $2->type;
    print_parser_text($$->data);
    //ICG ADDOP
    if($1[0]=='-'){
        aco << "POP AX\nNEG AX\nPUSH AX\n";
    }
    delete $1;
    delete $2;
}
                    |   NOT unary_expression
{
    print_parser_grammar("unary_expression", "NOT unary_expression");
    $$ = new putil();
    $$->data = "!"+$2->data;
    $$->type = $2->type;
    print_parser_text($$->data);
    //ICG NOT
    aco << "POP AX\nNOT AX\nPUSH AX\n";
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

    //ICG var
    SymbolInfo* sym=parse_var($1->data);
    bool is_ara= sym->data_type.find("ara")!=string::npos;
    if(is_ara){
    aco <<"POP AX ; ax = ara idx for " << $1->data << "\n" //contains expression: ID [expr]
        <<"SHL AX, 1 ; ax = 2*ara idx\n"; //ax contains 2*expression

        if(sym->is_global){
            aco << "MOV BX, AX\n"
                << "PUSH ["<<sym->global_name<<"+BX] ;" << $1->data << " pushed in stack \n";
        }else{
            aco <<"MOV SI, "<<sym->offset<<" ; si = ara base offset\n"
            <<"ADD SI, AX ; proper offset for " << $1->data << "\n" //si contains proper offset
            <<"NEG SI\n"
            <<"PUSH [BP+SI] ; " << $1->data <<" pushed in stack\n";
        }

    }else{
        if(sym->is_global){
            aco << "PUSH " << sym->global_name << $1->data << " ; pushed in stack \n";
        }
        else{
            aco << "PUSH [BP-"<<sym->offset<<"] ; " << $1->data << " pushed in stack \n"; 
        }
    }
    delete $1;
}
                    |   ID LPAREN argument_list RPAREN
{
    print_parser_grammar("factor", "ID LPAREN argument_list RPAREN");
    $$ = new putil();
    $$->data = $1->getName() + "(" + $3->data + ")";
    SymbolInfo* sym = sym_tab.lookUp($1->getName());
    if(sym==nullptr){
        print_undef_func($1->getName());
        $$->type = "ERR";
    }else{
        $$->type = sym->ret_type;
        if(!sym->is_func) print_not_a_func($1->getName()); //something other than function
        // else if(!sym->func_defined) print_undef_func($1->getName());//declared, not defined(decl enough)
        else if(arg_type_holder.size()!=sym->param_list.size()){ //declared, defined?, arglens no match
            print_param_len_mismatch($1->getName());
        }else{ //arg lens matched, now validate
            validate_arg_type(sym, arg_type_holder);
        }
    }
    arg_type_holder.clear();
    print_parser_text($$->data);
    //ICG func call
    aco << "CALL " << $1->getName() << " ; line " << yylineno << " , function call\n";
    aco << "PUSH DX ; return value pushed\n";
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
    $$->type = "CONST_INT";
    print_parser_text($$->data);  
    //ICG CONST_INT
    aco << "PUSH " + $1->getName() + "\n";
    delete $1;
}
                    |   CONST_FLOAT
{
    print_parser_grammar("factor", "CONST_FLOAT");
    $$ = new putil();
    $$->data = $1->getName();
    $$->type = "CONST_FLOAT";
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
    //ICG incop
    SymbolInfo* sym=parse_var($1->data);
    bool is_ara = sym->data_type.find("ara")!=string::npos;
    if(is_ara){
        aco << "POP AX ; ax=idx of " << $1->data << "\n"
        << "SHL AX, 1 ; ax=2*idx\n";
        if(sym->is_global){
            aco << "MOV BX, AX\n"
            << "PUSH ["<<sym->global_name<<"+BX] ; " << $1->data << " pushed in stack\n"
            << "INC WORD PTR["<<sym->global_name<<"+BX]\n";
        }else{
            aco << "MOV SI, " << sym->offset << " ; si=base offset \n"
            << "ADD SI, AX ; si=proper offset\n"
            << "NEG SI\n"
            << "PUSH [BP+SI] ; " << $1->data << " pushed in stack\n"
            << "INC WORD PTR[BP+SI]\n";
        } 
    }else{
        if(sym->is_global){
            aco << "PUSH " <<sym->global_name << " ; " << $1->data << " pushed\n"
                << "INC WORD PTR["<<sym->global_name<<"+BX]\n";
        }else{
            aco << "PUSH [BP-"<<sym->offset<<"] ; " << $1->data << " pushed\n"
                << "INC WORD PTR[BP-"<<sym->offset<<"]\n"; 
        }
        
    }
    delete $1;
}
                    |   variable DECOP
{
    print_parser_grammar("factor", "variable DECOP");
    $$ = new putil();
    $$->data = $1->data + "--";
    $$->type = "DECOP";
    print_parser_text($$->data);
    //ICG decop
    SymbolInfo* sym=parse_var($1->data);
    bool is_ara = sym->data_type.find("ara")!=string::npos;
    if(is_ara){
        aco << "POP AX ; ax=idx of " << $1->data << "\n"
        << "SHL AX, 1 ; ax=2*idx\n";
        if(sym->is_global){
            aco << "MOV BX, AX\n"
            << "PUSH ["<<sym->global_name<<"+BX] ; " << $1->data << " pushed in stack\n"
            << "DEC WORD PTR["<<sym->global_name<<"+BX]\n";
        }else{
            aco << "MOV SI, " << sym->offset << " ; si=base offset \n"
            << "ADD SI, AX ; si=proper offset\n"
            << "NEG SI\n"
            << "PUSH [BP+SI] ; " << $1->data << " pushed in stack\n"
            << "DEC WORD PTR[BP+SI]\n";
        } 
    }else{
        if(sym->is_global){
            aco << "PUSH " <<sym->global_name << " ; " << $1->data << " pushed\n"
                << "DEC WORD PTR["<<sym->global_name<<"+BX]\n";
        }else{
            aco << "PUSH [BP-"<<sym->offset<<"] ; " << $1->data << " pushed\n"
            << "DEC WORD PTR[BP-"<<sym->offset<<"]\n"; 
        }
    }
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
    arg_type_holder.push_back($3->type);
    print_parser_text($$->data);
    delete $1;
    delete $3;
}
                    |   logic_expression
{
    print_parser_grammar("arguments", "logic_expression");
    $$ = new putil();
    $$->data = $1->data;
    arg_type_holder.push_back($1->type);
    print_parser_text($$->data);
    delete $1;
}
                    ;
%%

main(int argc, char* argv[])
{
    init_asm_file();
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
    aco.close();
    peep_optimize();
    exit(0);
}
