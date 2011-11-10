%{
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

%}

%union {
  int 	num;
  char	*string;
  char	reg[50];
}

%token ALLOCA CALL GEP_INBOUNDS LOAD STORE ADD SUB MUL DIV EQUALS REG LABEL
	DEFINE NOUNWIND	PRIVATE UNNAMED_ADDR CONSTANT RET BR GLOBAL_DEF LPAREN
	RPAREN LBRACKET RBRACKET LBRACE RBRACE I8 I32 POINTER X COMMA NUM ELIPSIS
	NOUNWIND_SSP LABEL_KEYWORD DECLARE COMMENT I1 ICMP CMP_TYPE VOID

%type <num> NUM
%type <reg> REG LABEL GLOBAL_DEF CMP_TYPE POINTER
%type <string> DEFINE

%% 
// top level of syntax tree
func_list: 	func_call
			| func_call func_list
			
func_call:	 func_start  LBRACE stmt_list RBRACE
						{ printf("__function definition\n"); }

func_start:	DEFINE I32 GLOBAL_DEF param_list		
						{ printf("Function Header: %s\n", $1); }
						
			| DEFINE VOID GLOBAL_DEF param_list
						{ printf("Function Header: %s\n", $1); }

param_list:	LPAREN RPAREN
			| LPAREN param_obj RPAREN
			| LPAREN comma_list RPAREN

comma_list:	param_obj COMMA param_obj
			| comma_list COMMA I32 REG

param_obj:	I32 REG
			| I32 POINTER REG
			
//----------------------------
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
		
// statements
alloca_stmt:	REG EQUALS ALLOCA I32                   { allocaStmt($1, 0); }
                | REG EQUALS ALLOCA I32 COMMA I32 NUM   { int size = $7;
                                                          allocaStmt($1, size); }

label_stmt:	LABEL				{ labelStmt($1); }

addCC_stmt:	REG EQUALS ADD I32 NUM COMMA NUM
								{ param_t const1, const2;
								  const1.imm = $5;
								  const2.imm = $7;
								  add($1, const1, const2, ADD_CC); }

addRR_stmt:	REG EQUALS ADD I32 REG COMMA REG
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $5);
								  strcpy(reg2.reg, $7);
								  add($1, reg1, reg2, ADD_RR); }

addRC_stmt:	REG EQUALS ADD I32 REG COMMA NUM
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $5);
								  const1.imm = $7;
								  add($1, reg1, const1, ADD_RR); }

addCR_stmt:	REG EQUALS ADD I32 NUM COMMA REG
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $7);
								  const1.imm = $5;
								  sub($1, reg1, const1, ADD_CR); }

//----------------------------
subCC_stmt:	REG EQUALS SUB I32 NUM COMMA NUM
								{ param_t const1, const2;
								  const1.imm = $5;
								  const2.imm = $7;
								  sub($1, const1, const2, SUB_CC); }

subRR_stmt:	REG EQUALS SUB I32 REG COMMA REG
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $5);
								  strcpy(reg2.reg, $7);
								  sub($1, reg1, reg2, SUB_RR); }

subRC_stmt:	REG EQUALS SUB I32 REG COMMA NUM
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $5);
								  const1.imm = $7;
								  sub($1, reg1, const1, SUB_RR); }

subCR_stmt:	REG EQUALS SUB I32 NUM COMMA REG
								{ param_t reg1, reg2;
								  reg1.imm = $5;
								  strcpy(reg2.reg, $7);
								  sub($1, reg1, reg2, SUB_CR); }
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
								  cmpStmt($4, $1, reg1, reg2, CMP_RR); }

icmpRC_stmt:	REG EQUALS ICMP CMP_TYPE I32 REG COMMA NUM
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $6);
								  reg2.imm = $8;
								  cmpStmt($4, $1, reg1, reg2, CMP_RC); }

icmpCC_stmt:	REG EQUALS ICMP CMP_TYPE I32 NUM COMMA NUM
								{ param_t reg1, reg2;
								  reg1.imm = $6;
								  reg2.imm = $8;
								  cmpStmt($4, $1, reg1, reg2, CMP_CC); }

icmpCR_stmt:	REG EQUALS ICMP CMP_TYPE I32 NUM COMMA REG
								{ param_t reg1, reg2;
								  reg1.imm = $6;
								  strcpy(reg2.reg, $8);
								  cmpStmt($4, $1, reg1, reg2, CMP_CR); }
//----------------------------
load_stmt:	REG EQUALS LOAD I32 POINTER
								{ loadStmt($1, $5); }

storeReg_stmt:	STORE I32 REG COMMA I32 POINTER
								{ param_t param;
								  strcpy(param.reg, $3);
								  storeStmt($6, param, STR_REG); }

storeCon_stmt:	STORE I32 NUM COMMA I32 POINTER
								{ param_t param;
								  param.imm = $3;
								  storeStmt($6, param, STR_CONST); }

// portions of complex statments
array_type:	LBRACKET NUM X I32 RBRACKET
								{ printf("___Array Type: %d x i32\n\n", $2); }

comment:		COMMENT				{  }


%%
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


















