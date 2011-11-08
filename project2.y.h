
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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
     CMP_TYPE = 297
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 33 "project2.y"

  int 	num;
  char	reg[50];



/* Line 1676 of yacc.c  */
#line 101 "project2.y.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


