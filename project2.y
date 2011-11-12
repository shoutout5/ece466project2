%{
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "defines.h"

void allocaStmt(char *reg, int size, char *type, array_def *contents);
void labelStmt(char *name);
void add(char *reg, param_t p1, param_t p2, int type);
void sub(char *reg, param_t p1, param_t p2, int type);
void brUncond(char *label);
void brCond(char *cond, char *trueLabel, char *falseLabel);
void cmpStmt(char *comp, char *assignReg, param_t p1, param_t p2, int type);
void loadStmt(char *destReg, char *pointer);
void storeStmt(char *dest, param_t param, int type);
void return_stmt(char *return_type, param_t param);
void getelementpointers(int type,char *defined, param_t param1, param_t param2);
void global_constant(char *name,param_t num, param_t val);

#define CONST_VAL	(4)
#define REG_VAL	(5)
#define YYERROR_VERBOSE (1)

%}

%union {
    int 	num;
    char	*string;
    char	reg[50];
    array_def array_spec;
}
%expect 3

%token ALLOCA CALL GEP_INBOUNDS LOAD STORE ADD SUB MUL DIV EQUALS REG LABEL
	DEFINE NOUNWIND	PRIVATE UNNAMED_ADDR CONSTANT RET BR GLOBAL_DEF LPAREN
	RPAREN LBRACKET RBRACKET LBRACE RBRACE INT_TYPE POINTER X COMMA NUM ELIPSIS
	NOUNWIND_SSP LABEL_KEYWORD DECLARE COMMENT ICMP CMP_TYPE VOID NEWLINE
	ALIGN STR_LITERAL SCANF_CALL PRINTF_CALL NSW TRUE FALSE SEXT TO
	GLOBAL COMMON NULL_KEYWORD

%type <num> NUM
%type <reg> REG LABEL GLOBAL_DEF CMP_TYPE POINTER INT_TYPE
%type <string> DEFINE param param_list
%type <array_spec> array_type

%% 

// top level of syntax tree
file:		content         {  }
			| content file  {  }

content:	func_list		{  }
			| global_list	{  }

func_list: 	func_call
			| func_list func_call 
			
func_call:	func_start LBRACE stmt_list RBRACE
						{ printf("__function definition\n"); }
			| func_start NOUNWIND LBRACE stmt_list RBRACE
						{ printf("__function definition\n"); }
            | func_start NOUNWIND_SSP LBRACE stmt_list RBRACE
						{ printf("__function definition\n"); }

func_start:	DEFINE INT_TYPE GLOBAL_DEF LPAREN param_list	RPAREN	
						{ printf("Function Header: %s\n", $1); }
            | DEFINE INT_TYPE GLOBAL_DEF LPAREN RPAREN	
						{ printf("Function Header: %s\n", $1); }
			| DEFINE VOID GLOBAL_DEF LPAREN param_list RPAREN
						{ printf("Function Header: %s\n", $1); }
            | DEFINE VOID GLOBAL_DEF LPAREN RPAREN
						{ printf("Function Header: %s\n", $1); }

param_list: param {$$ = $1;}
            | param_list COMMA param {$$ = strcat($1,$3);}
            
param:      INT_TYPE REG {$$ = $2;}
            | INT_TYPE POINTER REG {$$ = $3;}
			
//----------------------------
stmt_list:
		stmt				{  }
		| stmt_list stmt 	{  }

stmt:	alloca_stmt         {  }
		| array_type		{  }
		| label_stmt		{  }
		| addCC_stmt		{  }
		| addRR_stmt		{  }
		| addRC_stmt		{  }
		| addCR_stmt		{  }
		| subCC_stmt		{  }
		| subRR_stmt		{  }
		| subRC_stmt		{  }
		| subCR_stmt		{  }
		| brUncond_stmt     {  }
		| brCond_stmt		{  }
		| icmpRR_stmt		{  }
		| icmpCC_stmt		{  }
		| icmpRC_stmt		{  }
		| icmpCR_stmt		{  }
		| load_stmt         {  }
		| storeReg_stmt     {  }
		| storeCon_stmt     {  }
		| storePtr_stmt     {  }
		| getelementptr     {  }
		| ret_stmt          {  }
		| sext_stmt         {  }
		| scanf_call		{  }
		| printf_call		{  }
		| comment			{  }
        
// statements

alloca_stmt:	REG EQUALS ALLOCA INT_TYPE                              { allocaStmt($1, 0, $4, NULL);  }
                | REG EQUALS ALLOCA INT_TYPE COMMA INT_TYPE NUM         { allocaStmt($1, $7, $4, NULL); }
                | REG EQUALS ALLOCA INT_TYPE COMMA ALIGN NUM            { allocaStmt($1, 0, $4, NULL);  }
                | REG EQUALS ALLOCA INT_TYPE POINTER                    { strcat($4, $5); allocaStmt($1, 0, $4, NULL); }
                | REG EQUALS ALLOCA INT_TYPE POINTER COMMA INT_TYPE NUM { strcat($4, $5); allocaStmt($1, $8, $4, NULL); }
                | REG EQUALS ALLOCA INT_TYPE POINTER COMMA ALIGN NUM    { strcat($4, $5); allocaStmt($1, 0, $4, NULL); }
                | REG EQUALS ALLOCA array_type                          { allocaStmt($1, 0, NULL, &$4); }
                | REG EQUALS ALLOCA array_type COMMA INT_TYPE NUM		{ allocaStmt($1, $7, $6, &$4); }
                | REG EQUALS ALLOCA array_type COMMA ALIGN NUM          { allocaStmt($1, 0, NULL, &$4); }

label_stmt:	LABEL				{ labelStmt($1); }

addCC_stmt:	REG EQUALS ADD INT_TYPE NUM COMMA NUM
								{ param_t const1, const2;
								  const1.imm = $5;
								  const2.imm = $7;
								  add($1, const1, const2, ADD_CC); }
								  
			| REG EQUALS ADD NSW INT_TYPE NUM COMMA NUM
								{ param_t const1, const2;
								  const1.imm = $6;
								  const2.imm = $8;
								  add($1, const1, const2, ADD_CC); }

addRR_stmt:	REG EQUALS ADD INT_TYPE REG COMMA REG
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $5);
								  strcpy(reg2.reg, $7);
								  add($1, reg1, reg2, ADD_RR); }

			| REG EQUALS ADD NSW INT_TYPE REG COMMA REG
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $6);
								  strcpy(reg2.reg, $8);
								  add($1, reg1, reg2, ADD_RR); }

addRC_stmt:	REG EQUALS ADD INT_TYPE REG COMMA NUM
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $5);
								  const1.imm = $7;
								  add($1, reg1, const1, ADD_RR); }

			| REG EQUALS ADD NSW INT_TYPE REG COMMA NUM
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $6);
								  const1.imm = $8;
								  add($1, reg1, const1, ADD_RR); }

addCR_stmt:	REG EQUALS ADD INT_TYPE NUM COMMA REG
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $7);
								  const1.imm = $5;
								  sub($1, reg1, const1, ADD_CR); }

			| REG EQUALS ADD NSW INT_TYPE NUM COMMA REG
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $8);
								  const1.imm = $6;
								  sub($1, reg1, const1, ADD_CR); }

//----------------------------
subCC_stmt:	REG EQUALS SUB INT_TYPE NUM COMMA NUM
								{ param_t const1, const2;
								  const1.imm = $5;
								  const2.imm = $7;
								  sub($1, const1, const2, SUB_CC); }

			| REG EQUALS SUB NSW INT_TYPE NUM COMMA NUM
								{ param_t const1, const2;
								  const1.imm = $6;
								  const2.imm = $8;
								  sub($1, const1, const2, SUB_CC); }

subRR_stmt:	REG EQUALS SUB INT_TYPE REG COMMA REG
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $5);
								  strcpy(reg2.reg, $7);
								  sub($1, reg1, reg2, SUB_RR); }

			| REG EQUALS SUB NSW INT_TYPE REG COMMA REG
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $6);
								  strcpy(reg2.reg, $8);
								  sub($1, reg1, reg2, SUB_RR); }

subRC_stmt:	REG EQUALS SUB INT_TYPE REG COMMA NUM
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $5);
								  const1.imm = $7;
								  sub($1, reg1, const1, SUB_RR); }

			| REG EQUALS SUB NSW INT_TYPE REG COMMA NUM
								{ param_t reg1, const1;
								  strcpy(reg1.reg, $6);
								  const1.imm = $8;
								  sub($1, reg1, const1, SUB_RR); }

subCR_stmt:	REG EQUALS SUB INT_TYPE NUM COMMA REG
								{ param_t reg1, reg2;
								  reg1.imm = $5;
								  strcpy(reg2.reg, $7);
								  sub($1, reg1, reg2, SUB_CR); }

			| REG EQUALS SUB NSW INT_TYPE NUM COMMA REG
								{ param_t reg1, reg2;
								  reg1.imm = $6;
								  strcpy(reg2.reg, $8);
								  sub($1, reg1, reg2, SUB_CR); }
//----------------------------
brUncond_stmt:	BR LABEL_KEYWORD REG
								{ brUncond($3); }

brCond_stmt:	BR INT_TYPE REG COMMA LABEL_KEYWORD REG COMMA LABEL_KEYWORD REG
								{ brCond($3, $6, $9); }
			| BR INT_TYPE TRUE COMMA LABEL_KEYWORD REG COMMA LABEL_KEYWORD REG
								{ brCond("true", $6, $9); }
			| BR INT_TYPE FALSE COMMA LABEL_KEYWORD REG COMMA LABEL_KEYWORD REG
								{ brCond("false", $6, $9); }
			
//----------------------------
icmpRR_stmt:	REG EQUALS ICMP CMP_TYPE INT_TYPE REG COMMA REG
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $6);
								  strcpy(reg2.reg, $8);
								  cmpStmt($4, $1, reg1, reg2, CMP_RR); }

icmpRC_stmt:	REG EQUALS ICMP CMP_TYPE INT_TYPE REG COMMA NUM
								{ param_t reg1, reg2;
								  strcpy(reg1.reg, $6);
								  reg2.imm = $8;
								  cmpStmt($4, $1, reg1, reg2, CMP_RC); }

icmpCC_stmt:	REG EQUALS ICMP CMP_TYPE INT_TYPE NUM COMMA NUM
								{ param_t reg1, reg2;
								  reg1.imm = $6;
								  reg2.imm = $8;
								  cmpStmt($4, $1, reg1, reg2, CMP_CC); }

icmpCR_stmt:	REG EQUALS ICMP CMP_TYPE INT_TYPE NUM COMMA REG
								{ param_t reg1, reg2;
								  reg1.imm = $6;
								  strcpy(reg2.reg, $8);
								  cmpStmt($4, $1, reg1, reg2, CMP_CR); }
//----------------------------
load_stmt:	REG EQUALS LOAD INT_TYPE POINTER REG 
								{ char tmp[150]; sprintf(tmp,"%s%s",$5,$6); 
									loadStmt($1, tmp); }

			| REG EQUALS LOAD INT_TYPE POINTER REG COMMA ALIGN NUM 
								{ loadStmt($1, $5); }

storeReg_stmt:	STORE INT_TYPE REG COMMA INT_TYPE POINTER REG 
								{ param_t param;
								  strcpy(param.reg, $3);
								  storeStmt($6, param, STR_REG); }

                | STORE INT_TYPE REG COMMA INT_TYPE POINTER REG COMMA ALIGN NUM 
								{ param_t param;
								  strcpy(param.reg, $3);
								  storeStmt($6, param, STR_REG); }

storeCon_stmt:	STORE INT_TYPE NUM COMMA INT_TYPE POINTER REG 
								{ param_t param;
								  param.imm = $3;
								  storeStmt($6, param, STR_CONST); }

                | STORE INT_TYPE NUM COMMA INT_TYPE POINTER REG COMMA ALIGN NUM 
								{ param_t param;
								  param.imm = $3;
								  storeStmt($6, param, STR_CONST); }

storePtr_stmt:	STORE INT_TYPE POINTER REG COMMA INT_TYPE POINTER REG 
								{ param_t param;
								  strcpy(param.reg, $3);
								  storeStmt($7, param, STR_REG); }

                | STORE INT_TYPE POINTER REG COMMA INT_TYPE POINTER REG COMMA ALIGN NUM 
								{ param_t param;
								  strcpy(param.reg, $3);
								  storeStmt($7, param, STR_REG); }

getelementptr:	REG EQUALS GEP_INBOUNDS INT_TYPE POINTER REG COMMA INT_TYPE NUM
								{ param_t param1; param_t param2;  char tmp[50]; sprintf(tmp,"%s%s",$5,$6);
									strcpy(param1.reg,tmp); param2.imm=$9;
									getelementpointers(GEP_RC,$1, param1, param2);  }
			| REG EQUALS GEP_INBOUNDS INT_TYPE POINTER REG COMMA INT_TYPE REG
								{ param_t param1; param_t param2; char tmp[50]; sprintf(tmp,"%s%s",$5,$6);
								 strcpy(param1.reg,tmp); strcpy(param2.reg,$9);
									getelementpointers(GEP_RR,$1,param1, param2); }
			| REG EQUALS GEP_INBOUNDS INT_TYPE POINTER REG COMMA INT_TYPE REG COMMA INT_TYPE NUM
								{ /*TODO*/ }
			| REG EQUALS GEP_INBOUNDS array_type POINTER REG COMMA INT_TYPE NUM COMMA INT_TYPE NUM
								{ /*TODO*/ }
			| REG EQUALS GEP_INBOUNDS array_type POINTER REG COMMA INT_TYPE NUM COMMA INT_TYPE REG
								{ /*TODO*/ }

ret_stmt:		RET VOID				{ param_t empty; strcpy(empty.reg,"");
									return_stmt("void",empty); }
			| RET INT_TYPE NUM			{	param_t empty; strcpy(empty.reg,"");	 
								return_stmt("i32",empty); }
			| RET INT_TYPE REG			{  	param_t param; strcpy(param.reg, $3);
								return_stmt("i32",param); }
			| RET INT_TYPE POINTER REG 	{ 	param_t param; sprintf(param.reg,"%s%s",$3,$4);
							return_stmt("i32",param); }

sext_stmt:	REG EQUALS SEXT INT_TYPE REG TO INT_TYPE
            { param_t old_type, new_type; strcpy(old_type.reg, $4); strcpy(new_type.reg, $7);
              process_instruction(SEXT, $1, &old_type, &new_type, $5, NULL, NULL); }

//---------------------------

scanf_call:	REG EQUALS CALL INT_TYPE call_pointer SCANF_CALL LPAREN INT_TYPE POINTER GEP_INBOUNDS LPAREN array_type POINTER GLOBAL_DEF COMMA INT_TYPE NUM COMMA INT_TYPE NUM RPAREN COMMA param_list RPAREN
								{ /*call(CALL_SCANF, $1, $12,$17,$20, $23)*/ }
								
printf_call: REG EQUALS CALL INT_TYPE call_pointer PRINTF_CALL LPAREN INT_TYPE POINTER GEP_INBOUNDS LPAREN array_type POINTER GLOBAL_DEF COMMA INT_TYPE NUM COMMA INT_TYPE NUM RPAREN COMMA param_list RPAREN
								{  }
								
call_pointer: LPAREN INT_TYPE POINTER COMMA ELIPSIS RPAREN POINTER
								{  }
                                
//---------------------------

//global statments
global_list:	global_stmt				{  }
			| global_stmt global_list	{  }
			
global_stmt:	GLOBAL_DEF EQUALS PRIVATE UNNAMED_ADDR CONSTANT array_type STR_LITERAL
									{ printf("_______global stmt\n"); 
										/*param_t tmp1; strcpy(tmp1.reg,"");
										global_constant($1,param_t num, param_t val); TODO*/
									}
			| GLOBAL_DEF EQUALS COMMON GLOBAL INT_TYPE NUM COMMA ALIGN NUM
									{ /*TODO*/ }
			| GLOBAL_DEF EQUALS GLOBAL INT_TYPE POINTER GLOBAL_DEF COMMA ALIGN NUM
									{ /*TODO*/ }
			| GLOBAL_DEF EQUALS COMMON GLOBAL INT_TYPE POINTER NULL_KEYWORD COMMA ALIGN NUM
									{ /*TODO*/ }
			| DECLARE INT_TYPE SCANF_CALL LPAREN INT_TYPE POINTER COMMA ELIPSIS RPAREN	{  }
			| DECLARE INT_TYPE PRINTF_CALL LPAREN INT_TYPE POINTER COMMA ELIPSIS RPAREN	{  }
									
// portions of complex statments
array_type:	LBRACKET NUM X INT_TYPE RBRACKET
								{ printf("___Array Type: %d x %s\n\n", $2, $4);  
                                  array_def contents; contents.size = $2; strcpy(contents.type, $4);
                                  $$ = contents; }

comment:		COMMENT				{  }


%%
extern FILE *yyin;
 yyerror (char const *s)
     {
       fprintf (stderr, "yyerror: %s\n", s);
     }
stmt *HEAD=NULL;
stmt *current=NULL;
param_t empty;

int main(int argc, char *argv[]) {
	strcpy(empty.reg,"");	
	HEAD=NULL;
	current=NULL;
	if (argc<3) {
        printf("Incorrect parameters.\n");
        printf("project2 [outputfile] [inputfile]\n");
    }
	else {
		yyin = fopen(argv[2], "r"); 
		yyparse();
		printf("yyparse done\n");
		current=HEAD;
		FILE *fp = fopen(argv[1], "w");
		if(fp == NULL) {
			printf("Error! Could not open output file for writing.\n");
        }
		else  {
			printf("in else\n");
			while (current != NULL){
				generate_llvm(current,fp);
				current=current->next;
            }
		fclose(fp);
        }
    }
    return 0;
}


void allocaStmt(char *reg, int size, char *type, array_def *contents)
{
	param_t tmp, array_size;
    printf("___Found Alloca Statment, Reg: %s\n\n", reg);	
	tmp.imm = size;
	printf("got it\n");
    
    if (contents == NULL)
        process_instruction(ALLOC, reg, &tmp, &empty, NULL, NULL, type);
    else {
        array_size.imm = contents->size;
        process_instruction(ALLOC_ARRAY, reg, &tmp, &array_size, contents->type, NULL, type);
    }
}

void labelStmt(char *name)
{
	printf("__Label %s\n", name);
 	process_instruction(LABELL, NULL, &empty, &empty, NULL, NULL, name);
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
    
    process_instruction(type, reg, &p1, &p2, NULL, NULL, empty.reg);
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
    process_instruction(type, reg, &p1, &p2, NULL, NULL, empty.reg);
}


void brUncond(char *label)
{
	printf("__Branch: %s", &label[1]);
	process_instruction(BR_UNCOND, NULL, &empty, &empty, NULL, NULL, label);
}


void brCond(char *cond, char *trueLabel, char *falseLabel)
{
	printf("__Branch: cond: %s, true: %s, false: %s", cond, &trueLabel[1], &falseLabel[1]);
	char * arr[3] = {cond, trueLabel, falseLabel};
	process_instruction(BR_COND, NULL, &empty, &empty, NULL, arr, empty.reg);
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
    
    process_instruction(type, assignReg, &p1, &p2, comp, NULL, empty.reg);
}

void getelementpointers(int type,char *defined, param_t param1, param_t param2)
{
	printf("___GEP ");
	process_instruction(type, defined,&param1,&param2,NULL, NULL,"");

}

void global_constant(char *name,param_t num, param_t val)
{
	printf("____GBL_CONST");
	process_instruction(GLOBAL_CONST,"",&num,&val,NULL,NULL,name);
}

void loadStmt(char *destReg, char *pointer)
{
	printf("__load: %s <- %s\n\n", destReg, pointer);
	param_t tmp;
	strcpy(tmp.reg,pointer);
    
    process_instruction(LOADD, destReg, &tmp, &empty, NULL, NULL, empty.reg);
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
    
    process_instruction(type,dest,&param, &empty, NULL, NULL, empty.reg);
}

void return_stmt(char *return_type, param_t param)
{
	printf("__return statement: %s ",return_type);
	process_instruction(RETURN,empty.reg,&param,&empty,NULL, NULL,return_type);
}

void call(int type, char *defined, char *array_type, int num1, int num2, char * arg_list)
{
	param_t param1, param2; 
    
    if (type == CALL_PRINTF)
		printf("____PRINTF");
	else		
		printf("____SCANF");
    
    param1.imm=num1;
	param2.imm=num2;
    
	process_instruction(type,defined,&param1,&param2,array_type, NULL,arg_list);
}





