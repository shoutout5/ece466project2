#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"


stmt *current=NULL;

int proccess_instruction(int type, char * defined_regs, param_t arg1, param_t arg2, ,int cmp, char **branch, char *label_name){
	
	stmt *data = (stmt *) malloc(sizeof(stmt));
	data->type = type;
	data->defined_regs = defined_regs;
	if (arg1.	
		data->imm1=imm1;
	else
		strcpy(data->arg1.reg,arg1.reg);
	if (
		data->imm2=imm2;
	else
		strcpy(data->reg2,reg2);
	strcpy(data->label_name,label_name);
	data->next=NULL;
	if (current != NULL)
		current->next=data;

	current=data;

	
}
