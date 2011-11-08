%{
#include <stdio.h>
#include <string.h>
#include "functions.h"

typedef union {
	int  imm;
	char reg[50];
} param_t;

void allocaStmt(char *reg);
void labelStmt(char *name);
void storeStmt(char *reg1, char *reg2);
void add(char *reg, param_t p1, param_t p2, int type);
void sub(char *reg, param_t p1, param_t p2, int type);

#define RR (0)
#define CC (1)
#define RC (2)
#define CR (3)



%}

%union {
  int 	num;
  char	reg[50];
}

%token ALLOCA CALL GEP_INBOUNDS LOAD STORE ADD SUB MUL DIV EQUALS REG LABEL
	DEFINE NOUNWIND	PRIVATE UNNAMED_ADDR CONSTANT RET BR GLOBAL_DEF LPAREN
	RPAREN LBRACKET RBRACKET LBRACE RBRACE I8 I32 POINTER X COMMA NUM ELIPSIS
	NOUNWIND_SSP LABEL_KEYWORD DECLARE COMMENT I1

%type <num> NUM
%type <reg> REG LABEL GLOBAL_DEF

%% 
// top level of syntax tree
stmt_list:
		stmt				{ printf("\n"); }
		| stmt stmt_list 	{ printf("\n"); }

stmt:	alloca_stmt		{ printf("\n"); }
		| array_type		{ printf("\n"); }
		| label_stmt		{ printf("\n"); }
		| store_stmt		{ printf("\n"); }
		| addCC_stmt		{ printf("\n"); }
		| addRR_stmt		{ printf("\n"); }
		| addRC_stmt		{ printf("\n"); }
		| addCR_stmt		{ printf("\n"); }
		| subCC_stmt		{ printf("\n"); }
		| subRR_stmt		{ printf("\n"); }
		| subRC_stmt		{ printf("\n"); }
		| subCR_stmt		{ printf("\n"); }
		| brUncond_stmt	{ printf("\n"); }
		| brCond_stmt		{ printf("\n"); }
		
		| comment			{}
		
// statments
alloca_stmt:	REG EQUALS ALLOCA I32	{ allocaStmt($1); }

label_stmt:	LABEL				{ labelStmt($1); }

store_stmt:	STORE I32 REG COMMA I32 POINTER REG 
								{ storeStmt($3, $7); }

addCC_stmt:	REG EQUALS ADD I32 NUM COMMA NUM
								{ param_t const1, const2;
								  const1.imm = $5;
								  const2.imm = $7;
								  add($1, const1, const2, CC); }

addRR_stmt:	REG EQUALS ADD I32 REG COMMA REG
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $5);
								  strcpy(reg2.reg, $7);
								  add($1, reg1, reg2, RR); }

addRC_stmt:	REG EQUALS ADD I32 REG COMMA NUM
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $5);
								  const1.imm = $7;
								  add($1, reg1, const1, RC); }

addCR_stmt:	REG EQUALS ADD I32 NUM COMMA REG
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $7);
								  const1.imm = $5;
								  sub($1, reg1, const1, RC); }

//----------------------------
subCC_stmt:	REG EQUALS SUB I32 NUM COMMA NUM
								{ param_t const1, const2;
								  const1.imm = $5;
								  const2.imm = $7;
								  sub($1, const1, const2, CC); }

subRR_stmt:	REG EQUALS SUB I32 REG COMMA REG
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $5);
								  strcpy(reg2.reg, $7);
								  sub($1, reg1, reg2, RR); }

subRC_stmt:	REG EQUALS SUB I32 REG COMMA NUM
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $5);
								  const1.imm = $7;
								  sub($1, reg1, const1, RC); }

subCR_stmt:	REG EQUALS SUB I32 NUM COMMA REG
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $7);
								  const1.imm = $5;
								  sub($1, reg1, const1, RC); }

//----------------------------
brUncond_stmt:	BR LABEL_KEYWORD REG
								{}

brCond_stmt:	BR I1 REG COMMA LABEL_KEYWORD REG COMMA LABEL_KEYWORD REG
								{}

// portions of complex statments
array_type:	LBRACKET NUM X I32 RBRACKET
								{ printf("___Array Type: %d x i32\n\n", $2); }

comment:		COMMENT				{  }


%%
extern FILE *yyin;

int yyerror() { return 0; }

main() {yyparse();}

void allocaStmt(char *reg)
{
	printf("___Found Alloca Statment, Reg: %s\n\n", reg);
}

void labelStmt(char *name)
{
	printf("__Label %s\n", name);
}

void storeStmt(char *reg1, char *reg2)
{
	printf("__Store: %s -> %s\n\n", reg1, reg2);
}

void add(char *reg, param_t p1, param_t p2, int type)
{
	if(type == CC)
	{
		printf("__Add: %s <- %d + %d\n\n", reg, p1.imm, p2.imm);
	}
	else if(type == RR)
	{
		printf("__Add: %s <- %s + %s\n\n", reg, p1.reg, p2.reg);
	}
	else if(type == RC)
	{
		printf("__Add: %s <- %s + %d\n\n", reg, p1.reg, p2.imm);
	}
}

void sub(char *reg, param_t p1, param_t p2, int type)
{
	if(type == CC)
	{
		printf("__Sub: %s <- %d - %d\n\n", reg, p1.imm, p2.imm);
	}
	else if(type == RR)
	{
		printf("__Sub: %s <- %s - %s\n\n", reg, p1.reg, p2.reg);
	}
	else if(type == RC)
	{
		printf("__Sub: %s <- %s - %d\n\n", reg, p1.reg, p2.imm);
	}
}












