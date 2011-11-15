%{
#include "defines.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "project2.y.h"
%}

%option yylineno

%%
"target datalayout =".*                 { }
"target triple =".*                     { }

alloca                                  { return ALLOCA; }
align                                   { return ALIGN; }
icmp                                    { return ICMP; }
"eq"|"ne"|"slt"|"sle"|"sgt"|"sge"       { strcpy(yylval.reg, yytext); return CMP_TYPE;}
call                                    { return CALL; }
define                                  { yylval.string = yytext; return DEFINE; }
declare                                 { return DECLARE; }
"getelementptr inbounds"                { return GEP_INBOUNDS; }
load                                    { return LOAD; }
nounwind                                { return NOUNWIND; }
"nounwind ssp"                          { return NOUNWIND_SSP; }
private                                 { return PRIVATE; }
unnamed_addr                            { return UNNAMED_ADDR; }
constant                                { return CONSTANT; }
global                                  { return GLOBAL; }
common                                  { return COMMON; }
null                                    { return NULL_KEYWORD; }
store                                   { return STORE; }
add                                     { return ADD; }
sub                                     { return SUB; }
mul                                     { return MUL; }
sdiv                                    { return SDIV; }
ret                                     { return RET; }
br                                      { return BR; }
sext                                    { return SEXT; }
void                                    { return VOID; }
nsw                                     { return NSW; }
true                                    { strcpy(yylval.reg, yytext); return BOOLEAN; }
false                                   { strcpy(yylval.reg, yytext); return BOOLEAN; }
to                                      { return TO; }
@scanf                                  { return SCANF_CALL; }
@printf                                 { return PRINTF_CALL; }
label                                   { return LABEL_KEYWORD; }
"="                                     { return EQUALS; }
"%"[a-zA-Z0-9][a-zA-Z_0-9]*             { strcpy(yylval.reg, yytext); return REG; }
"; <label>:"[a-zA-Z0-9][a-zA-Z_0-9]*	{ strcpy(yylval.reg, yytext); return LABEL; }
"@"[a-zA-Z.0-9][a-zA-Z0-9]*             { strcpy(yylval.reg, yytext); return GLOBAL_DEF; }
"("                                     { return LPAREN; }
")"                                     { return RPAREN; }
"["                                     { return LBRACKET; }
"]"                                     { return RBRACKET; }
"{"                                     { return LBRACE; }
"}"                                     { return RBRACE; }
"c\"".*"\""                             { strcpy(yylval.reg, yytext); return STR_LITERAL; }
i1                                      { strcpy(yylval.reg, yytext); return INT_TYPE; }
i8                                      { strcpy(yylval.reg, yytext); return INT_TYPE; }
i16                                     { strcpy(yylval.reg, yytext); return INT_TYPE; }
i32                                     { strcpy(yylval.reg, yytext); return INT_TYPE; }
i64                                     { strcpy(yylval.reg, yytext); return INT_TYPE; }
\*+                                     { strcpy(yylval.reg, yytext); return POINTER; }
x                                       { return X; }
","                                     { return COMMA; }
[0-9]+                                  { yylval.num=atoi(yytext); return NUM; }
"..."                                   { return ELLIPSIS; }
" "                                     ;
";".*"\n"                               { strcpy(yylval.reg, yytext); return COMMENT; }
"\n"                                    ; 
.                                       { }
%%


