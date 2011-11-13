%{
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "defines.h"

void allocaStmt(char *reg, int size, array_def *contents);
void labelStmt(char *name);
void add(char *reg, param_t p1, param_t p2, int type);
void sub(char *reg, param_t p1, param_t p2, int type);
void brUncond(char *label);
void brCond(char *cond, char *trueLabel, char *falseLabel);
void cmpStmt(char *comp, char *assignReg, param_t p1, param_t p2, int type);
void loadStmt(char *destReg, char *pointer);
void storeStmt(char *dest, param_t param, int type);
void return_stmt(char *return_type, param_t param);
void getelementpointers(int type,char *defined, param_t param1, param_t param2, param_t param3);
void global_constant(char *name, int size, char *strVal);
void call(int type, char *defined, int arraySize, int num1, int num2, char * arg_list);
void globalVar(char *name, char *typeData, int val);

char *type_arr[5];

#define YYERROR_VERBOSE (1)

%}

%union {
    int 	num;
    char	*string;
    char	reg[100];
    array_def array_spec;
}
%expect 3

%token ALLOCA CALL GEP_INBOUNDS LOAD STORE ADD SUB MUL DIV EQUALS REG LABEL
	DEFINE NOUNWIND	PRIVATE UNNAMED_ADDR CONSTANT RET BR GLOBAL_DEF LPAREN
	RPAREN LBRACKET RBRACKET LBRACE RBRACE INT_TYPE POINTER X COMMA NUM ELLIPSIS
	NOUNWIND_SSP LABEL_KEYWORD DECLARE COMMENT ICMP CMP_TYPE VOID NEWLINE
	ALIGN STR_LITERAL SCANF_CALL PRINTF_CALL NSW BOOLEAN SEXT TO
	GLOBAL COMMON NULL_KEYWORD

%type <num> NUM
%type <reg> REG LABEL GLOBAL_DEF CMP_TYPE POINTER INT_TYPE param param_list STR_LITERAL BOOLEAN
%type <string> DEFINE
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

param_list: param {strcpy($$,$1); printf("________________________list1: %s\n", $$);}
            | param_list COMMA param {strcpy($$,strcat($1,", "));
            					   strcpy($$,strcat($$,$3)); 
            					   printf("________________________list2: %s\n", $$);}
            
param:      INT_TYPE REG {strcpy($$,strcat($1," ")); 
					 strcpy($$,strcat($1,$2)); printf("________________________param1: %s\n", $$);}
            | INT_TYPE POINTER REG {strcpy($$,strcat($1,$2));
            					 strcpy($$,strcat($$," "));
            					 strcpy($$,strcat($$,$3)); printf("________________________param2: %s\n", $$);}
			
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

alloca_stmt:	REG EQUALS ALLOCA INT_TYPE                              { type_arr[0] = $4; 
                                                                          allocaStmt($1, 0, NULL);  }
                | REG EQUALS ALLOCA INT_TYPE COMMA INT_TYPE NUM         { type_arr[0,1] = $4,$6; 
                                                                          allocaStmt($1, $7, NULL); }
                | REG EQUALS ALLOCA INT_TYPE COMMA ALIGN NUM            { type_arr[0] = $4; 
                                                                          allocaStmt($1, 0, NULL);  }
                | REG EQUALS ALLOCA INT_TYPE POINTER                    { strcat($4, $5); type_arr[0] = $4;
                                                                          allocaStmt($1, 0, NULL); }
                | REG EQUALS ALLOCA INT_TYPE POINTER COMMA INT_TYPE NUM { strcat($4, $5); type_arr[0,1] = $4,$7; 
                                                                          allocaStmt($1, $8, NULL); }
                | REG EQUALS ALLOCA INT_TYPE POINTER COMMA ALIGN NUM    { strcat($4, $5); type_arr[0] = $4; 
                                                                          allocaStmt($1, 0, NULL); }
                | REG EQUALS ALLOCA array_type                          { allocaStmt($1, 0, &$4); }
                | REG EQUALS ALLOCA array_type COMMA INT_TYPE NUM		{ type_arr[0] = $6; 
                                                                          allocaStmt($1, $7, &$4); }
                | REG EQUALS ALLOCA array_type COMMA ALIGN NUM          { allocaStmt($1, 0, &$4); }

label_stmt:	LABEL				{ labelStmt($1); }

addCC_stmt:	REG EQUALS ADD INT_TYPE NUM COMMA NUM
								{ param_t const1, const2;
                                  type_arr[0] = $4;
                                  const1.imm = $5;
								  const2.imm = $7;
								  add($1, const1, const2, ADD_CC); }
								  
			| REG EQUALS ADD NSW INT_TYPE NUM COMMA NUM
								{ param_t const1, const2;
                                  type_arr[0] = $5;
								  const1.imm = $6;
								  const2.imm = $8;
								  add($1, const1, const2, ADD_CC_NSW); }

addRR_stmt:	REG EQUALS ADD INT_TYPE REG COMMA REG
								{ param_t reg1, reg2;
                                  type_arr[0] = $4;
								  strcpy(reg1.reg, $5);
								  strcpy(reg2.reg, $7);
								  add($1, reg1, reg2, ADD_RR); }

			| REG EQUALS ADD NSW INT_TYPE REG COMMA REG
								{ param_t reg1, reg2;
                                  type_arr[0] = $5;
								  strcpy(reg1.reg, $6);
								  strcpy(reg2.reg, $8);
								  add($1, reg1, reg2, ADD_RR_NSW); }

addRC_stmt:	REG EQUALS ADD INT_TYPE REG COMMA NUM
								{ param_t reg1, const1;
                                  type_arr[0] = $4;
								  strcpy(reg1.reg, $5);
								  const1.imm = $7;
								  add($1, reg1, const1, ADD_RR); }

			| REG EQUALS ADD NSW INT_TYPE REG COMMA NUM
								{ param_t reg1, const1;
                                  type_arr[0] = $5;
								  strcpy(reg1.reg, $6);
								  const1.imm = $8;
								  add($1, reg1, const1, ADD_RR_NSW); }

addCR_stmt:	REG EQUALS ADD INT_TYPE NUM COMMA REG
								{ param_t reg1, const1;
                                  type_arr[0] = $4;
								  strcpy(reg1.reg, $7);
								  const1.imm = $5;
								  sub($1, reg1, const1, ADD_CR); }

			| REG EQUALS ADD NSW INT_TYPE NUM COMMA REG
								{ param_t reg1, const1;
                                  type_arr[0] = $5;
								  strcpy(reg1.reg, $8);
								  const1.imm = $6;
								  sub($1, reg1, const1, ADD_CR_NSW); }

//----------------------------
subCC_stmt:	REG EQUALS SUB INT_TYPE NUM COMMA NUM
								{ param_t const1, const2;
                                  type_arr[0] = $4;
								  const1.imm = $5;
								  const2.imm = $7;
								  sub($1, const1, const2, SUB_CC); }

			| REG EQUALS SUB NSW INT_TYPE NUM COMMA NUM
								{ param_t const1, const2;
                                  type_arr[0] = $5;
								  const1.imm = $6;
								  const2.imm = $8;
								  sub($1, const1, const2, SUB_CC_NSW); }

subRR_stmt:	REG EQUALS SUB INT_TYPE REG COMMA REG
								{ param_t reg1, reg2;
                                  type_arr[0] = $4;
								  strcpy(reg1.reg, $5);
								  strcpy(reg2.reg, $7);
								  sub($1, reg1, reg2, SUB_RR); }

			| REG EQUALS SUB NSW INT_TYPE REG COMMA REG
								{ param_t reg1, reg2;
                                  type_arr[0] = $5;
								  strcpy(reg1.reg, $6);
								  strcpy(reg2.reg, $8);
								  sub($1, reg1, reg2, SUB_RR_NSW); }

subRC_stmt:	REG EQUALS SUB INT_TYPE REG COMMA NUM
								{ param_t reg1, const1;
                                  type_arr[0] = $4;  
								  strcpy(reg1.reg, $5);
								  const1.imm = $7;
								  sub($1, reg1, const1, SUB_RR); }

			| REG EQUALS SUB NSW INT_TYPE REG COMMA NUM
								{ param_t reg1, const1;
                                  type_arr[0] = $5;
								  strcpy(reg1.reg, $6);
								  const1.imm = $8;
								  sub($1, reg1, const1, SUB_RR_NSW); }

subCR_stmt:	REG EQUALS SUB INT_TYPE NUM COMMA REG
								{ param_t reg1, reg2;
                                  type_arr[0] = $4;
								  reg1.imm = $5;
								  strcpy(reg2.reg, $7);
								  sub($1, reg1, reg2, SUB_CR); }

			| REG EQUALS SUB NSW INT_TYPE NUM COMMA REG
								{ param_t reg1, reg2;
                                  type_arr[0] = $5;
								  reg1.imm = $6;
								  strcpy(reg2.reg, $8);
								  sub($1, reg1, reg2, SUB_CR_NSW); }
//----------------------------
brUncond_stmt:	BR LABEL_KEYWORD REG
								{ brUncond($3); }

brCond_stmt:	BR INT_TYPE REG COMMA LABEL_KEYWORD REG COMMA LABEL_KEYWORD REG
								{ type_arr[0] = $2; brCond($3, $6, $9); }
			| BR INT_TYPE BOOLEAN COMMA LABEL_KEYWORD REG COMMA LABEL_KEYWORD REG
								{ type_arr[0] = $2; brCond($3, $6, $9); }
			
//----------------------------
icmpRR_stmt:	REG EQUALS ICMP CMP_TYPE INT_TYPE REG COMMA REG
								{ param_t reg1, reg2;
                                  type_arr[0] = $5;
								  strcpy(reg1.reg, $6);
								  strcpy(reg2.reg, $8);
								  cmpStmt($4, $1, reg1, reg2, CMP_RR); }

icmpRC_stmt:	REG EQUALS ICMP CMP_TYPE INT_TYPE REG COMMA NUM
								{ param_t reg1, reg2;
                                  type_arr[0] = $5;
								  strcpy(reg1.reg, $6);
								  reg2.imm = $8;
								  cmpStmt($4, $1, reg1, reg2, CMP_RC); }

icmpCC_stmt:	REG EQUALS ICMP CMP_TYPE INT_TYPE NUM COMMA NUM
								{ param_t reg1, reg2;
                                  type_arr[0] = $5;
								  reg1.imm = $6;
								  reg2.imm = $8;
								  cmpStmt($4, $1, reg1, reg2, CMP_CC); }

icmpCR_stmt:	REG EQUALS ICMP CMP_TYPE INT_TYPE NUM COMMA REG
								{ param_t reg1, reg2;
                                  type_arr[0] = $5; 
								  reg1.imm = $6;
								  strcpy(reg2.reg, $8);
								  cmpStmt($4, $1, reg1, reg2, CMP_CR); }
//----------------------------
load_stmt:	REG EQUALS LOAD INT_TYPE POINTER REG 
								{ strcat($4, $5);
                                  type_arr[0] = $4;
                                  loadStmt($1, $4); }

                | REG EQUALS LOAD INT_TYPE POINTER REG COMMA ALIGN NUM 
								{ strcat($4, $5);
                                  type_arr[0] = $4;
                                  loadStmt($1, $4); }

storeReg_stmt:	STORE INT_TYPE REG COMMA INT_TYPE POINTER REG 
								{ strcat($5,$6);
                                  type_arr[0,1] = $2,$5;
                                  param_t param;
								  strcpy(param.reg, $3);
								  storeStmt($5, param, STR_REG); }

                | STORE INT_TYPE REG COMMA INT_TYPE POINTER REG COMMA ALIGN NUM 
								{ strcat($5,$6); 
                                  type_arr[0,1] = $2,$5;
                                  param_t param;
								  strcpy(param.reg, $3);
								  storeStmt($5, param, STR_REG); }

storeCon_stmt:	STORE INT_TYPE NUM COMMA INT_TYPE POINTER REG 
								{ strcat($5,$6);
                                  type_arr[0,1] = $2,$5;
                                  param_t param;
								  param.imm = $3;
								  storeStmt($5, param, STR_CONST); }

                | STORE INT_TYPE NUM COMMA INT_TYPE POINTER REG COMMA ALIGN NUM 
								{ strcat($5,$6);
                                  type_arr[0,1] = $2,$5;
                                  param_t param;
								  param.imm = $3;
								  storeStmt($5, param, STR_CONST); }

storePtr_stmt:	STORE INT_TYPE POINTER REG COMMA INT_TYPE POINTER REG 
                                { strcat($2,$3); strcat($6,$7);
                                  type_arr[0,1] = $2,$6;
                                  param_t param;
								  strcpy(param.reg, $4);
								  storeStmt($8, param, STR_REG); }

                | STORE INT_TYPE POINTER REG COMMA INT_TYPE POINTER REG COMMA ALIGN NUM 
								{ strcat($2,$3); strcat($6,$7);
                                  type_arr[0,1] = $2,$6;
                                  param_t param;
								  strcpy(param.reg, $4);
								  storeStmt($8, param, STR_REG); }

getelementptr:	REG EQUALS GEP_INBOUNDS INT_TYPE POINTER REG COMMA INT_TYPE NUM
								{ char first[100]; param_t param1; param_t param2; param_t empty; strcpy(empty.reg,"");
                              						 sprintf(first,"%s%s",$4,$5); param2.imm=$9; type_arr[0,1] = first, $8;// type_arr[1]=$8;
									getelementpointers(GEP_RC, $1, param1, param2, empty);  }
			| REG EQUALS GEP_INBOUNDS INT_TYPE POINTER REG COMMA INT_TYPE REG
								{ param_t param1; param_t param2; param_t empty; strcpy(empty.reg,"");
                                				  strcat($4,$5); strcpy(param2.reg,$9); type_arr[0,1] = $4,$8;
									getelementpointers(GEP_RR,$1,param1, param2, empty); }
			| REG EQUALS GEP_INBOUNDS INT_TYPE POINTER REG COMMA INT_TYPE REG COMMA INT_TYPE NUM
								{ param_t param1; param_t param2; param_t param3; char array_str[50];
                                				  strcat($4,$5); strcpy(param1.reg,$6); strcpy(param2.reg,$9); 
								  type_arr[0,1,2] = $4,$8,$11; sprintf(param3.reg,"%d",$12);
								  getelementpointers(GEP_RRC,$1,param1,param2,param3); }
			| REG EQUALS GEP_INBOUNDS array_type POINTER REG COMMA INT_TYPE NUM COMMA INT_TYPE NUM
								{ param_t param1; param_t param2; param_t param3;  param3.imm=$12; char array_str[50];
								strcpy(param1.reg,$6); param2.imm=$9; sprintf(array_str,"[%d x %s]%s",$4.size,$4.type,$5);
								type_arr[0,1,2] = array_str,$8,$11; getelementpointers(GEP_RCC,$1,param1,param2,param3); }
			| REG EQUALS GEP_INBOUNDS array_type POINTER REG COMMA INT_TYPE NUM COMMA INT_TYPE REG
								{ /*param_t param1; param_t param2; param_t param3; param3.reg="fixme"; char array_str[50];
									strcat($4,$5); strcpy(param1.reg,$6); strcpy(param2.reg,$9); sprintf(array_str,"[%d x %s]%s",$4.size,$4.type,$5);
									type_arr[0,1,2] = array_str,$8,$11; getelementpointers(GEP_RCR,$1,param1,param2,param3)*/ }

ret_stmt:		RET VOID				{ param_t empty; strcpy(empty.reg,"");
                                          return_stmt("void",empty); }
			| RET INT_TYPE NUM			{ param_t empty; strcpy(empty.reg,"");	 
                                          return_stmt($2,empty); }
			| RET INT_TYPE REG			{ param_t param; strcpy(param.reg, $3);
                                          return_stmt($2,param); }
            | RET INT_TYPE POINTER REG 	{ param_t param; sprintf(param.reg,"%s%s",$3,$4); strcat($2, $3);
                                          return_stmt($2, param); }

sext_stmt:	REG EQUALS SEXT INT_TYPE REG TO INT_TYPE
            { param_t old_type, new_type; strcpy(old_type.reg, $4); strcpy(new_type.reg, $7);
              process_instruction(SEXT, $1, &old_type, &new_type, $5, NULL, NULL); }

//---------------------------

scanf_call:	REG EQUALS CALL INT_TYPE call_pointer SCANF_CALL LPAREN INT_TYPE POINTER GEP_INBOUNDS LPAREN array_type POINTER GLOBAL_DEF COMMA INT_TYPE NUM COMMA INT_TYPE NUM RPAREN COMMA param_list RPAREN
								{ call(CALL_SCANF, $1, $12.size,$17,$20, $23); }
								
printf_call: REG EQUALS CALL INT_TYPE call_pointer PRINTF_CALL LPAREN INT_TYPE POINTER GEP_INBOUNDS LPAREN array_type POINTER GLOBAL_DEF COMMA INT_TYPE NUM COMMA INT_TYPE NUM RPAREN COMMA param_list RPAREN
								{ call(CALL_PRINTF, $1, $12.size,$17,$20, $23); }
								
call_pointer: LPAREN INT_TYPE POINTER COMMA ELLIPSIS RPAREN POINTER
								{  }
                                
//---------------------------

//global statments
global_list:	global_stmt				{  }
			| global_stmt global_list	{  }
			
global_stmt:	GLOBAL_DEF EQUALS PRIVATE UNNAMED_ADDR CONSTANT array_type STR_LITERAL
									{ printf("__global stmt\n");  
									  global_constant($1, $6.size, $7); }
			| GLOBAL_DEF EQUALS COMMON GLOBAL INT_TYPE NUM COMMA ALIGN NUM
									{ char data[50];
									  strcpy(data, "common global ");
									  strcat(data, $5);
									  printf("____________________here: %s\n", data);
									  globalVar($1, data, $6); }
			| GLOBAL_DEF EQUALS GLOBAL INT_TYPE POINTER GLOBAL_DEF COMMA ALIGN NUM
									{ /*TODO*/ }
			| GLOBAL_DEF EQUALS COMMON GLOBAL INT_TYPE POINTER NULL_KEYWORD COMMA ALIGN NUM
									{ /*TODO*/ }
			| DECLARE INT_TYPE SCANF_CALL LPAREN INT_TYPE POINTER COMMA ELLIPSIS RPAREN	{  }
			| DECLARE INT_TYPE PRINTF_CALL LPAREN INT_TYPE POINTER COMMA ELLIPSIS RPAREN	{  }
									
// portions of complex statments
array_type:	LBRACKET NUM X INT_TYPE RBRACKET
								{ printf("___Array Type: %d x %s\n\n", $2, $4);  
                                  array_def contents; contents.size = $2; contents.type = $4;
                                  $$ = contents; printf("test\n");}

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
        if(yyin == NULL) {
			printf("Error! Could not open input file for reading.\nPlease check your spelling and try again.\n");
        }
		yyparse();
		printf("yyparse done\n");
		current=HEAD;
		FILE *fp = fopen(argv[1], "w");
		if(fp == NULL) {
			printf("Error! Could not open output file for writing.\nPlease check your spelling and try again.\n");
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


void allocaStmt(char *reg, int size, array_def *contents)
{
	param_t tmp, array_size;
    printf("___Found Alloca Statment, Reg: %s\n\n", reg);	
	tmp.imm = size;
    
    if (contents == NULL)
        process_instruction(ALLOC, reg, &tmp, &empty, NULL, type_arr, "");
    else {
        array_size.imm = contents->size;
        process_instruction(ALLOC_ARRAY, reg, &tmp, &array_size, contents->type, type_arr, "");
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
    
    process_instruction(type, reg, &p1, &p2, NULL, type_arr, empty.reg);
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
    process_instruction(type, reg, &p1, &p2, NULL, type_arr, empty.reg);
}


void brUncond(char *label)
{
	printf("__Branch: %s", &label[1]);
	process_instruction(BR_UNCOND, NULL, &empty, &empty, NULL, type_arr, label);
}


void brCond(char *cond, char *trueLabel, char *falseLabel)
{
	printf("__Branch: cond: %s, true: %s, false: %s", cond, &trueLabel[1], &falseLabel[1]);
	char * arr[3] = {cond, trueLabel, falseLabel};
	process_instruction(BR_COND, NULL, &empty, &empty, NULL, type_arr, empty.reg);
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
    
    process_instruction(type, assignReg, &p1, &p2, comp, type_arr, empty.reg);
}

void getelementpointers(int type,char *defined, param_t param1, param_t param2, param_t param3)
{
	printf("___GEP ");
	process_instruction(type, defined,&param1,&param2,param3.reg,type_arr,"");

}

void global_constant(char *name, int size, char *strVal)
{
	param_t value, sizeParam;
	printf("____GBL_CONST");
	strcpy(value.reg, strVal);
	sizeParam.imm = size;
	process_instruction(GLOBAL_CONST,name,&sizeParam,&value,"",NULL,"");
}

void loadStmt(char *destReg, char *pointer)
{
	printf("__load: %s <- %s\n\n", destReg, pointer);
	param_t tmp;
	strcpy(tmp.reg,pointer);
    
    process_instruction(LOADD, destReg, &tmp, &empty, NULL, type_arr, empty.reg);
}


void storeStmt(char *dest, param_t param, int type)
{
	if(type == STR_REG)
	{
		printf("__store: %s <- %s\n\n", dest, param.reg);
	}
	else if(type == STR_CONST)
	{
		printf("__store: %s <- %d\n\n", dest, param.imm);
	}
    
    process_instruction(type,dest,&param, &empty, NULL, type_arr, empty.reg);
}

void return_stmt(char *return_type, param_t param)
{
	printf("__return statement: %s ",return_type);
	process_instruction(RETURN,empty.reg,&param,&empty,NULL, type_arr, return_type);
}

void call(int type, char *defined, int arraySize, int num1, int num2, char * arg_list)
{
	param_t param1, param2; 
    
    if (type == CALL_PRINTF)
		printf("____PRINTF");
	else		
		printf("____SCANF");
    
    param1.imm=arraySize;
	param2.imm=arraySize;
    
	process_instruction(type,defined,&param1,&param2,NULL, NULL,arg_list);
}

void globalVar(char *name, char *typeData, int val)
{
	
}

















