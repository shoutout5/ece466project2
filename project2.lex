%{
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "project2.y.h"
%}


%%

alloca  				{ printf("ALLOCA\n"); return ALLOCA; }
call						{ printf("CALL\n"); return CALL; }
define					{ printf("DEFINE\n"); return DEFINE; }
declare					{ printf("DECLARE\n"); return DECLARE; }
"getelementptr inbounds"		{ printf("GEP_INBOUNDS\n"); return GEP_INBOUNDS; }
load						{ printf("LOAD\n"); return LOAD; }
"nounwind ssp"				{ printf("NOUNWIND_SSP\n"); return NOUNWIND_SSP; }
private					{ printf("PRIVATE\n"); return PRIVATE; }
unnamed_addr				{ printf("UNNAMED_ADDR\n"); return UNNAMED_ADDR; }
constant					{ printf("CONSTANT\n"); return CONSTANT; }
store					{ printf("STORE\n"); return STORE; }
add						{ printf("ADD\n"); return ADD; }
sub						{ printf("SUB\n"); return SUB; }
mul						{ printf("MUL\n"); return MUL; }
div						{ printf("DIV\n"); return DIV; }
ret						{ printf("RET\n"); return RET; }
br						{ printf("BR\n"); return BR; }
label					{ printf("LABEL_KEYWORD\n"); return LABEL_KEYWORD; }
"="						{ printf("EQUALS\n"); return EQUALS; }
"%"[a-zA-Z0-9][a-zA-Z_0-9]*	{ strcpy(yylval.reg, yytext); printf("REG , %s\n", &yytext[1]); return REG; }
[a-zA-Z0-9][a-zA-Z_0-9]*":"	{ strcpy(yylval.reg, yytext); printf("LABEL\n"); return LABEL; }
"@"[a-zA-Z.][a-zA-Z0-9]*		{ strcpy(yylval.reg, yytext); printf("GLOBAL_DEF\n"); return GLOBAL_DEF; }
"("						{ printf("LPAREN\n"); return LPAREN; }
")"						{ printf("RPAREN\n"); return RPAREN; }
"["						{ printf("LBRACKET\n"); return LBRACKET; }
"]"						{ printf("RBRACKET\n"); return RBRACKET; }
"{"						{ printf("LBRACE\n"); return LBRACE; }
"}"						{ printf("RBRACE\n"); return RBRACE; }
i1						{ printf("I1\n"); return I1; }
i8						{ printf("I8\n"); return I8; }
i32						{ printf("I32\n"); return I32; }
"*"						{ printf("POINTER\n"); return POINTER; }
x						{ printf("X\n"); return X; }
","						{ printf("COMMA\n"); return COMMA; }
[0-9]+					{ yylval.num=atoi(yytext); printf("NUM\n"); return NUM; }
…						{ printf("ELIPSIS\n"); return ELIPSIS; }
";"[a-zA-Z0-9.' '?<>:;]*"\n"	{ printf("COMMENT\n"); return COMMENT; }

%%
