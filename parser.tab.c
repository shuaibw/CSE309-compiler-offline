/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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
vector<SymbolInfo> param_holder;
vector<string> arg_type_holder;

void yyerror(string s){
	plo << "Error at line "<< yylineno << ": " << s << "\n" << endl;
    peo << "Error at line "<< yylineno << ": " << s << "\n" << endl;
    err_count++;
}

int yylex(void);
int yyparse(void);


#line 105 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    INT = 259,
    FLOAT = 260,
    VOID = 261,
    ELSE = 262,
    FOR = 263,
    WHILE = 264,
    DO = 265,
    BREAK = 266,
    CHAR = 267,
    DOUBLE = 268,
    RETURN = 269,
    SWITCH = 270,
    CASE = 271,
    DEFAULT = 272,
    CONTINUE = 273,
    PRINTLN = 274,
    INCOP = 275,
    DECOP = 276,
    NOT = 277,
    LPAREN = 278,
    RPAREN = 279,
    LCURL = 280,
    RCURL = 281,
    LTHIRD = 282,
    RTHIRD = 283,
    COMMA = 284,
    SEMICOLON = 285,
    ID = 286,
    CONST_INT = 287,
    CONST_FLOAT = 288,
    CONST_CHAR = 289,
    ERRFLT = 290,
    ADDOP = 291,
    MULOP = 292,
    RELOP = 293,
    LOGICOP = 294,
    ASSIGNOP = 295,
    LOWER_THAN_ELSE = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 36 "parser.y"

    SymbolInfo* sym_info;
    struct putil* pt;
    char *op;

#line 205 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   147

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

#define YYUNDEFTOK  2
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    54,    54,    61,    70,    79,    87,    95,   104,   124,
     144,   143,   190,   189,   227,   241,   251,   263,   273,   272,
     296,   295,   309,   340,   348,   356,   366,   381,   397,   411,
     427,   436,   446,   454,   462,   470,   481,   490,   500,   509,
     521,   531,   538,   547,   565,   586,   595,   614,   623,   635,
     644,   656,   665,   677,   686,   712,   722,   731,   741,   750,
     774,   783,   792,   801,   810,   820,   829,   834,   844
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "INT", "FLOAT", "VOID", "ELSE",
  "FOR", "WHILE", "DO", "BREAK", "CHAR", "DOUBLE", "RETURN", "SWITCH",
  "CASE", "DEFAULT", "CONTINUE", "PRINTLN", "INCOP", "DECOP", "NOT",
  "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "COMMA",
  "SEMICOLON", "ID", "CONST_INT", "CONST_FLOAT", "CONST_CHAR", "ERRFLT",
  "ADDOP", "MULOP", "RELOP", "LOGICOP", "ASSIGNOP", "LOWER_THAN_ELSE",
  "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "$@1", "$@2", "parameter_list", "compound_statement",
  "$@3", "$@4", "var_declaration", "type_specifier", "declaration_list",
  "statements", "statement", "expression_statement", "variable",
  "expression", "logic_expression", "rel_expression", "simple_expression",
  "term", "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-21)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      71,   -75,   -75,   -75,    28,    71,   -75,   -75,   -75,   -75,
       0,   -75,   -75,    23,    18,    11,     1,     8,   -75,    14,
      -6,    24,    44,    51,   -75,    55,    52,    71,   -75,   -75,
      49,    57,   -75,   -75,    55,    54,    58,    99,    63,   -75,
     -75,   -75,    69,    70,    76,   105,    77,   105,   105,   -75,
      26,   -75,   -75,   105,   -75,   -75,    75,    65,   -75,   -75,
      -8,    64,   -75,    72,   -16,    73,   -75,   -75,   -75,   105,
      29,   105,    79,    81,    37,   -75,    90,   105,   105,   -75,
      88,   -75,   -75,   -75,   -75,   105,   -75,   105,   105,   105,
     105,    92,    29,    93,   -75,    95,   -75,   -75,    96,    94,
      97,   -75,   -75,    73,    98,   -75,    99,   105,    99,   103,
     -75,   105,   -75,   119,   115,   -75,   -75,   -75,    99,    99,
     -75,   -75
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    23,    24,    25,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    28,     0,     0,     0,     0,    22,    12,
       0,    17,     0,    26,     9,     0,    10,     0,    16,    29,
       0,    18,    13,     8,     0,    15,     0,     0,     0,    11,
      14,    27,     0,     0,     0,     0,     0,     0,     0,    41,
      43,    61,    62,     0,    34,    32,     0,     0,    30,    33,
      58,     0,    45,    47,    49,    51,    53,    57,    21,     0,
       0,     0,     0,     0,    58,    56,     0,    66,     0,    55,
      28,    19,    31,    63,    64,     0,    42,     0,     0,     0,
       0,     0,     0,     0,    40,     0,    60,    68,     0,    65,
       0,    46,    48,    52,    50,    54,     0,     0,     0,     0,
      59,     0,    44,    36,     0,    38,    39,    67,     0,     0,
      37,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -75,   -75,   -75,   135,   -75,   -75,   -75,   -75,   -75,   -15,
     -75,   -75,    21,     9,   -75,   -75,   -52,   -63,   -47,   -44,
     -74,    56,    53,    59,   -45,   -75,   -75,   -75
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    34,    25,    20,    54,
      37,    38,    55,    56,    14,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    98,    99
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      74,    72,    75,    97,    76,    82,    74,    92,    79,    10,
      32,   101,    83,    84,    10,     1,     2,     3,    26,    39,
      88,     9,    89,    27,    21,    91,     9,    93,    11,   107,
      74,    13,    85,    22,   100,    19,    35,   117,    74,    23,
      74,    74,    74,    74,    24,   105,    15,    17,    18,    77,
      16,    47,    48,    78,   113,    28,   115,    83,    84,    49,
      50,    51,    52,   114,    74,    53,   120,   121,    42,     1,
       2,     3,    29,    43,    44,     1,     2,     3,    30,    45,
      31,    36,    33,   -20,    46,    40,    41,    47,    48,    68,
      31,    81,    69,    70,    86,    49,    50,    51,    52,    71,
      73,    53,    42,     1,     2,     3,    80,    43,    44,    94,
      90,    87,    95,    45,    96,    16,   106,   108,    46,   109,
     110,    47,    48,   111,    31,   112,   118,    47,    48,    49,
      50,    51,    52,   116,    88,    53,    50,    51,    52,   119,
      12,    53,   104,   102,     0,     0,     0,   103
};

static const yytype_int8 yycheck[] =
{
      47,    45,    47,    77,    48,    57,    53,    70,    53,     0,
      25,    85,    20,    21,     5,     4,     5,     6,    24,    34,
      36,     0,    38,    29,    15,    69,     5,    71,     0,    92,
      77,    31,    40,    32,    78,    24,    27,   111,    85,    31,
      87,    88,    89,    90,    30,    90,    23,    29,    30,    23,
      27,    22,    23,    27,   106,    31,   108,    20,    21,    30,
      31,    32,    33,   107,   111,    36,   118,   119,     3,     4,
       5,     6,    28,     8,     9,     4,     5,     6,    27,    14,
      25,    32,    30,    26,    19,    31,    28,    22,    23,    26,
      25,    26,    23,    23,    30,    30,    31,    32,    33,    23,
      23,    36,     3,     4,     5,     6,    31,     8,     9,    30,
      37,    39,    31,    14,    24,    27,    24,    24,    19,    24,
      24,    22,    23,    29,    25,    28,     7,    22,    23,    30,
      31,    32,    33,    30,    36,    36,    31,    32,    33,    24,
       5,    36,    89,    87,    -1,    -1,    -1,    88
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,    43,    44,    45,    46,    47,    54,
      55,     0,    45,    31,    56,    23,    27,    29,    30,    24,
      50,    55,    32,    31,    30,    49,    24,    29,    31,    28,
      27,    25,    51,    30,    48,    55,    32,    52,    53,    51,
      31,    28,     3,     8,     9,    14,    19,    22,    23,    30,
      31,    32,    33,    36,    51,    54,    55,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    26,    23,
      23,    23,    61,    23,    60,    66,    61,    23,    27,    66,
      31,    26,    58,    20,    21,    40,    30,    39,    36,    38,
      37,    61,    59,    61,    30,    31,    24,    62,    68,    69,
      61,    62,    63,    65,    64,    66,    24,    59,    24,    24,
      24,    29,    28,    58,    61,    58,    30,    62,     7,    24,
      58,    58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      48,    47,    49,    47,    50,    50,    50,    50,    52,    51,
      53,    51,    54,    55,    55,    55,    56,    56,    56,    56,
      57,    57,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    59,    59,    60,    60,    61,    61,    62,    62,    63,
      63,    64,    64,    65,    65,    66,    66,    66,    67,    67,
      67,    67,    67,    67,    67,    68,    68,    69,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       0,     3,     3,     1,     1,     1,     3,     6,     1,     4,
       1,     2,     1,     1,     1,     7,     5,     7,     5,     5,
       3,     1,     2,     1,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     2,     2,     1,     1,     4,
       3,     1,     1,     2,     2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
    case 43: /* start  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1211 "parser.tab.c"
        break;

    case 44: /* program  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1217 "parser.tab.c"
        break;

    case 45: /* unit  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1223 "parser.tab.c"
        break;

    case 46: /* func_declaration  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1229 "parser.tab.c"
        break;

    case 47: /* func_definition  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1235 "parser.tab.c"
        break;

    case 50: /* parameter_list  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1241 "parser.tab.c"
        break;

    case 51: /* compound_statement  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1247 "parser.tab.c"
        break;

    case 54: /* var_declaration  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1253 "parser.tab.c"
        break;

    case 55: /* type_specifier  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1259 "parser.tab.c"
        break;

    case 56: /* declaration_list  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1265 "parser.tab.c"
        break;

    case 57: /* statements  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1271 "parser.tab.c"
        break;

    case 58: /* statement  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1277 "parser.tab.c"
        break;

    case 59: /* expression_statement  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1283 "parser.tab.c"
        break;

    case 60: /* variable  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1289 "parser.tab.c"
        break;

    case 61: /* expression  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1295 "parser.tab.c"
        break;

    case 62: /* logic_expression  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1301 "parser.tab.c"
        break;

    case 63: /* rel_expression  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1307 "parser.tab.c"
        break;

    case 64: /* simple_expression  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1313 "parser.tab.c"
        break;

    case 65: /* term  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1319 "parser.tab.c"
        break;

    case 66: /* unary_expression  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1325 "parser.tab.c"
        break;

    case 67: /* factor  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1331 "parser.tab.c"
        break;

    case 68: /* argument_list  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1337 "parser.tab.c"
        break;

    case 69: /* arguments  */
#line 52 "parser.y"
           {delete ((*yyvaluep).pt);}
#line 1343 "parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 55 "parser.y"
{
    print_parser_grammar("start", "program");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    delete (yyvsp[0].pt);
}
#line 1618 "parser.tab.c"
    break;

  case 3:
#line 62 "parser.y"
{
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-1].pt)->data + "\n" + (yyvsp[0].pt)->data;
    print_parser_grammar("program", "program unit");
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-1].pt);
    delete (yyvsp[0].pt);
}
#line 1631 "parser.tab.c"
    break;

  case 4:
#line 71 "parser.y"
{
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    print_parser_grammar("program", "unit");
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 1643 "parser.tab.c"
    break;

  case 5:
#line 80 "parser.y"
{
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    print_parser_grammar("unit", "var_declaration");
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 1655 "parser.tab.c"
    break;

  case 6:
#line 88 "parser.y"
{
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    print_parser_grammar("unit", "func_declaration");
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 1667 "parser.tab.c"
    break;

  case 7:
#line 96 "parser.y"
{
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    print_parser_grammar("unit", "func_definition");
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 1679 "parser.tab.c"
    break;

  case 8:
#line 105 "parser.y"
{
    print_parser_grammar("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-5].pt)->data + " " + (yyvsp[-4].sym_info)->getName() + "(" + (yyvsp[-2].pt)->data + ");";
    bool inserted = sym_tab.insert((yyvsp[-4].sym_info)->getName(), (yyvsp[-4].sym_info)->getType(), llo);
    if(inserted == false) {
        print_multidecl_func((yyvsp[-4].sym_info)->getName());
    }
    else {
        print_parser_text((yyval.pt)->data);
        SymbolInfo* sym = sym_tab.lookUp((yyvsp[-4].sym_info)->getName());
        sym->ret_type = (yyvsp[-5].pt)->data;
        sym->param_list = param_holder;
        sym->is_func = true;
    }
    param_holder.clear();
    delete (yyvsp[-4].sym_info);
    delete (yyvsp[-2].pt);
}
#line 1703 "parser.tab.c"
    break;

  case 9:
#line 125 "parser.y"
{
    print_parser_grammar("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-4].pt)->data + " " + (yyvsp[-3].sym_info)->getName() + "();";
    bool inserted = sym_tab.insert((yyvsp[-3].sym_info)->getName(), (yyvsp[-3].sym_info)->getType(), llo);
    if(inserted == false) {
        print_multidecl_func((yyvsp[-3].sym_info)->getName());
    }
    else {
        print_parser_text((yyval.pt)->data);
        SymbolInfo* sym = sym_tab.lookUp((yyvsp[-3].sym_info)->getName());
        sym->ret_type = (yyvsp[-4].pt)->data;
        sym->is_func = true;
    }
    delete (yyvsp[-4].pt);
    delete (yyvsp[-3].sym_info);
}
#line 1725 "parser.tab.c"
    break;

  case 10:
#line 144 "parser.y"
{   //Function scope not entered yet, insert function to global scope
    bool inserted = sym_tab.insert((yyvsp[-3].sym_info)->getName(), (yyvsp[-3].sym_info)->getType(), llo);
    SymbolInfo* sym = sym_tab.lookUp((yyvsp[-3].sym_info)->getName());
    if(inserted){ //first time definition
        sym->param_list = param_holder;
        sym->func_defined = true;
        sym->is_func = true;
        sym->ret_type = (yyvsp[-4].pt)->data;
    }
    else if(sym->is_func){ //in current scope, sym points to previously declared ID. Now validate
        if(!sym->func_defined){ //was not defined previously, but ret_type, param fixed
            sym->func_defined = true;
            bool param_len_match = sym->param_list.size()==param_holder.size();
            bool ret_type_match = sym->ret_type == (yyvsp[-4].pt)->data;
            if(!ret_type_match){
                print_ret_type_mismatch((yyvsp[-3].sym_info)->getName());
            }
            if(!param_len_match){
                print_param_len_mismatch((yyvsp[-3].sym_info)->getName());
            }
            else{
                validate_param_type(sym, param_holder);
            }
        }else{ //was defined already
            print_multidef_func((yyvsp[-3].sym_info)->getName());
        }
    }else{ // something other than func exists with same name
        print_multidecl_var((yyvsp[-3].sym_info)->getName());
    }
    // Don't clear params, to be inserted in function scope by compound_statement
}
#line 1761 "parser.tab.c"
    break;

  case 11:
#line 176 "parser.y"
{
    print_parser_grammar("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");
    if(!match_types((yyvsp[-6].pt)->data, (yyvsp[0].pt)->type)) print_return_type_mismatch((yyvsp[-5].sym_info)->getName());
    plo << (yyvsp[-6].pt)->data << ", "<<(yyvsp[0].pt)->type<<"\n\n";
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-6].pt)->data + " " + (yyvsp[-5].sym_info)->getName() + "(" + (yyvsp[-3].pt)->data + ")" + (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    
    delete (yyvsp[-6].pt);
    delete (yyvsp[-5].sym_info);
    delete (yyvsp[-3].pt);
    delete (yyvsp[0].pt);
}
#line 1779 "parser.tab.c"
    break;

  case 12:
#line 190 "parser.y"
{
    bool inserted = sym_tab.insert((yyvsp[-2].sym_info)->getName(), (yyvsp[-2].sym_info)->getType(), llo);
    SymbolInfo* sym = sym_tab.lookUp((yyvsp[-2].sym_info)->getName());
    if(inserted){
        sym->func_defined = true;
        sym->is_func = true;
        sym->ret_type = (yyvsp[-3].pt)->data;
        param_holder.clear();
    }
    else if(sym->is_func){ //in current scope, sym points to previously declared ID. Now validate
        if(!sym->func_defined){
            sym->func_defined = true;
            bool ret_type_match = sym->ret_type == (yyvsp[-3].pt)->data;
            if(!ret_type_match){
                print_ret_type_mismatch((yyvsp[-2].sym_info)->getName());
            }
        }else{
            print_multidef_func((yyvsp[-2].sym_info)->getName());
        }
    }else{
        print_multidecl_var((yyvsp[-2].sym_info)->getName());
    }
}
#line 1807 "parser.tab.c"
    break;

  case 13:
#line 214 "parser.y"
{
    print_parser_grammar("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
    if(!match_types((yyvsp[-5].pt)->data, (yyvsp[0].pt)->type)) print_return_type_mismatch((yyvsp[-4].sym_info)->getName());
    plo << (yyvsp[-5].pt)->data << ", "<<(yyvsp[0].pt)->type<<"\n\n";
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-5].pt)->data + " " + (yyvsp[-4].sym_info)->getName() + "()" + (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-5].pt);
    delete (yyvsp[-4].sym_info);
    delete (yyvsp[0].pt);
}
#line 1823 "parser.tab.c"
    break;

  case 14:
#line 228 "parser.y"
{
    if(find_param_by_name(param_holder, (yyvsp[0].sym_info)->getName())){
        print_multidecl_param((yyvsp[0].sym_info)->getName());
    }
    param_holder.emplace_back((yyvsp[0].sym_info)->getName(), (yyvsp[-1].pt)->data);
    print_parser_grammar("parameter_list", "parameter_list COMMA type_specifier ID");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-3].pt)->data +"," + (yyvsp[-1].pt)->data + " " + (yyvsp[0].sym_info)->getName();
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-3].pt);
    delete (yyvsp[-1].pt);
    delete (yyvsp[0].sym_info);
}
#line 1841 "parser.tab.c"
    break;

  case 15:
#line 242 "parser.y"
{
    print_parser_grammar("parameter_list", "parameter_list COMMA type_specifier");
    param_holder.emplace_back("-1", (yyvsp[0].pt)->data);
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-2].pt)->data + "," + (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-2].pt);
    delete (yyvsp[0].pt);
}
#line 1855 "parser.tab.c"
    break;

  case 16:
#line 252 "parser.y"
{
    if(find_param_by_name(param_holder, (yyvsp[0].sym_info)->getName())){
        print_multidecl_param((yyvsp[0].sym_info)->getName());
    }
    param_holder.emplace_back((yyvsp[0].sym_info)->getName(), (yyvsp[-1].pt)->data);
    print_parser_grammar("parameter_list", "type_specifier ID");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-1].pt)->data + " " + (yyvsp[0].sym_info)->getName();

    print_parser_text((yyval.pt)->data);
}
#line 1871 "parser.tab.c"
    break;

  case 17:
#line 264 "parser.y"
{
    print_parser_grammar("parameter_list", "type_specifier");
    param_holder.emplace_back("-1", (yyvsp[0].pt)->data);
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
}
#line 1883 "parser.tab.c"
    break;

  case 18:
#line 273 "parser.y"
{ //Now insert function parameters to scope table if they exist
    sym_tab.enterScope();
    if(!param_holder.empty()){ //param holder contains function
        for(const auto &sym: param_holder) {
            bool inserted = sym_tab.insert(sym.getName(), "ID", llo);
            
            sym_tab.lookUp(sym.getName())->data_type = sym.getType();
        }
    }
    param_holder.clear();
}
#line 1899 "parser.tab.c"
    break;

  case 19:
#line 285 "parser.y"
{
    print_parser_grammar("compound_statement", "LCURL statements RCURL");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "{\n" + (yyvsp[-1].pt)->data + "\n}";
    (yyval.pt)->type = (yyvsp[-1].pt)->type; //for holding return data type
    print_parser_text((yyval.pt)->data);
    sym_tab.printAllScopes(plo);
    sym_tab.exitScope();
    delete (yyvsp[-1].pt);
}
#line 1914 "parser.tab.c"
    break;

  case 20:
#line 296 "parser.y"
{
    sym_tab.enterScope();
}
#line 1922 "parser.tab.c"
    break;

  case 21:
#line 300 "parser.y"
{
    print_parser_grammar("compound_statement", "LCURL RCURL");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "{}";
    print_parser_text((yyval.pt)->data);
    sym_tab.printAllScopes(plo);
    sym_tab.exitScope();
}
#line 1935 "parser.tab.c"
    break;

  case 22:
#line 310 "parser.y"
{
    print_parser_grammar("var_declaration", "type_specifier declaration_list SEMICOLON");
    if((yyvsp[-2].pt)->data == "void"){
        print_void_var();
    }
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-2].pt)->data + " " + (yyvsp[-1].pt)->data + ";";
    print_parser_text((yyval.pt)->data);
    //set data types in symbol info
    vector<string> vars = split((yyvsp[-1].pt)->data, ',');
    for(const auto &s: vars){
        size_t loc = s.find("[");
        string name;
        string dtype;
        if(loc==string::npos) {
            name=s;
            dtype=(yyvsp[-2].pt)->data;
        }
        else {
            name=s.substr(0, loc);
            dtype="ara_"+(yyvsp[-2].pt)->data;
        }
        SymbolInfo* sym = sym_tab.lookUp(name);
        if(!sym->data_type.empty()) continue;
        sym->data_type = dtype;
    }
    delete (yyvsp[-2].pt);
    delete (yyvsp[-1].pt);
}
#line 1969 "parser.tab.c"
    break;

  case 23:
#line 341 "parser.y"
{
    print_parser_grammar("type_specifier", "INT");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "int";
    (yyval.pt)->type = "int";
    print_parser_text((yyval.pt)->data);
}
#line 1981 "parser.tab.c"
    break;

  case 24:
#line 349 "parser.y"
{
    print_parser_grammar("type_specifier", "FLOAT");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "float";
    (yyval.pt)->type = "float";
    print_parser_text((yyval.pt)->data);
}
#line 1993 "parser.tab.c"
    break;

  case 25:
#line 357 "parser.y"
{
    print_parser_grammar("type_specifier", "VOID");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "void";
    (yyval.pt)->type = "void";
    print_parser_text((yyval.pt)->data);
}
#line 2005 "parser.tab.c"
    break;

  case 26:
#line 367 "parser.y"
{
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-2].pt)->data + "," + (yyvsp[0].sym_info)->getName();
    //----Symbol table insertion
    bool inserted = sym_tab.insert((yyvsp[0].sym_info)->getName(), (yyvsp[0].sym_info)->getType(), llo);
    if(inserted == false){
        print_multidecl_var((yyvsp[0].sym_info)->getName());
    }
    print_parser_grammar("declaration_list", "declaration_list COMMA ID");
    print_parser_text((yyval.pt)->data);
    //----Finished symbol table insertion
    delete (yyvsp[-2].pt);
    delete (yyvsp[0].sym_info);
}
#line 2024 "parser.tab.c"
    break;

  case 27:
#line 382 "parser.y"
{
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-5].pt)->data + "," + (yyvsp[-3].sym_info)->getName() + "[" + (yyvsp[-1].sym_info)->getName() + "]";
    //-----Symbol table insertion
    bool inserted = sym_tab.insert((yyvsp[-3].sym_info)->getName(), (yyvsp[-3].sym_info)->getType(), llo);
    if(inserted == false) {
        print_multidecl_var((yyvsp[-3].sym_info)->getName());
    }
    print_parser_grammar("declaration_list", "declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
    print_parser_text((yyval.pt)->data);
    //-----Finished SymbolTable insertion
    delete (yyvsp[-5].pt);
    delete (yyvsp[-3].sym_info);
    delete (yyvsp[-1].sym_info);
}
#line 2044 "parser.tab.c"
    break;

  case 28:
#line 398 "parser.y"
{
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].sym_info)->getName();
    //-----SymbleTable insertion
    bool inserted = sym_tab.insert((yyvsp[0].sym_info)->getName(), (yyvsp[0].sym_info)->getType(), llo);
    if(inserted == false) {
        print_multidecl_var((yyvsp[0].sym_info)->getName());
    }
    print_parser_grammar("declaration_list", "ID");
    print_parser_text((yyval.pt)->data);
    //------Finished SymbolTable insertion
    delete (yyvsp[0].sym_info);
}
#line 2062 "parser.tab.c"
    break;

  case 29:
#line 412 "parser.y"
{
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-3].sym_info)->getName() + "[" + (yyvsp[-1].sym_info)->getName() + "]";
    //-----SymbleTable insertion
    bool inserted = sym_tab.insert((yyvsp[-3].sym_info)->getName(), (yyvsp[-3].sym_info)->getType(), llo);
    if(inserted == false) {
        print_multidecl_var((yyvsp[-3].sym_info)->getName());
    }
    print_parser_grammar("declaration_list", "ID LTHIRD CONST_INT RTHIRD");
    print_parser_text((yyval.pt)->data);
    //------Finished SymbolTable insertion
    delete (yyvsp[-3].sym_info);
    delete (yyvsp[-1].sym_info);
}
#line 2081 "parser.tab.c"
    break;

  case 30:
#line 428 "parser.y"
{
    print_parser_grammar("statements", "statement");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    (yyval.pt)->type = (yyvsp[0].pt)->type; //for return value data type
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2094 "parser.tab.c"
    break;

  case 31:
#line 437 "parser.y"
{
    print_parser_grammar("statements", "statements statement");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-1].pt)->data + "\n" + (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-1].pt);
    delete (yyvsp[0].pt);
}
#line 2107 "parser.tab.c"
    break;

  case 32:
#line 447 "parser.y"
{
    print_parser_grammar("statement", "var_declaration");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2119 "parser.tab.c"
    break;

  case 33:
#line 455 "parser.y"
{
    print_parser_grammar("statement", "expression_statement");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2131 "parser.tab.c"
    break;

  case 34:
#line 463 "parser.y"
{
    print_parser_grammar("statement", "compound_statement");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2143 "parser.tab.c"
    break;

  case 35:
#line 471 "parser.y"
{
    print_parser_grammar("statement", "FOR LPAREN expression_statement expression_statement expression RPAREN statement");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "for(" + (yyvsp[-4].pt)->data + (yyvsp[-3].pt)->data + (yyvsp[-2].pt)->data + ")" + (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-4].pt);
    delete (yyvsp[-3].pt);
    delete (yyvsp[-2].pt);
    delete (yyvsp[0].pt);
}
#line 2158 "parser.tab.c"
    break;

  case 36:
#line 482 "parser.y"
{
    print_parser_grammar("statement", "IF LPAREN expression RPAREN statement");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "if(" + (yyvsp[-2].pt)->data + ")" + (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-2].pt);
    delete (yyvsp[0].pt);
}
#line 2171 "parser.tab.c"
    break;

  case 37:
#line 491 "parser.y"
{
    print_parser_grammar("statement", "IF LPAREN expression RPAREN statement ELSE statement");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "if(" + (yyvsp[-4].pt)->data + ")" + (yyvsp[-2].pt)->data + "else " + (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-4].pt);
    delete (yyvsp[-2].pt);
    delete (yyvsp[0].pt);
}
#line 2185 "parser.tab.c"
    break;

  case 38:
#line 501 "parser.y"
{
    print_parser_grammar("statement", "WHILE LPAREN expression RPAREN statement");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "while(" + (yyvsp[-2].pt)->data + ")" + (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-2].pt);
    delete (yyvsp[0].pt);
}
#line 2198 "parser.tab.c"
    break;

  case 39:
#line 510 "parser.y"
{
    print_parser_grammar("statement", "PRINTLN LPAREN ID RPAREN SEMICOLON");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "printf(" + (yyvsp[-2].sym_info)->getName() + ");";
    SymbolInfo* sym = sym_tab.lookUp((yyvsp[-2].sym_info)->getName());
    if(sym==nullptr){
        print_undecl_var((yyvsp[-2].sym_info)->getName());
    }
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-2].sym_info);
}
#line 2214 "parser.tab.c"
    break;

  case 40:
#line 522 "parser.y"
{
    print_parser_grammar("statement", "RETURN expression SEMICOLON");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "return " + (yyvsp[-1].pt)->data + ";";
    (yyval.pt)->type = (yyvsp[-1].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-1].pt);
}
#line 2227 "parser.tab.c"
    break;

  case 41:
#line 532 "parser.y"
{
    print_parser_grammar("expression_statement", "SEMICOLON");
    (yyval.pt) = new putil();
    (yyval.pt)->data = ";";
    print_parser_text((yyval.pt)->data);
}
#line 2238 "parser.tab.c"
    break;

  case 42:
#line 539 "parser.y"
{
    print_parser_grammar("expression_statement", "expression SEMICOLON");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-1].pt)->data + ";";
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-1].pt);
}
#line 2250 "parser.tab.c"
    break;

  case 43:
#line 548 "parser.y"
{
    print_parser_grammar("variable", "ID");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].sym_info)->getName();
    SymbolInfo* ret = sym_tab.lookUp((yyvsp[0].sym_info)->getName());
    if(ret == nullptr){
        print_undecl_var((yyvsp[0].sym_info)->getName());
        (yyval.pt)->type = "ERR";
    }else{
        if(ret->data_type.find("ara")==0){ //if data type starts with ara (ara_int, ara_float)
            print_inv_ara_assignment(ret->getName()); //must contain []
        }
        (yyval.pt)->type = ret->data_type;
    }
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].sym_info);
}
#line 2272 "parser.tab.c"
    break;

  case 44:
#line 566 "parser.y"
{
    print_parser_grammar("variable", "ID LTHIRD expression RTHIRD");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-3].sym_info)->getName() + "[" + (yyvsp[-1].pt)->data + "]";
    SymbolInfo *ret = sym_tab.lookUp((yyvsp[-3].sym_info)->getName());
    bool is_idx_int = (yyvsp[-1].pt)->type == "CONST_INT" ||  (yyvsp[-1].pt)->type == "int";
    if(ret == nullptr){ //not declared yet
        print_undecl_var((yyvsp[-3].sym_info)->getName());
        (yyval.pt)->type="ERR";
    }else if (ret->data_type.find("ara")!=0){//data_type doesn't begin with ara_, so not an ara
        print_not_an_ara((yyvsp[-3].sym_info)->getName());
    } else if(!is_idx_int){ //Invalid index
        print_invalid_ara_idx();
    }
    (yyval.pt)->type = ret->data_type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-3].sym_info);
    delete (yyvsp[-1].pt);
}
#line 2296 "parser.tab.c"
    break;

  case 45:
#line 587 "parser.y"
{
    print_parser_grammar("expression", "logic_expression");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    (yyval.pt)->type = (yyvsp[0].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2309 "parser.tab.c"
    break;

  case 46:
#line 596 "parser.y"
{
    print_parser_grammar("expression", "variable ASSIGNOP logic_expression");
    string v = (yyvsp[-2].pt)->data;
    size_t loc = v.find("[");
    string var_name = loc==string::npos? v : v.substr(0, loc);
    SymbolInfo* sym = sym_tab.lookUp(var_name);
    if((yyvsp[0].pt)->type=="void") print_void_func_in_expr(); //don't check anything else
    else if(sym!=nullptr && !match_types(sym->data_type, (yyvsp[0].pt)->type)){ //was declared before, but type mismatch
        print_type_mismatch();
    }
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-2].pt)->data + "=" + (yyvsp[0].pt)->data;
    (yyval.pt)->type = (yyvsp[0].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-2].pt);
    delete (yyvsp[0].pt);
}
#line 2331 "parser.tab.c"
    break;

  case 47:
#line 615 "parser.y"
{
    print_parser_grammar("logic_expression", "rel_expression");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    (yyval.pt)->type = (yyvsp[0].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2344 "parser.tab.c"
    break;

  case 48:
#line 624 "parser.y"
{
    print_parser_grammar("logic_expression", "rel_expression LOGICOP rel_expression");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-2].pt)->data + (yyvsp[-1].op) + (yyvsp[0].pt)->data;
    (yyval.pt)->type = "CONST_INT";
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-2].pt);
    delete (yyvsp[-1].op);
    delete (yyvsp[0].pt);
}
#line 2359 "parser.tab.c"
    break;

  case 49:
#line 636 "parser.y"
{
    print_parser_grammar("rel_expression", "simple_expression");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    (yyval.pt)->type = (yyvsp[0].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2372 "parser.tab.c"
    break;

  case 50:
#line 645 "parser.y"
{
    print_parser_grammar("rel_expression", "simple_expression RELOP simple_expression");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-2].pt)->data + (yyvsp[-1].op) + (yyvsp[0].pt)->data;
    (yyval.pt)->type = "CONST_INT";
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-2].pt);
    delete (yyvsp[-1].op);
    delete (yyvsp[0].pt);
}
#line 2387 "parser.tab.c"
    break;

  case 51:
#line 657 "parser.y"
{
    print_parser_grammar("simple_expression", "term");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    (yyval.pt)->type = (yyvsp[0].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2400 "parser.tab.c"
    break;

  case 52:
#line 666 "parser.y"
{
    print_parser_grammar("simple_expression", "simple_expression ADDOP term");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-2].pt)->data + (yyvsp[-1].op) + (yyvsp[0].pt)->data;
    (yyval.pt)->type = upcast_type((yyvsp[-2].pt)->type, (yyvsp[0].pt)->type);
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-2].pt);
    delete (yyvsp[-1].op);
    delete (yyvsp[0].pt);
}
#line 2415 "parser.tab.c"
    break;

  case 53:
#line 678 "parser.y"
{
    print_parser_grammar("term", "unary_expression");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    (yyval.pt)->type = (yyvsp[0].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2428 "parser.tab.c"
    break;

  case 54:
#line 687 "parser.y"
{
    print_parser_grammar("term", "term MULOP unary_expression");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-2].pt)->data  + (yyvsp[-1].op) + (yyvsp[0].pt)->data;
    //div/mod by zero check
    if((yyvsp[0].pt)->data=="0"){
        if((yyvsp[-1].op)[0]=='%') print_mod_by_zero();
        else if((yyvsp[-1].op)[0]=='*') print_div_by_zero();
    }
    //void func check
    if((yyvsp[0].pt)->type=="void") print_void_func_in_expr();
    if((yyvsp[-1].op)[0]=='%'){
        (yyval.pt)->type="CONST_INT"; 
        if ((yyvsp[-2].pt)->type!="CONST_INT" || (yyvsp[0].pt)->type!="CONST_INT") {
            print_mod_mismatch();
        }
    }else{
        (yyval.pt)->type = upcast_type((yyvsp[-2].pt)->type, (yyvsp[0].pt)->type);
    }
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-2].pt);
    delete (yyvsp[-1].op);
    delete (yyvsp[0].pt);
}
#line 2457 "parser.tab.c"
    break;

  case 55:
#line 713 "parser.y"
{
    print_parser_grammar("unary_expression", "ADDOP unary_expression");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-1].op) + (yyvsp[0].pt)->data;
    (yyval.pt)->type = (yyvsp[0].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-1].op);
    delete (yyvsp[0].pt);
}
#line 2471 "parser.tab.c"
    break;

  case 56:
#line 723 "parser.y"
{
    print_parser_grammar("unary_expression", "NOT unary_expression");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "!"+(yyvsp[0].pt)->data;
    (yyval.pt)->type = (yyvsp[0].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2484 "parser.tab.c"
    break;

  case 57:
#line 732 "parser.y"
{
    print_parser_grammar("unary_expression", "factor");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    (yyval.pt)->type = (yyvsp[0].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2497 "parser.tab.c"
    break;

  case 58:
#line 742 "parser.y"
{
    print_parser_grammar("factor", "variable");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    (yyval.pt)->type = (yyvsp[0].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2510 "parser.tab.c"
    break;

  case 59:
#line 751 "parser.y"
{
    print_parser_grammar("factor", "ID LPAREN argument_list RPAREN");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-3].sym_info)->getName() + "(" + (yyvsp[-1].pt)->data + ")";
    SymbolInfo* sym = sym_tab.lookUp((yyvsp[-3].sym_info)->getName());
    if(sym==nullptr){
        print_undef_func((yyvsp[-3].sym_info)->getName());
        (yyval.pt)->type = "ERR";
    }else{
        (yyval.pt)->type = sym->ret_type;
        if(!sym->is_func) print_not_a_func((yyvsp[-3].sym_info)->getName()); //something other than function
        else if(!sym->func_defined) print_undef_func((yyvsp[-3].sym_info)->getName());//declared, not defined
        else if(arg_type_holder.size()!=sym->param_list.size()){ //declared, defined, arglens no match
            print_param_len_mismatch((yyvsp[-3].sym_info)->getName());
        }else{ //arg lens matched, now validate
            validate_arg_type(sym, arg_type_holder);
        }
    }
    arg_type_holder.clear();
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-3].sym_info);
    delete (yyvsp[-1].pt);
}
#line 2538 "parser.tab.c"
    break;

  case 60:
#line 775 "parser.y"
{
    print_parser_grammar("factor", "LPAREN expression RPAREN");
    (yyval.pt) = new putil();
    (yyval.pt)->data = "(" + (yyvsp[-1].pt)->data + ")";
    (yyval.pt)->type = (yyvsp[-1].pt)->type;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-1].pt);
}
#line 2551 "parser.tab.c"
    break;

  case 61:
#line 784 "parser.y"
{
    print_parser_grammar("factor", "CONST_INT");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].sym_info)->getName();
    (yyval.pt)->type = "CONST_INT";
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].sym_info);
}
#line 2564 "parser.tab.c"
    break;

  case 62:
#line 793 "parser.y"
{
    print_parser_grammar("factor", "CONST_FLOAT");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].sym_info)->getName();
    (yyval.pt)->type = "CONST_FLOAT";
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].sym_info);
}
#line 2577 "parser.tab.c"
    break;

  case 63:
#line 802 "parser.y"
{
    print_parser_grammar("factor", "variable INCOP");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-1].pt)->data + "++";
    (yyval.pt)->type = "INCOP";
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-1].pt);
}
#line 2590 "parser.tab.c"
    break;

  case 64:
#line 811 "parser.y"
{
    print_parser_grammar("factor", "variable DECOP");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-1].pt)->data + "--";
    (yyval.pt)->type = "DECOP";
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-1].pt);
}
#line 2603 "parser.tab.c"
    break;

  case 65:
#line 821 "parser.y"
{
    print_parser_grammar("argument_list", "arguments");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2615 "parser.tab.c"
    break;

  case 66:
#line 829 "parser.y"
{
    print_parser_grammar("argument_list", "");
    (yyval.pt) = new putil();
}
#line 2624 "parser.tab.c"
    break;

  case 67:
#line 835 "parser.y"
{
    print_parser_grammar("arguments", "arguments COMMA logic_expression");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[-2].pt)->data + "," + (yyvsp[0].pt)->data;
    arg_type_holder.push_back((yyvsp[0].pt)->type);
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[-2].pt);
    delete (yyvsp[0].pt);
}
#line 2638 "parser.tab.c"
    break;

  case 68:
#line 845 "parser.y"
{
    print_parser_grammar("arguments", "logic_expression");
    (yyval.pt) = new putil();
    (yyval.pt)->data = (yyvsp[0].pt)->data;
    arg_type_holder.push_back((yyvsp[0].pt)->type);
    print_parser_text((yyval.pt)->data);
    delete (yyvsp[0].pt);
}
#line 2651 "parser.tab.c"
    break;


#line 2655 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 854 "parser.y"


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
