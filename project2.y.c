
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "project2.y"

#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "defines.h"

void allocaStmt(char *reg, int size);
void labelStmt(char *name);
void add(char *reg, param_t p1, param_t p2, int type);
void sub(char *reg, param_t p1, param_t p2, int type);
void brUncond(char *label);
void brCond(char *cond, char *trueLabel, char *falseLabel);
void cmpStmt(char *comp, char *assignReg, param_t p1, param_t p2, int type);
void loadStmt(char *destReg, char *pointer);
void storeStmt(char *dest, param_t param, int type);

#define CONST_VAL	(4)
#define REG_VAL	(5)



/* Line 189 of yacc.c  */
#line 95 "project2.y.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ALLOCA = 258,
     CALL = 259,
     GEP_INBOUNDS = 260,
     LOAD = 261,
     STORE = 262,
     ADD = 263,
     SUB = 264,
     MUL = 265,
     DIV = 266,
     EQUALS = 267,
     REG = 268,
     LABEL = 269,
     DEFINE = 270,
     NOUNWIND = 271,
     PRIVATE = 272,
     UNNAMED_ADDR = 273,
     CONSTANT = 274,
     RET = 275,
     BR = 276,
     GLOBAL_DEF = 277,
     LPAREN = 278,
     RPAREN = 279,
     LBRACKET = 280,
     RBRACKET = 281,
     LBRACE = 282,
     RBRACE = 283,
     I8 = 284,
     I32 = 285,
     POINTER = 286,
     X = 287,
     COMMA = 288,
     NUM = 289,
     ELIPSIS = 290,
     NOUNWIND_SSP = 291,
     LABEL_KEYWORD = 292,
     DECLARE = 293,
     COMMENT = 294,
     I1 = 295,
     ICMP = 296,
     CMP_TYPE = 297,
     VOID = 298
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 22 "project2.y"

  int 	num;
  char	*string;
  char	reg[50];



/* Line 214 of yacc.c  */
#line 182 "project2.y.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 194 "project2.y.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   118

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNRULES -- Number of states.  */
#define YYNSTATES  123

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    13,    18,    23,    26,    30,
      34,    38,    43,    46,    50,    52,    55,    57,    59,    61,
      63,    65,    67,    69,    71,    73,    75,    77,    79,    81,
      83,    85,    87,    89,    91,    93,    95,    97,   102,   110,
     112,   120,   128,   136,   144,   152,   160,   168,   176,   180,
     190,   199,   208,   217,   226,   232,   239,   246,   252
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    46,    -1,    46,    45,    -1,    47,    27,
      51,    28,    -1,    15,    30,    22,    48,    -1,    15,    43,
      22,    48,    -1,    23,    24,    -1,    23,    50,    24,    -1,
      23,    49,    24,    -1,    50,    33,    50,    -1,    49,    33,
      30,    13,    -1,    30,    13,    -1,    30,    31,    13,    -1,
      52,    -1,    52,    51,    -1,    53,    -1,    72,    -1,    54,
      -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,    59,
      -1,    60,    -1,    61,    -1,    62,    -1,    63,    -1,    64,
      -1,    65,    -1,    67,    -1,    66,    -1,    68,    -1,    69,
      -1,    70,    -1,    71,    -1,    73,    -1,    13,    12,     3,
      30,    -1,    13,    12,     3,    30,    33,    30,    34,    -1,
      14,    -1,    13,    12,     8,    30,    34,    33,    34,    -1,
      13,    12,     8,    30,    13,    33,    13,    -1,    13,    12,
       8,    30,    13,    33,    34,    -1,    13,    12,     8,    30,
      34,    33,    13,    -1,    13,    12,     9,    30,    34,    33,
      34,    -1,    13,    12,     9,    30,    13,    33,    13,    -1,
      13,    12,     9,    30,    13,    33,    34,    -1,    13,    12,
       9,    30,    34,    33,    13,    -1,    21,    37,    13,    -1,
      21,    40,    13,    33,    37,    13,    33,    37,    13,    -1,
      13,    12,    41,    42,    30,    13,    33,    13,    -1,    13,
      12,    41,    42,    30,    13,    33,    34,    -1,    13,    12,
      41,    42,    30,    34,    33,    34,    -1,    13,    12,    41,
      42,    30,    34,    33,    13,    -1,    13,    12,     6,    30,
      31,    -1,     7,    30,    13,    33,    30,    31,    -1,     7,
      30,    34,    33,    30,    31,    -1,    25,    34,    32,    30,
      26,    -1,    39,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    39,    39,    40,    42,    45,    48,    51,    52,    53,
      55,    56,    58,    59,    63,    64,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    89,    90,    93,
      95,   101,   107,   113,   120,   126,   132,   138,   144,   147,
     150,   156,   162,   168,   174,   177,   182,   188,   191
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ALLOCA", "CALL", "GEP_INBOUNDS", "LOAD",
  "STORE", "ADD", "SUB", "MUL", "DIV", "EQUALS", "REG", "LABEL", "DEFINE",
  "NOUNWIND", "PRIVATE", "UNNAMED_ADDR", "CONSTANT", "RET", "BR",
  "GLOBAL_DEF", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LBRACE",
  "RBRACE", "I8", "I32", "POINTER", "X", "COMMA", "NUM", "ELIPSIS",
  "NOUNWIND_SSP", "LABEL_KEYWORD", "DECLARE", "COMMENT", "I1", "ICMP",
  "CMP_TYPE", "VOID", "$accept", "func_list", "func_call", "func_start",
  "param_list", "comma_list", "param_obj", "stmt_list", "stmt",
  "alloca_stmt", "label_stmt", "addCC_stmt", "addRR_stmt", "addRC_stmt",
  "addCR_stmt", "subCC_stmt", "subRR_stmt", "subRC_stmt", "subCR_stmt",
  "brUncond_stmt", "brCond_stmt", "icmpRR_stmt", "icmpRC_stmt",
  "icmpCC_stmt", "icmpCR_stmt", "load_stmt", "storeReg_stmt",
  "storeCon_stmt", "array_type", "comment", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    46,    47,    47,    48,    48,    48,
      49,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    53,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     4,     4,     4,     2,     3,     3,
       3,     4,     2,     3,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     7,     1,
       7,     7,     7,     7,     7,     7,     7,     7,     3,     9,
       8,     8,     8,     8,     5,     6,     6,     5,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     0,     0,     1,     3,     0,
       0,     0,     0,     0,    39,     0,     0,    58,     0,    14,
      16,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    31,    30,    32,    33,    34,    35,    17,
      36,     0,     5,     6,     0,     0,     0,     0,     0,     4,
      15,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,     0,     0,    12,     0,     9,     0,     8,
       0,     0,     0,    37,     0,     0,     0,     0,     0,     0,
      13,     0,    10,     0,     0,     0,    54,     0,     0,     0,
       0,     0,     0,    57,    11,    55,    56,     0,     0,     0,
       0,     0,     0,     0,     0,    38,    41,    42,    43,    40,
      45,    46,    47,    44,     0,     0,     0,    50,    51,    53,
      52,     0,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,    42,    53,    54,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -14
static const yytype_int8 yypact[] =
{
      -5,     6,    12,    -5,     2,    23,    24,   -14,   -14,    -6,
      25,    25,    17,    16,   -14,   -13,    21,   -14,    26,    -6,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,
     -14,    20,   -14,   -14,   -11,    -3,    18,    38,    27,   -14,
     -14,   -14,     9,    -7,    19,    28,    29,    30,    33,    34,
      35,    11,   -14,    36,    37,   -14,    43,   -14,    40,   -14,
      41,    42,    44,    45,    46,    -9,    -4,    49,    31,    32,
     -14,    53,   -14,    50,    51,    54,   -14,    47,    52,    55,
      56,    -2,    60,   -14,   -14,   -14,   -14,    57,     0,     1,
       3,     5,    59,    61,    62,   -14,   -14,   -14,   -14,   -14,
     -14,   -14,   -14,   -14,     7,     8,    39,   -14,   -14,   -14,
     -14,    70,   -14
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -14,    72,   -14,   -14,    75,   -14,    48,    68,   -14,   -14,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      57,    12,    55,    58,    87,    59,    60,    13,    14,    89,
       1,   102,     7,   106,   108,    15,   110,    67,   112,    16,
     117,   119,    65,    56,    46,    88,    68,    47,    45,     9,
      90,    62,   103,    17,   107,   109,     5,   111,    61,   113,
      66,   118,   120,    69,    51,    10,    11,    44,    41,     6,
      52,    63,    70,    77,    49,    48,    80,     0,    93,    64,
      73,    71,    72,    74,    75,    76,    94,    79,    92,    78,
      81,    52,    83,   104,    84,     8,   121,    86,    85,    91,
      98,    95,    96,   122,    97,    99,    43,    50,   100,   101,
       0,   105,   114,     0,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82
};

static const yytype_int8 yycheck[] =
{
       3,     7,    13,     6,    13,     8,     9,    13,    14,    13,
      15,    13,     0,    13,    13,    21,    13,    24,    13,    25,
      13,    13,    13,    34,    37,    34,    33,    40,    12,    27,
      34,    13,    34,    39,    34,    34,    30,    34,    41,    34,
      31,    34,    34,    24,    24,    22,    22,    30,    23,    43,
      30,    13,    33,    42,    28,    34,    13,    -1,    26,    32,
      30,    33,    33,    30,    30,    30,    13,    30,    37,    33,
      30,    30,    30,    13,    30,     3,    37,    31,    33,    30,
      33,    31,    31,    13,    30,    33,    11,    19,    33,    33,
      -1,    34,    33,    -1,    33,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    15,    45,    46,    47,    30,    43,     0,    45,    27,
      22,    22,     7,    13,    14,    21,    25,    39,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    23,    48,    48,    30,    12,    37,    40,    34,    28,
      51,    24,    30,    49,    50,    13,    34,     3,     6,     8,
       9,    41,    13,    13,    32,    13,    31,    24,    33,    24,
      33,    33,    33,    30,    30,    30,    30,    42,    33,    30,
      13,    30,    50,    30,    30,    33,    31,    13,    34,    13,
      34,    30,    37,    26,    13,    31,    31,    30,    33,    33,
      33,    33,    13,    34,    13,    34,    13,    34,    13,    34,
      13,    34,    13,    34,    33,    33,    33,    13,    34,    13,
      34,    37,    13
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:

/* Line 1455 of yacc.c  */
#line 43 "project2.y"
    { printf("__function definition\n"); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 46 "project2.y"
    { printf("Function Header: %s\n", (yyvsp[(1) - (4)].string)); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 49 "project2.y"
    { printf("Function Header: %s\n", (yyvsp[(1) - (4)].string)); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 63 "project2.y"
    { printf("\n"); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 64 "project2.y"
    { printf("\n"); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 66 "project2.y"
    { printf("\n"); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 67 "project2.y"
    { printf("\n"); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 68 "project2.y"
    { printf("\n"); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 69 "project2.y"
    { printf("\n"); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 70 "project2.y"
    { printf("\n"); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 71 "project2.y"
    { printf("\n"); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 72 "project2.y"
    { printf("\n"); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 73 "project2.y"
    { printf("\n"); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 74 "project2.y"
    { printf("\n"); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 75 "project2.y"
    { printf("\n"); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 76 "project2.y"
    { printf("\n"); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 77 "project2.y"
    { printf("\n"); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 78 "project2.y"
    { printf("\n"); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 79 "project2.y"
    { printf("\n"); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 80 "project2.y"
    { printf("\n"); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 81 "project2.y"
    { printf("\n"); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 82 "project2.y"
    { printf("\n"); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 83 "project2.y"
    { printf("\n"); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 84 "project2.y"
    { printf("\n"); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 85 "project2.y"
    { printf("\n"); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 86 "project2.y"
    { printf("\n"); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 89 "project2.y"
    { allocaStmt((yyvsp[(1) - (4)].reg), 0); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 90 "project2.y"
    { int size = (yyvsp[(7) - (7)].num);
                                                          allocaStmt((yyvsp[(1) - (7)].reg), size); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 93 "project2.y"
    { labelStmt((yyvsp[(1) - (1)].reg)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 96 "project2.y"
    { param_t const1, const2;
								  const1.imm = (yyvsp[(5) - (7)].num);
								  const2.imm = (yyvsp[(7) - (7)].num);
								  add((yyvsp[(1) - (7)].reg), const1, const2, ADD_CC); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 102 "project2.y"
    { param_t reg1, reg2;
								  strcpy(reg1.reg, (yyvsp[(5) - (7)].reg));
								  strcpy(reg2.reg, (yyvsp[(7) - (7)].reg));
								  add((yyvsp[(1) - (7)].reg), reg1, reg2, ADD_RR); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 108 "project2.y"
    { param_t reg1, const1;
								  strcpy(reg1.reg, (yyvsp[(5) - (7)].reg));
								  const1.imm = (yyvsp[(7) - (7)].num);
								  add((yyvsp[(1) - (7)].reg), reg1, const1, ADD_RR); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 114 "project2.y"
    { param_t reg1, const1;
								  strcpy(reg1.reg, (yyvsp[(7) - (7)].reg));
								  const1.imm = (yyvsp[(5) - (7)].num);
								  sub((yyvsp[(1) - (7)].reg), reg1, const1, ADD_CR); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 121 "project2.y"
    { param_t const1, const2;
								  const1.imm = (yyvsp[(5) - (7)].num);
								  const2.imm = (yyvsp[(7) - (7)].num);
								  sub((yyvsp[(1) - (7)].reg), const1, const2, SUB_CC); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 127 "project2.y"
    { param_t reg1, reg2;
								  strcpy(reg1.reg, (yyvsp[(5) - (7)].reg));
								  strcpy(reg2.reg, (yyvsp[(7) - (7)].reg));
								  sub((yyvsp[(1) - (7)].reg), reg1, reg2, SUB_RR); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 133 "project2.y"
    { param_t reg1, const1;
								  strcpy(reg1.reg, (yyvsp[(5) - (7)].reg));
								  const1.imm = (yyvsp[(7) - (7)].num);
								  sub((yyvsp[(1) - (7)].reg), reg1, const1, SUB_RR); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 139 "project2.y"
    { param_t reg1, reg2;
								  reg1.imm = (yyvsp[(5) - (7)].num);
								  strcpy(reg2.reg, (yyvsp[(7) - (7)].reg));
								  sub((yyvsp[(1) - (7)].reg), reg1, reg2, SUB_CR); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 145 "project2.y"
    { brUncond((yyvsp[(3) - (3)].reg)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 148 "project2.y"
    { brCond((yyvsp[(3) - (9)].reg), (yyvsp[(6) - (9)].reg), (yyvsp[(9) - (9)].reg)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 151 "project2.y"
    { param_t reg1, reg2;
								  strcpy(reg1.reg, (yyvsp[(6) - (8)].reg));
								  strcpy(reg2.reg, (yyvsp[(8) - (8)].reg));
								  cmpStmt((yyvsp[(4) - (8)].reg), (yyvsp[(1) - (8)].reg), reg1, reg2, CMP_RR); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 157 "project2.y"
    { param_t reg1, reg2;
								  strcpy(reg1.reg, (yyvsp[(6) - (8)].reg));
								  reg2.imm = (yyvsp[(8) - (8)].num);
								  cmpStmt((yyvsp[(4) - (8)].reg), (yyvsp[(1) - (8)].reg), reg1, reg2, CMP_RC); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 163 "project2.y"
    { param_t reg1, reg2;
								  reg1.imm = (yyvsp[(6) - (8)].num);
								  reg2.imm = (yyvsp[(8) - (8)].num);
								  cmpStmt((yyvsp[(4) - (8)].reg), (yyvsp[(1) - (8)].reg), reg1, reg2, CMP_CC); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 169 "project2.y"
    { param_t reg1, reg2;
								  reg1.imm = (yyvsp[(6) - (8)].num);
								  strcpy(reg2.reg, (yyvsp[(8) - (8)].reg));
								  cmpStmt((yyvsp[(4) - (8)].reg), (yyvsp[(1) - (8)].reg), reg1, reg2, CMP_CR); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 175 "project2.y"
    { loadStmt((yyvsp[(1) - (5)].reg), (yyvsp[(5) - (5)].reg)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 178 "project2.y"
    { param_t param;
								  strcpy(param.reg, (yyvsp[(3) - (6)].reg));
								  storeStmt((yyvsp[(6) - (6)].reg), param, STR_REG); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 183 "project2.y"
    { param_t param;
								  param.imm = (yyvsp[(3) - (6)].num);
								  storeStmt((yyvsp[(6) - (6)].reg), param, STR_CONST); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 189 "project2.y"
    { printf("___Array Type: %d x i32\n\n", (yyvsp[(2) - (5)].num)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 191 "project2.y"
    {  ;}
    break;



/* Line 1455 of yacc.c  */
#line 1874 "project2.y.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 194 "project2.y"

extern FILE *yyin;
int yyerror() { return 0; }
stmt *HEAD=NULL;
stmt *current=NULL;
param_t empty;

int main(int argc, char *argv[]) {
	empty.imm = 0;	
	stmt *HEAD=NULL;
	stmt *current=NULL;
	yyin = fopen(argv[1], "r"); 
	yyparse();
	current=HEAD;
	FILE *fp = fopen("output.ll", "w");
	if(fp == NULL)
		printf("Could not open output file");
	else 
		while (current->next != NULL){
			printf("%s",generate_llvm(current,fp));
		}
	fclose(fp);
	

}


void allocaStmt(char *reg, int size)
{
	printf("___Found Alloca Statment, Reg: %s\n\n", reg);
	param_t tmp;
	tmp.imm = size;
	process_instruction(ALLOC, reg, tmp, empty, NULL, NULL, NULL);
}

void labelStmt(char *name)
{
	printf("__Label %s\n", name);
 	process_instruction(LABELL, NULL, empty, empty, NULL, NULL, name);
}

void add(char *reg, param_t p1, param_t p2, int type)
{
	if(type == ADD_CC)
	{
		printf("__Add: %s <- %d + %d\n\n", reg, p1.imm, p2.imm);
	}
	else if(type == ADD_RR)
	{
		printf("__Add: %s <- %s + %s\n\n", reg, p1.reg, p2.reg);
	}
	else if(type == ADD_RR)
	{
		printf("__Add: %s <- %s + %d\n\n", reg, p1.reg, p2.imm);
	}
	else if(type == ADD_CR)
	{
		printf("__Sub: %s <- %d - %s\n\n", reg, p1.imm, p2.reg);
	}
    
    process_instruction(type, reg, p1, p2, NULL, NULL, NULL);
}

void sub(char *reg, param_t p1, param_t p2, int type)
{
	if(type == SUB_CC)
	{
		printf("__Sub: %s <- %d - %d\n\n", reg, p1.imm, p2.imm);
	}
	else if(type == SUB_RR)
	{
		printf("__Sub: %s <- %s - %s\n\n", reg, p1.reg, p2.reg);
	}
	else if(type == SUB_RR)
	{
		printf("__Sub: %s <- %s - %d\n\n", reg, p1.reg, p2.imm);
	}
	else if(type == SUB_CR)
	{
		printf("__Sub: %s <- %d - %s\n\n", reg, p1.imm, p2.reg);
	}
    process_instruction(type, reg, p1, p2, NULL, NULL, NULL);
}


void brUncond(char *label)
{
	printf("__Branch: %s", &label[1]);
	process_instruction(BR_UNCOND, NULL, empty, empty, NULL, NULL, label);
}


void brCond(char *cond, char *trueLabel, char *falseLabel)
{
	printf("__Branch: cond: %s, true: %s, false: %s", cond, &trueLabel[1], &falseLabel[1]);
	char * arr[3] = {cond, trueLabel, falseLabel};
	process_instruction(BR_COND, NULL, empty, empty, NULL, arr, NULL);
}

void cmpStmt(char *comp, char *assignReg, param_t p1, param_t p2, int type)
{
	if(type == CMP_CC)
	{
		printf("__CMP: %s <- %d %s %d\n\n", assignReg, p1.imm, comp, p2.imm);
	}
	else if(type == CMP_RR)
	{
		printf("__CMP: %s <- %s %s %s\n\n", assignReg, p1.reg, comp, p2.reg);
	}
	else if(type == CMP_RC)
	{
		printf("__CMP: %s <- %s %s %d\n\n", assignReg, p1.reg, comp, p2.imm);
	}
	else if(type == CMP_CR)
	{
		printf("__CMP: %s <- %d %s %s\n\n", assignReg, p1.imm, comp, p2.reg);
	}
    
    process_instruction(type, assignReg, p1, p2, comp, NULL, NULL);
}


void loadStmt(char *destReg, char *pointer)
{
	printf("__load: %s <- %s\n\n", destReg, pointer);
	param_t tmp;
	strcpy(tmp.reg,pointer);
    
    process_instruction(LOADD, destReg, tmp, empty, NULL, NULL, NULL);
}


void storeStmt(char *dest, param_t param, int type)
{
	if(type == REG_VAL)
	{
		printf("__store: %s <- %s\n\n", dest, param.reg);
	}
	else if(type == CONST_VAL)
	{
		printf("__store: %s <- %d\n\n", dest, param.imm);
	}
    
    process_instruction(type,dest,param, empty, NULL, NULL, NULL);
}



















