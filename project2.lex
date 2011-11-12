%{
#include "defines.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "project2.y.h"
%}


%%
"target datalayout =".*			{ printf("Target datalayout ignored\n"); }
"target triple =".*				{ printf("Target triple ignored\n"); }

alloca  					{ printf("ALLOCA\n"); return ALLOCA; }
align						{ printf("ALIGN\n"); return ALIGN; }
icmp							{ printf("ICMP\n"); return ICMP; }
"eq"|"ne"|"slt"|"sle"|"sgt"|"sge"	{ strcpy(yylval.reg, yytext); printf("Compare Type\n"); return CMP_TYPE;}
call							{ printf("CALL\n"); return CALL; }
define						{ printf("DEFINE\n"); yylval.string = yytext; return DEFINE; }
declare						{ printf("DECLARE\n"); return DECLARE; }
"getelementptr inbounds"			{ printf("GEP_INBOUNDS\n"); return GEP_INBOUNDS; }
load							{ printf("LOAD\n"); return LOAD; }
nounwind						{ printf("NOUNWIND\n"); return NOUNWIND; }
"nounwind ssp"					{ printf("NOUNWIND_SSP\n"); return NOUNWIND_SSP; }
private						{ printf("PRIVATE\n"); return PRIVATE; }
unnamed_addr					{ printf("UNNAMED_ADDR\n"); return UNNAMED_ADDR; }
constant						{ printf("CONSTANT\n"); return CONSTANT; }
global						{ printf("GLOBAL\n"); return GLOBAL; }
common						{ printf("COMMON\n"); return COMMON; }
null							{ printf("NULL_KEYWORD\n"); return NULL_KEYWORD; }
store						{ printf("STORE\n"); return STORE; }
add							{ printf("ADD\n"); return ADD; }
sub							{ printf("SUB\n"); return SUB; }
mul							{ printf("MUL\n"); return MUL; }
div							{ printf("DIV\n"); return DIV; }
ret							{ printf("RET\n"); return RET; }
br							{ printf("BR\n"); return BR; }
sext							{ printf("SEXT\n"); return SEXT; }
void							{ printf("VOID\n"); return VOID; }
nsw							{ printf("NSW\n"); return NSW; }
true							{ printf("TRUE\n"); return TRUE; }
false						{ printf("FALSE\n"); return FALSE; }
to							{ printf("TO\n"); return TO; }
@scanf						{ printf("SCANF_CALL\n"); return SCANF_CALL; }
@printf						{ printf("PRINTF_CALL\n"); return PRINTF_CALL; }
label						{ printf("LABEL_KEYWORD\n"); return LABEL_KEYWORD; }
"="							{ printf("EQUALS\n"); return EQUALS; }
"%"[a-zA-Z0-9][a-zA-Z_0-9]*		{ strcpy(yylval.reg, yytext); printf("REG, %s\n", &yytext[1]); return REG; }
[a-zA-Z0-9][a-zA-Z_0-9]*":"		{ strcpy(yylval.reg, yytext); printf("LABEL\n"); return LABEL; }
"@"[a-zA-Z.][a-zA-Z0-9]*			{ strcpy(yylval.reg, yytext); printf("GLOBAL_DEF\n"); return GLOBAL_DEF; }
"("							{ printf("LPAREN\n"); return LPAREN; }
")"							{ printf("RPAREN\n"); return RPAREN; }
"["							{ printf("LBRACKET\n"); return LBRACKET; }
"]"							{ printf("RBRACKET\n"); return RBRACKET; }
"{"							{ printf("LBRACE\n"); return LBRACE; }
"}"							{ printf("RBRACE\n"); return RBRACE; }
"c\"".*"\""					{ strcpy(yylval.reg, yytext); printf("STRING LITERAL\n"); return STR_LITERAL; }
i1							{strcpy(yylval.reg, yytext);  printf("I1\n"); return INT_TYPE; }
i8							{ strcpy(yylval.reg, yytext); printf("I8\n"); return INT_TYPE; }
i32							{ strcpy(yylval.reg, yytext); printf("I32\n"); return INT_TYPE; }
i64							{ strcpy(yylval.reg, yytext); printf("I64\n"); return INT_TYPE; }
\*+							{ printf("POINTER , %s\n", &yytext[0]); return POINTER; }
x							{ printf("X\n"); return X; }
","							{ printf("COMMA\n"); return COMMA; }
[0-9]+						{ yylval.num=atoi(yytext); printf("NUM\n"); return NUM; }
"..."						{ printf("ELIPSIS\n"); return ELIPSIS; }
" "							;
";".*"\n"						{ printf("COMMENT\n");  }
"\n"							;
.						 	{printf("UNKNOWN\n"); }
%%
