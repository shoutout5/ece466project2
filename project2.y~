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
void add(char *reg, param_t p1, param_t p2, int type);
void sub(char *reg, param_t p1, param_t p2, int type);
void brUncond(char *label);
void brCond(char *cond, char *trueLabel, char *falseLabel);
void cmpStmt(char *comp, char *assignReg, param_t p1, param_t p2, int type);
void loadStmt(char *destReg, char *pointer);
void storeStmt(char *dest, param_t param, int type);

#define RR (0)
#define CC (1)
#define RC (2)
#define CR (3)

#define CONST_VAL	(4)
#define REG_VAL	(5)



%}

%union {
  int 	num;
  char	reg[50];
}

%token ALLOCA CALL GEP_INBOUNDS LOAD STORE ADD SUB MUL DIV EQUALS REG LABEL
	DEFINE NOUNWIND	PRIVATE UNNAMED_ADDR CONSTANT RET BR GLOBAL_DEF LPAREN
	RPAREN LBRACKET RBRACKET LBRACE RBRACE I8 I32 POINTER X COMMA NUM ELIPSIS
	NOUNWIND_SSP LABEL_KEYWORD DECLARE COMMENT I1 ICMP CMP_TYPE

%type <num> NUM
%type <reg> REG LABEL GLOBAL_DEF CMP_TYPE

%% 
// top level of syntax tree
stmt_list:
		stmt				{ printf("\n"); }
		| stmt stmt_list 	{ printf("\n"); }

stmt:	alloca_stmt		{ printf("\n"); }
		| array_type		{ printf("\n"); }
		| label_stmt		{ printf("\n"); }
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
		| icmpRR_stmt		{ printf("\n"); }
		| icmpCC_stmt		{ printf("\n"); }
		| icmpRC_stmt		{ printf("\n"); }
		| icmpCR_stmt		{ printf("\n"); }
		| load_stmt		{ printf("\n"); }
		| storeReg_stmt	{ printf("\n"); }
		| storeCon_stmt	{ printf("\n"); }
		| comment			{ printf("\n"); }
		
// statments
alloca_stmt:	REG EQUALS ALLOCA I32	{ allocaStmt($1); }

label_stmt:	LABEL				{ labelStmt($1); }

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
								{ param_t reg1, reg2;
								  reg1.imm = $5;
								  strcpy(reg2.reg, $7);
								  sub($1, reg1, reg2, CR); }
//----------------------------
brUncond_stmt:	BR LABEL_KEYWORD REG
								{ brUncond($3); }

brCond_stmt:	BR I1 REG COMMA LABEL_KEYWORD REG COMMA LABEL_KEYWORD REG
								{ brCond($3, $6, $9); }
//----------------------------
icmpRR_stmt:	REG EQUALS ICMP CMP_TYPE I32 REG COMMA REG
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $6);
								  strcpy(reg2.reg, $8);
								  cmpStmt($4, $1, reg1, reg2, RR); }

icmpRC_stmt:	REG EQUALS ICMP CMP_TYPE I32 REG COMMA NUM
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $6);
								  reg2.imm = $8;
								  cmpStmt($4, $1, reg1, reg2, RC); }

icmpCC_stmt:	REG EQUALS ICMP CMP_TYPE I32 NUM COMMA NUM
								{ param_t reg1, reg2;
								  reg1.imm = $6;
								  reg2.imm = $8;
								  cmpStmt($4, $1, reg1, reg2, CC); }

icmpCR_stmt:	REG EQUALS ICMP CMP_TYPE I32 NUM COMMA REG
								{ param_t reg1, reg2;
								  reg1.imm = $6;
								  strcpy(reg2.reg, $8);
								  cmpStmt($4, $1, reg1, reg2, CR); }
//----------------------------
load_stmt:	REG EQUALS LOAD I32 POINTER REG
								{ loadStmt($1, $6); }

storeReg_stmt:	STORE I32 REG COMMA I32 POINTER REG
								{ param_t param;
								  strcpy(param.reg, $3);
								  storeStmt($7, param, REG_VAL); }

storeCon_stmt:	STORE I32 NUM COMMA I32 POINTER REG
								{ param_t param;
								  param.imm = $3;
								  storeStmt($7, param, CONST_VAL); }

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
	else if(type == CR)
	{
		printf("__Sub: %s <- %d - %s\n\n", reg, p1.imm, p2.reg);
	}
}


void brUncond(char *label)
{
	printf("__Branch: %s", &label[1]);
}


void brCond(char *cond, char *trueLabel, char *falseLabel)
{
	printf("__Branch: cond: %s, true: %s, false: %s", cond, &trueLabel[1], &falseLabel[1]);
}

void cmpStmt(char *comp, char *assignReg, param_t p1, param_t p2, int type)
{
	if(type == CC)
	{
		printf("__CMP: %s <- %d %s %d\n\n", assignReg, p1.imm, comp, p2.imm);
	}
	else if(type == RR)
	{
		printf("__CMP: %s <- %s %s %s\n\n", assignReg, p1.reg, comp, p2.reg);
	}
	else if(type == RC)
	{
		printf("__CMP: %s <- %s %s %d\n\n", assignReg, p1.reg, comp, p2.imm);
	}
	else if(type == CR)
	{
		printf("__CMP: %s <- %d %s %s\n\n", assignReg, p1.imm, comp, p2.reg);
	}
}


void loadStmt(char *destReg, char *pointer)
{
	printf("__load: %s <- %s\n\n", destReg, pointer);
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
}
















