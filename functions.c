#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"


int process_instruction(int type, char * defined_regs, param_t *arg1, param_t *arg2, char *cmp, char **branch, char *label_name){
    printf("starting\n");
	stmt *data = (stmt *) malloc(sizeof(stmt));
	data->type = type;
	
	printf("______________-------------______________ orig: %s\n",defined_regs);
	if(defined_regs != NULL)
		strcpy(data->defined_regs, defined_regs);
	else
		strcpy(data->defined_regs,"");
	printf("______________-------------______________ copy: %s\n",data->defined_regs);
	if (type == SUB_CC || type == SUB_CR || type == ADD_CC || type == ADD_CR || type == CMP_CC || type == CMP_CR || STR_CONST || type == ALLOC_ARRAY )
		data->arg1.imm=arg1->imm;
	else
		strcpy(data->arg1.reg,arg1->reg);
	if (type == SUB_CC || type == SUB_RC || type == ADD_CC || type == ADD_RC || type == CMP_CC || type == CMP_RC || type == ALLOC_ARRAY )
		data->arg2.imm=arg2->imm;
	else
		strcpy(data->arg2.reg,arg2->reg);
	strcpy(data->label_name,label_name);
    
	data->next=NULL;
	if (current != NULL)
		current->next=data;
	if (HEAD == NULL)
		HEAD=data;
	current=data;
	printf("finished\n");
	return 0;
}



void generate_llvm(stmt *stmnt, FILE *fp){
    
	char output[150];
	switch (stmnt->type){
            
		case ADD_CC:
			sprintf(output,"%s = add i32 %d, %d \n",stmnt->defined_regs,stmnt->arg1.imm,stmnt->arg2.imm);
			break;
		case ADD_RR:
			sprintf(output,"%s = add i32 %s, %s \n",stmnt->defined_regs,stmnt->arg1.reg,stmnt->arg2.reg);
			break;
		case ADD_RC:
			sprintf(output,"%s = add i32 %s, %d \n",stmnt->defined_regs,stmnt->arg1.reg,stmnt->arg2.imm);
			break;
		case ADD_CR:
			sprintf(output,"%s = add i32 %d, %s \n",stmnt->defined_regs,stmnt->arg1.imm,stmnt->arg2.reg);
			break;
		case ALLOC:
			if(stmnt->arg1.imm == 0) {
				sprintf(output,"%s = alloca i32 \n",stmnt->defined_regs);
				break;
			}
			else {
				sprintf(output,"%s = alloca i32, i32 %d \n",stmnt->defined_regs, stmnt->arg1.imm);
				break;
			}
		case BR_UNCOND:
			sprintf(output,"br label %s \n",stmnt->label_name);
			break;
		case BR_COND:
			sprintf(output,"br i1 %s, label %s, label %s \n",stmnt->branch[0],stmnt->branch[1],stmnt->branch[2]);
			break;
		case CALL_PRINTF:
			sprintf(output,"%s = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str0, i32 0, i32 0), i32 %%r9)",stmnt->defined_regs);
			break;
		case CALL_SCANF:
			sprintf(output,"%s = call i32 (i8*, ...)* @scanf(i8* getelementptr inbounds ([3 x i8]* @.str0, i32 0, i32 0), i32* %%a)",stmnt->defined_regs);
			break;
		case CMP_CC:
			sprintf(output,"%s = icmp %s i32 %d, %d \n",stmnt->defined_regs,stmnt->cmp,stmnt->arg1.imm,stmnt->arg2.imm);
			break;
		case CMP_RR:
			sprintf(output,"%s = icmp %s i32 %s, %s \n",stmnt->defined_regs,stmnt->cmp,stmnt->arg1.reg,stmnt->arg2.reg);
			break;
		case CMP_RC:
			sprintf(output,"%s = icmp %s i32 %s, %d \n",stmnt->defined_regs,stmnt->cmp,stmnt->arg1.reg,stmnt->arg2.imm);
			break;
		case CMP_CR:
			sprintf(output,"%s = icmp %s i32 %d, %s \n",stmnt->defined_regs,stmnt->cmp,stmnt->arg1.imm,stmnt->arg2.reg);
			break;
		case GEP_RR:
			sprintf(output,"%s = getelementptr inbounds i32 %s, i32 %s",stmnt->defined_regs,stmnt->arg1.reg,stmnt->arg2.reg);
			break;
		case GEP_RC:
			sprintf(output,"%s = getelementptr inbounds i32 %s, i32 %d",stmnt->defined_regs,stmnt->arg1.reg,stmnt->arg2.imm);
			break;
		case GLOBAL_CONST:
			sprintf(output,"@.%s = private unnamed_addr constant [%d x i8] c%s",stmnt->label_name,stmnt->arg1.imm,stmnt->arg2.reg);
			break;
		case LABELL:
			sprintf(output,"; <label>:%s \n",stmnt->label_name);
			break;
		case LOADD:
			sprintf(output,"%s = load i32* %s \n",stmnt->defined_regs,stmnt->arg1.reg);
			break;
		case RETURN:
			sprintf(output,"ret %s %s",stmnt->label_name,stmnt->arg1.reg);
			break;
		case STR_REG:
			sprintf(output,"store i32 %s, i32* %s \n",stmnt->arg1.reg, stmnt->arg2.reg);
			break;
		case STR_CONST:
			sprintf(output,"store i32 %d, i32* %s \n",stmnt->arg1.imm, stmnt->arg2.reg);
			break;
		case SUB_CC:
			sprintf(output,"%s = sub i32 %d, %d \n",stmnt->defined_regs,stmnt->arg1.imm,stmnt->arg2.imm);
			break;
		case SUB_RR:
			sprintf(output,"%s = sub i32 %s, %s \n",stmnt->defined_regs,stmnt->arg1.reg,stmnt->arg2.reg);
			break;
		case SUB_RC:
			sprintf(output,"%s = sub i32 %s, %d \n",stmnt->defined_regs,stmnt->arg1.reg,stmnt->arg2.imm);
			break;
		case SUB_CR:
			sprintf(output,"%s = add i32 %d, %s \n",stmnt->defined_regs,stmnt->arg1.imm,stmnt->arg2.reg);
			break;
            
            
		default: sprintf(output,"Failed to identify");
            
	}
    fprintf(fp,"%s",output);
}
