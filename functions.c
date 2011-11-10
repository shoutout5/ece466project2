#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"


int process_instruction(int type, char * defined_regs, param_t arg1, param_t arg2, char *cmp, char **branch, char *label_name){
	
	stmt *data = (stmt *) malloc(sizeof(stmt));
	data->type = type;
	data->defined_regs = defined_regs;
	if (type == SUB_CC || type == SUB_CR || type == ADD_CC || type == ADD_CR || type == CMP_CC || type == CMP_CR || STR_CONST )
		data->arg1.imm=arg1.imm;
	else
		strcpy(data->arg1.reg,arg1.reg);
	if (type == SUB_CC || type == SUB_RC || type == ADD_CC || type == ADD_RC || type == CMP_CC || type == CMP_RC )
		data->arg2.imm=arg2.imm;
	else
		strcpy(data->arg2.reg,arg2.reg);
	strcpy(data->label_name,label_name);
	data->next=NULL;
	if (current != NULL)
		current->next=data;
	if (HEAD == NULL)
		HEAD=data;
	current=data;
	return 0;
}



char *generate_llvm(stmt *stmnt, FILE *fp){

	char output[150];
	
	switch (stmnt->type){

		case ADD_CC:
			sprintf(output,"%s = add i32 %d, %d",stmnt->defined_regs,stmnt->arg1.imm,stmnt->arg2.imm);
		case ADD_RR:
			sprintf(output,"%s = add i32 %s, %s",stmnt->defined_regs,stmnt->arg1.reg,stmnt->arg2.reg);
		case ADD_RC:
			sprintf(output,"%s = add i32 %s, %d",stmnt->defined_regs,stmnt->arg1.reg,stmnt->arg2.imm);
		case ADD_CR:
			sprintf(output,"%s = add i32 %d, %s",stmnt->defined_regs,stmnt->arg1.imm,stmnt->arg2.reg);
		case ALLOC:
			if(stmnt->arg1.imm == 0)
				sprintf(output,"%s = alloca i32 ",stmnt->defined_regs);
			else
				sprintf(output,"%s = alloca i32, i32 %d",stmnt->defined_regs, stmnt->arg1.imm);
		case BR_UNCOND:
			sprintf(output,"br label %s",stmnt->label_name);
		case BR_COND:
			sprintf(output,"BR i1 %s, label %s, label %s",stmnt->branch[0],stmnt->branch[1],stmnt->branch[2]);
		case CMP_CC:
			sprintf(output,"%s = icmp %s i32 %d, %d",stmnt->defined_regs,stmnt->cmp,stmnt->arg1.imm,stmnt->arg2.imm);
		case CMP_RR:
			sprintf(output,"%s = icmp %s i32 %s, %s",stmnt->defined_regs,stmnt->cmp,stmnt->arg1.reg,stmnt->arg2.reg);
		case CMP_RC:
			sprintf(output,"%s = icmp %s i32 %s, %d",stmnt->defined_regs,stmnt->cmp,stmnt->arg1.reg,stmnt->arg2.imm);
		case CMP_CR:
			sprintf(output,"%s = icmp %s i32 %d, %s",stmnt->defined_regs,stmnt->cmp,stmnt->arg1.imm,stmnt->arg2.reg);
		case LABELL:
			sprintf(output,"; <label>:%s",stmnt->label_name);
		case LOADD:
			sprintf(output,"%s = load i32* %s",stmnt->defined_regs,stmnt->arg1.reg);
		case STR_REG:
			sprintf(output,"store i32 %s, i32* %s",stmnt->arg1.reg, stmnt->arg2.reg);
		case STR_CONST:
			sprintf(output,"store i32 %d, i32* %s",stmnt->arg1.imm, stmnt->arg2.reg);
		case SUB_CC:
			sprintf(output,"%s = sub i32 %d, %d",stmnt->defined_regs,stmnt->arg1.imm,stmnt->arg2.imm);
		case SUB_RR:
			sprintf(output,"%s = sub i32 %s, %s",stmnt->defined_regs,stmnt->arg1.reg,stmnt->arg2.reg);
		case SUB_RC:
			sprintf(output,"%s = sub i32 %s, %d",stmnt->defined_regs,stmnt->arg1.reg,stmnt->arg2.imm);
		case SUB_CR:
			sprintf(output,"%s = add i32 %d, %s",stmnt->defined_regs,stmnt->arg1.imm,stmnt->arg2.reg);
		
		default: sprintf(output,"Failed to identify");

	}
   fprintf(fp,"%s",output);
}
