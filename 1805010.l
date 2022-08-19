%option noyywrap yylineno
%x BS
%x SLC
%x MLC
%x UNS

%{
    #include<iostream>
    #include<string>
    #include<fstream>
    #include "SymbolTable.h"
    #include "SymbolInfo.h"
    #include "y.tab.h"
    using namespace std;

    string sbuff;
    string lbuff;
    const int BUCKET = 7;
    int error_count=0;
    extern int err_count;
    extern ofstream llo;
    extern ofstream lto;
    extern ofstream peo;
    extern ofstream plo;
    extern SymbolTable sym_tab;

    char process_charptr(const char* lex){
        char ch;
        if(lex[1]=='\\'){
            switch (lex[2]){
                case '\\':
                    ch = '\\';
                    break;
                case 'n':
                    ch = '\n';
                    break;
                case 't':
                    ch = '\t';
                    break;
                case 'a':
                    ch = '\a';
                    break;
                case 'f':
                    ch = '\f';
                    break;
                case 'r':
                    ch = '\r';
                    break;
                case 'b':
                    ch = '\b';
                    break;
                case 'v':
                    ch = '\v';
                    break;
                case '0':
                    ch = '\0';
                    break;
            }
        }else{
            ch = lex[1];
        }
        return ch;
    }

    
    
    void print_log(const char* TOK, const char* lex, int line_no){
        llo << "Line no " << line_no 
        << ": Token <" << TOK 
        << "> Lexeme " << lex 
        <<" found" << endl << endl;
        return;
    }

    void print_tok(const char* TOK, const char* lex=NULL){
        if(lex!=NULL)
            lto << "<" << TOK
                 << ", " << lex
                 << "> ";
        else
            lto << "<" << TOK <<"> "; 
        return;
    }

    void print_char_log(const char* TOK, const char* lex, int line_no){
        llo << "Line no " << line_no 
        << ": Token <" << TOK 
        << "> Lexeme " << lex 
        <<" found";
        char ch = process_charptr(lex);
        llo << " --> <" << TOK
                << ", " << ch
                << ">" << endl << endl;
        return;
    }

    void print_char_tok(const char* TOK, const char* lex){
        char ch = process_charptr(lex);
        lto << "<" << TOK
                << ", " << ch
                << "> ";
        return;
    }

   void print_str_log(const char* TOK, const char* lex, int line_no){
        llo << "Line no " << line_no 
        << ": Token <" << TOK 
        << "> Lexeme " << lbuff 
        <<" found" << " --> <" 
        << TOK << ", " << sbuff
        << ">" << endl << endl;;
        lbuff.clear();
        sbuff.clear();
        return;
    }

    void print_str_tok(const char* TOK, const char* lex){
        lto << "<" << TOK
                << ", " << sbuff 
                << "> ";
        return;
    }
    void print_unk_char(string name){
        err_count++;
        peo << "Error at line " << yylineno << ": " << "Unrecognized character " << name << "\n" << endl;
        plo << "Error at line " << yylineno << ": " << "Unrecognized character " << name << "\n" << endl;
    }
    void print_errflt(string name){
        err_count++;
        peo << "Error at line " << yylineno << ": " << "Invalid floating point number" << name << "\n" << endl;
        plo << "Error at line " << yylineno << ": " << "Invalid floating point number" << name << "\n" << endl;
    }
    void logerr_tmdp(){
        llo << "Error at line no " << yylineno
                <<": Too many decimal points "
                <<yytext<<endl<<endl;
    }

    void logerr_flt(){
        llo << "Error at line no "<<yylineno
                << ": Ill formed number "
                <<yytext<<endl<<endl;
    }
    void logerr_invs(){
        llo << "Error at line no "<<yylineno
                << ": Invalid prefix on ID or invalid suffix on Number "
                << yytext << endl << endl;
    }
    void logerr_mchar(){
        llo << "Error at line no "<<yylineno
                << ": Multi character constant error "
                << yytext << endl << endl;
    }
    void logerr_unchar(){
        llo << "Error at line no "<<yylineno
                << ": Unterminated character "
                << yytext << endl << endl;
    }
    void logerr_emchar(){
        llo << "Error at line no "<<yylineno
                << ": Empty character constant error "
                << yytext << endl << endl;
    }
    void logerr_unstr(const char* str){
        llo << "Error at line no "<<yylineno
                << ": Unterminated string "
                << str << endl << endl;
    }
    void logerr_uncmnt(const char* str){
        llo << "Error at line no "<<yylineno
                << ": Unterminated comment "
                << str << endl << endl;
    }
    void logerr_unk(){
        llo << "Error at line no "<<yylineno
                << ": Unrecognized character "
                << yytext << endl << endl;
    }
    void logdone(){
        sym_tab.printAllScopes(llo);
        llo << "Total lines: "<<yylineno<<endl;
        llo << "Total errors: "<<error_count<<endl;
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
CHAR        '[^"\\""\n"]'|'{ESCSEQ}'
ADDOP       [+-]
MULOP       [*/%]
INCOP       "++"
DECOP       "--"
RELOP       "<="|">="|"<"|">"|"=="|"!="
ASSIGNOP    "="|"+="|"-="|"*="|"/="
LOGICOP     "&&"|"||"
NOT         "!"
LPAREN      "("
RPAREN      ")"
LCURL       "{"
RCURL       "}"
LTHIRD      "["
RTHIRD      "]"
COMMA       ","
SEMICOLON   ";"
CHELP       {LETTER}|{DIGIT}|[;_]
ERRTMDP     ({DIGIT}*(\.)+{DIGIT}*)+("\n")?
ERRINVS     {DIGIT}+[a-zA-Z_]+
ERRFLT1     {FLOAT}[\.]+{ERRTMDP}
ERRFLT2     {DIGIT}*(\.{DIGIT}*){1}[\.]+
ERRFLT3     {DIGIT}*(\.{DIGIT}*)?([Ee][+-]?{DIGIT}+)?[\.]+{DIGIT}*
ERRFLT      ({ERRFLT1}|{ERRFLT2}|{ERRFLT3})("\n")?
ERRMCHAR    '(.|{ESCSEQ}){2,}'("\n")?
ERRUNCHAR   ('({CHELP}|{ESCSEQ})*|({CHELP}|{ESCSEQ})*'|'\\')("\n")?
ERREMCHAR   ''("\n")?
%%
{WS}        {}
{NL}        {}

"if"        {
                print_tok("IF");
                print_log("IF", yytext, yylineno);
                return IF;
            }

"for"       {
                print_tok("FOR");
                print_log("FOR", yytext, yylineno);
                return FOR;
            }

"do"        {
                print_tok("DO");
                print_log("DO", yytext, yylineno);
                return DO;
            }

"int"       {
                print_tok("INT");
                print_log("INT", yytext, yylineno);
                return INT;
            }

"float"     {
                print_tok("FLOAT");
                print_log("FLOAT", yytext, yylineno);
                return FLOAT;
            }

"void"      {
                print_tok("VOID");
                print_log("VOID", yytext, yylineno);
                return VOID;
            }

"switch"    {
                print_tok("SWITCH");
                print_log("SWITCH", yytext, yylineno);
                return SWITCH;
            }

"default"   {
                print_tok("DEFAULT");
                print_log("DEFAULT", yytext, yylineno);
                return DEFAULT;
            }

"else"      {
                print_tok("ELSE");
                print_log("ELSE", yytext, yylineno);
                return ELSE;
            }

"while"     {
                print_tok("WHILE");
                print_log("WHILE", yytext, yylineno);
                return WHILE;
            }

"break"     {
                print_tok("BREAK");
                print_log("BREAK", yytext, yylineno);
                return BREAK;
            }

"char"      {
                print_tok("CHAR");
                print_log("CHAR", yytext, yylineno);
                return CHAR;
            }
        
"double"    {
                print_tok("DOUBLE");
                print_log("DOUBLE", yytext, yylineno);
                return DOUBLE;
            }

"return"    {
                print_tok("RETURN");
                print_log("RETURN", yytext, yylineno);
                return RETURN;
            }

"case"      {
                print_tok("CASE");
                print_log("CASE", yytext, yylineno);
                return CASE;
            }

"continue"  {
                print_tok("CONTINUE");
                print_log("CONTINUE", yytext, yylineno);
                return CONTINUE;
            }
"printf"|"println"    {
                return PRINTLN;
            }

{INT}       {
                print_tok("CONST_INT", yytext);
                print_log("CONST_INT", yytext, yylineno);
                yylval.sym_info = new SymbolInfo(yytext, "CONST_INT");
                return CONST_INT;
            }

{FLOAT}     {
                print_tok("CONST_FLOAT", yytext);
                print_log("CONST_FLOAT", yytext, yylineno);
                yylval.sym_info = new SymbolInfo(yytext, "CONST_FLOAT");
                return CONST_FLOAT;
            }

{CHAR}      {
                print_char_tok("CONST_CHAR", yytext);
                print_char_log("CONST_CHAR", yytext, yylineno);
                yylval.sym_info = new SymbolInfo(yytext, "CONST_CHAR");
                return CONST_CHAR;
            }

{ADDOP}     {
                print_tok("ADDOP", yytext);
                print_log("ADDOP", yytext, yylineno);
                yylval.op = strdup(yytext);
                return ADDOP;
            }

{MULOP}     {
                print_tok("MULOP", yytext);
                print_log("MULOP", yytext, yylineno);
                yylval.op = strdup(yytext);
                return MULOP;
            }

{ID}        {
                print_tok("ID", yytext);
                print_log("ID", yytext, yylineno);
                yylval.sym_info = new SymbolInfo(yytext, "ID");
                return ID;
            }

{INCOP}     {
                print_tok("INCOP", yytext);
                print_log("INCOP", yytext, yylineno);
                return INCOP;
            }

{DECOP}     {
                print_tok("DECOP", yytext);
                print_log("DECOP", yytext, yylineno);
                return DECOP;
            }
            
{RELOP}     {
                print_tok("RELOP", yytext);
                print_log("RELOP", yytext, yylineno);
                yylval.op = strdup(yytext);
                return RELOP;
            }

{ASSIGNOP}  {
                print_tok("ASSIGNOP", yytext);
                print_log("ASSIGNOP", yytext, yylineno);
                yylval.op = strdup(yytext);
                return ASSIGNOP;
            }

{LOGICOP}   {
                print_tok("LOGICOP", yytext);
                print_log("LOGICOP", yytext, yylineno);
                yylval.op = strdup(yytext);
                return LOGICOP;
            }

{NOT}       {
                print_tok("NOT", yytext);
                print_log("NOT", yytext, yylineno);
                yylval.op = strdup(yytext);
                return NOT;
            }

{LPAREN}    {
                print_tok("LPAREN", yytext);
                print_log("LPAREN", yytext, yylineno);
                return LPAREN;
            }

{RPAREN}    {
                print_tok("RPAREN", yytext);
                print_log("RPAREN", yytext, yylineno);
                return RPAREN;
            }

{LCURL}     {
                print_tok("LCURL", yytext);
                print_log("LCURL", yytext, yylineno);
                return LCURL;  
            }

{RCURL}     {
                print_tok("RCURL", yytext);
                print_log("RCURL", yytext, yylineno);
                return RCURL;
            }

{LTHIRD}    {
                print_tok("LTHIRD", yytext);
                print_log("LTHIRD", yytext, yylineno);
                return LTHIRD;
            }

{RTHIRD}    {
                print_tok("RTHIRD", yytext);
                print_log("RTHIRD", yytext, yylineno);
                return RTHIRD;
            }

{COMMA}     {
                print_tok("COMMA", yytext);
                print_log("COMMA", yytext, yylineno);
                return COMMA;
            }

{SEMICOLON} {
                print_tok("SEMICOLON", yytext);
                print_log("SEMICOLON", yytext, yylineno);
                return SEMICOLON;
            }

\"          {
                BEGIN BS;
                lbuff.append("\"");
            }
<BS>[^"\\"/"\n"]+ {
                lbuff.append(yytext);
                sbuff.append(yytext);
             }
<BS>(\\\\)  {
                lbuff.append("\\\\");
                sbuff.append("\\");
            }
<BS>(\\n)   {
                lbuff.append("\\n");
                sbuff.append("\n");
            }
<BS>(\\t)   {
                lbuff.append("\\t");
                sbuff.append("\t");
            }
<BS>(\\a)   {
                lbuff.append("\\a");
                sbuff.append("\a");
            }
<BS>(\\f)   {
                lbuff.append("\\f");
                sbuff.append("\f");
            }                                    
<BS>(\\r)   {
                lbuff.append("\\r");
                sbuff.append("\r");
            }
<BS>(\\b)   {
                lbuff.append("\\b");
                sbuff.append("\b");
            }
<BS>(\\v)   {
                lbuff.append("\\v");
                sbuff.append("\v");
            }
<BS>(\\0)   {
                lbuff.append("\\0");
                sbuff.append("\0");
            }
<BS>(\\\")  {
                lbuff.append("\\\"");
                sbuff.append("\"");
            }
<BS>(\\\n)  {
                lbuff.append("\\\n");
            }
<BS>"\n"   {    
                error_count++;
                logerr_unstr(lbuff.c_str());
                lbuff.clear();
                sbuff.clear();
                BEGIN INITIAL;
            }
<BS><<EOF>> {
                error_count++;
                logerr_unstr(lbuff.c_str());
                lbuff.clear();
                sbuff.clear();
                BEGIN INITIAL;
            }               
<BS>(\")    {
                lbuff.append("\"");
                print_str_tok("STRING", lbuff.c_str());
                print_str_log("STRING", sbuff.c_str(), yylineno);
                BEGIN INITIAL;
            }
"//"        {
                BEGIN SLC;
                lbuff.append(yytext);
            }
<SLC>.*  {
                lbuff.append(yytext);
                if(yytext[yyleng-1]!='\\'){
                    print_log("COMMENT", lbuff.c_str(), yylineno);
                    lbuff.clear();
                    BEGIN INITIAL;
                } else lbuff.append("\n");
         }
<SLC>{NL} {}
<SLC><<EOF>> {
                    print_log("COMMENT", lbuff.c_str(), yylineno);
                    lbuff.clear();
                    BEGIN INITIAL;
             }
"/*"    {
            BEGIN MLC;
            lbuff.append(yytext);
        }
<MLC>"*/"   {
                lbuff.append(yytext);
                print_log("COMMENT", lbuff.c_str(), yylineno);
                lbuff.clear();
                BEGIN INITIAL;    
            }
<MLC>.|\n   {
                lbuff.append(yytext);
            }
<MLC><<EOF>> {
                error_count++;
                logerr_uncmnt(lbuff.c_str());
                lbuff.clear();
                BEGIN INITIAL;
             }
{ERRINVS}   {
                error_count++;
                logerr_invs();
            }
{ERRTMDP}   {
                error_count++;
                logerr_tmdp();
            }
{ERRMCHAR}  {
                error_count++;
                logerr_mchar();
            }
{ERREMCHAR} {
                error_count++;
                logerr_emchar();
            }
{ERRUNCHAR} {
                error_count++;
                logerr_unchar();
            }
{ERRFLT}    {
                error_count++;
                logerr_flt();
                print_errflt(yytext);
            }
.           {
                error_count++;
                logerr_unk();
                print_unk_char(yytext);
            }
<<EOF>>     {
                logdone();
                return 0;
            }
%%