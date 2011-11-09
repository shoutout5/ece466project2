#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"


stmt *current=NULL;

int proccess_instruction(int type, char * defined_regs, param_t arg1, param_t arg2, char *cmp, char **branch, char *label_name){
	
	stmt *data = (stmt *) malloc(sizeof(stmt));
	data->type = type;
	data->defined_regs = defined_regs;
	if (true)
		data->imm1=imm1;
	else
		strcpy(data->arg1.reg,arg1.reg);
	if (true)
		data->imm2=imm2;
	else
		strcpy(data->reg2,reg2);
	strcpy(data->label_name,label_name);
	data->next=NULL;
	if (current != NULL)
		current->next=data;

	current=data;

	return 0;
}



char *generate_llvm(stmt stmnt){
char *output;
	switch (llvmstmt.type){

			
		case ADD_CC:
			output = sprintf("%s = add i32 %d, %d",stmnt.defined_regs,stmnt.arg1.imm,stmnt.arg2.imm);
		case ADD_RR:
			output = sprintf("%s = add i32 %s, %s",stmnt.defined_regs,stmnt.arg1.reg,stmnt.arg2.reg);
		case ADD_RC:
			output = sprintf("%s = add i32 %s, %d",stmnt.defined_regs,stmnt.arg1.reg,stmnt.arg2.imm);
		case ADD_CR:
			output = sprintf("%s = add i32 %d, %s",stmnt.defined_regs,stmnt.arg1.imm,stmnt.arg2.reg);
		case ALLOCA:
			if(stmnt.arg1.imm == NULL)
				output = sprintf("%s = alloca i32 ",stmnt.defined_regs);
			else
				output = sprintf("%s = alloca i32, i32 %d",stmnt.defined_regs, stmnt.arg1.imm);
		case BR_UNCOND:
			output = sprintf("br label %s",stmt.label_name);
		case BR_COND:
			output = sprintf("BR i1 %s, label %s, label %s",stmt.branch[0],stmt.branch[1],stmt.branch[2]);
		case CMP_CC:
			output = sprintf("%s = icmp %s i32 %d, %d",stmnt.defined_regs,stmt.cmp,stmnt.arg1.imm,stmnt.arg2.imm);
		case CMP_RR:
			output = sprintf("%s = icmp %s i32 %s, %s",stmnt.defined_regs,stmt.cmp,stmnt.arg1.reg,stmnt.arg2.reg);
		case CMP_RC:
			output = sprintf("%s = icmp %s i32 %s, %d",stmnt.defined_regs,stmt.cmp,stmnt.arg1.reg,stmnt.arg2.imm);
		case CMP_CR:
			output = sprintf("%s = icmp %s i32 %d, %s",stmnt.defined_regs,stmt.cmp,stmnt.arg1.imm,stmnt.arg2.reg);
//		case LABEL:
//		case LOAD:
//		case STR_REG:
//		case STR_CONST:
		case SUB_CC:
			output = sprintf("%s = sub i32 %d, %d",stmnt.defined_regs,stmnt.arg1.imm,stmnt.arg2.imm);
		case SUB_RR:
			output = sprintf("%s = sub i32 %s, %s",stmnt.defined_regs,stmnt.arg1.reg,stmnt.arg2.reg);
		case SUB_RC:
			output = sprintf("%s = sub i32 %s, %d",stmnt.defined_regs,stmnt.arg1.reg,stmnt.arg2.imm);
		case SUB_CR:
			output = sprintf("%s = add i32 %d, %s",stmnt.defined_regs,stmnt.arg1.imm,stmnt.arg2.reg);
		
		default: output = "Failed to identify";


		return output;
	}
}
