#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "project2.y.h"

extern char type_arr[6][100];

int process_instruction(int type, char *defined_regs, param_t *arg1, param_t *arg2, char *cmp, char **branch, char *label_name){
    int i;
    
    printf("starting\n");
	stmt *data = (stmt *) malloc(sizeof(stmt));
	data->type = type;
	
	if(defined_regs != NULL)
		strcpy(data->defined_regs, defined_regs);
	else
		strcpy(data->defined_regs,"");
		
	if (type == SUB_CC || type == SUB_CR || type == ADD_CC || type == ADD_CR || type == CMP_CC || type == CMP_CR || type == STR_CONST || type == ALLOC_ARRAY || type == CALL_PRINTF || type == ADD_CR || type == CMP_CC || type == CMP_CR || type == ALLOC_ARRAY || type == CALL_SCANF || type == GLOBAL_CONST || type == RET_NUM)
		data->arg1.imm=arg1->imm;
	else
		strcpy(data->arg1.reg,arg1->reg);
	if (type == SUB_CC || type == SUB_RC || type == ADD_CC || type == ADD_RC || type == CMP_CC || type == CMP_RC || type == ALLOC_ARRAY || type == CALL_SCANF || type == CALL_PRINTF || type == GEP_RC || type == GEP_RCC)
		data->arg2.imm=arg2->imm;
	else
		strcpy(data->arg2.reg,arg2->reg);
	strcpy(data->label_name,label_name);
    
    if (cmp != NULL)
        strcpy(data->cmp, cmp);
    
    for(i=0; i<=5; i++)
    {
		if(type_arr[i] != NULL)
        {
			//printf("%d %s\n", i, type_arr[i]);
            strcpy(data->branch[i],type_arr[i]);
        }
    }

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
			sprintf(output,"  %s = add %s %d, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.imm);
			break;
		case ADD_RR:
			sprintf(output,"  %s = add %s %s, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.reg);
			break;
		case ADD_RC:
			sprintf(output,"  %s = add %s %s, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.imm);
			break;
		case ADD_CR:
			sprintf(output,"  %s = add %s %d, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.reg);
			break;
		case ADD_CC_NSW:
			sprintf(output,"  %s = add nsw %s %d, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.imm);
			break;
		case ADD_RR_NSW:
			sprintf(output,"  %s = add nsw %s %s, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.reg);
			break;
		case ADD_RC_NSW:
			sprintf(output,"  %s = add nsw %s %s, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.imm);
			break;
		case ADD_CR_NSW:
			sprintf(output,"  %s = add nsw %s %d, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.reg);
			break;
		case ALLOC:
			if(stmnt->arg1.imm == 0) {
				sprintf(output,"  %s = alloca %s\n",stmnt->defined_regs,stmnt->branch[0]);
				break;
			}
			else {
				sprintf(output,"  %s = alloca %s, %s %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->branch[1], stmnt->arg1.imm);
				break;
			}
		case ALLOC_ARRAY:
            if(stmnt->arg1.imm == 0) {
				sprintf(output,"  %s = alloca %s\n",stmnt->defined_regs, stmnt->branch[0]);
				break;
			}
			else {
				sprintf(output,"  %s = alloca %s, %s %d\n",stmnt->defined_regs, stmnt->branch[0],stmnt->branch[1], stmnt->arg1.imm);
				break;
			}
		case BR_UNCOND:
			sprintf(output,"  br label %s\n",stmnt->label_name);
			break;
		case BR_COND:
			sprintf(output,"  br %s %s, label %s, label %s\n",stmnt->branch[0],stmnt->branch[1],stmnt->branch[2],stmnt->branch[3]);
			break;
		case CALL_PRINTF:
			sprintf(output,"  %s = call %s (%s, ...)* @printf(%s getelementptr inbounds (%s %s, %s %d, %s %d), %s)\n", stmnt->defined_regs, stmnt->branch[0], stmnt->branch[1], stmnt->branch[2], stmnt->branch[3], stmnt->cmp, stmnt->branch[4], stmnt->arg1.imm, stmnt->branch[5], stmnt->arg2.imm, stmnt->label_name);			
            break;
		case CALL_SCANF:
			sprintf(output,"  %s = call %s (%s, ...)* @scanf(%s getelementptr inbounds (%s %s, %s %d, %s %d), %s)\n", stmnt->defined_regs, stmnt->branch[0], stmnt->branch[1], stmnt->branch[2], stmnt->branch[3], stmnt->cmp, stmnt->branch[4], stmnt->arg1.imm, stmnt->branch[5], stmnt->arg2.imm, stmnt->label_name);	
			break;
		case CMP_CC:
			sprintf(output,"  %s = icmp %s %s %d, %d\n",stmnt->defined_regs,stmnt->cmp,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.imm);
			break;
		case CMP_RR:
			sprintf(output,"  %s = icmp %s %s %s, %s\n",stmnt->defined_regs,stmnt->cmp,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.reg);
			break;
		case CMP_RC:
			sprintf(output,"  %s = icmp %s %s %s, %d\n",stmnt->defined_regs,stmnt->cmp,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.imm);
			break;
		case CMP_CR:
			sprintf(output,"  %s = icmp %s %s %d, %s\n",stmnt->defined_regs,stmnt->cmp,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.reg);
			break;
        case SDIV_RR:
            sprintf(output,"  %s = sdiv %s %s, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.reg);
            break;
        case SDIV_RC:
            sprintf(output,"  %s = sdiv %s %s, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.imm);
            break;
        case SDIV_CR:
            sprintf(output,"  %s = sdiv %s %d, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.reg);
            break;
        case SDIV_CC:
            sprintf(output,"  %s = sdiv %s %d, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.imm);
            break;
        case SDIV_RR_NSW:
            sprintf(output,"  %s = sdiv nsw %s %s, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.reg);
            break;
        case SDIV_RC_NSW:
            sprintf(output,"  %s = sdiv nsw %s %s, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.imm);
            break;
        case SDIV_CR_NSW:
            sprintf(output,"  %s = sdiv nsw %s %d, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.reg);
            break;
		case SDIV_CC_NSW:
            sprintf(output,"  %s = sdiv nsw %s %d, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.imm);
            break;
		case GEP_RR:
			sprintf(output,"  %s = getelementptr inbounds %s %s, %s %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->branch[1],stmnt->arg2.reg);
			break;
		case GEP_RC:
			sprintf(output,"  %s = getelementptr inbounds %s %s, %s %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->branch[1],stmnt->arg2.imm);
			break;
		case GEP_RCC:
			sprintf(output,"  %s = getelementptr inbounds %s %s, %s %d, %s %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->branch[1],stmnt->arg2.imm,stmnt->branch[2],stmnt->cmp);
			break;
		case GEP_RCR:
			sprintf(output,"  %s = getelementptr inbounds %s %s, %s %s, %s %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->branch[1],stmnt->cmp,stmnt->branch[2],stmnt->arg2.reg);
			break;
		case GEP_RRC:
			sprintf(output,"  %s = getelementptr inbounds %s %s, %s %s, %s %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->branch[1],stmnt->arg2.reg,stmnt->branch[2],stmnt->cmp);
			break;
		case GEP_RRR:
			printf("Need to implement GEP_RRR\n");
			break;
		case GLOBAL_CONST:
			sprintf(output,"%s = private unnamed_addr constant [%d x i8] %s\n",stmnt->defined_regs,stmnt->arg1.imm,stmnt->arg2.reg);
			break;
		case LABELL:
			sprintf(output,"\n; <label>:%s",stmnt->label_name);
			break;
		case LOADD:
			sprintf(output,"  %s = load %s %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg);
			break;
        case MUL_RR:
            sprintf(output,"  %s = mul  %s %s, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.reg);
            break;
        case MUL_RC:
            sprintf(output,"  %s = mul %s %s, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.imm);
            break;
        case MUL_CR:
            sprintf(output,"  %s = mul %s %d, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.reg);
            break;
        case MUL_CC:
            sprintf(output,"  %s = mul %s %d, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.imm);
            break;
        case MUL_RR_NSW:
            sprintf(output,"  %s = mul nsw %s %s, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.reg);
            break;
        case MUL_RC_NSW:
            sprintf(output,"  %s = mul nsw %s %s, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.imm);
            break;
        case MUL_CR_NSW:
            sprintf(output,"  %s = mul nsw %s %d, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.reg);
            break;
        case MUL_CC_NSW:
            sprintf(output,"  %s = mul nsw %s %d, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.imm);
            break;
		case RET_NUM:
			sprintf(output,"  ret %s %d\n",stmnt->label_name,stmnt->arg1.imm);
			break;
        case RET_REG:
			sprintf(output,"  ret %s %s\n",stmnt->label_name,stmnt->arg1.reg);
			break;
        case SEXT:
            sprintf(output,"  %s = sext %s %s to %s\n",stmnt->defined_regs,stmnt->branch[0], stmnt->arg1.reg, stmnt->branch[1]);
            break;
		case STR_REG:
			sprintf(output,"  store %s %s, %s %s\n",stmnt->branch[0],stmnt->arg1.reg,stmnt->branch[1],stmnt->defined_regs);
			break;
		case STR_CONST:
			sprintf(output,"  store %s %d, %s %s\n",stmnt->branch[0],stmnt->arg1.imm, stmnt->branch[1],stmnt->defined_regs);
			break;
		case SUB_CC:
			sprintf(output,"  %s = sub %s %d, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.imm);
			break;
		case SUB_RR:
			sprintf(output,"  %s = sub %s %s, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.reg);
			break;
		case SUB_RC:
			sprintf(output,"  %s = sub %s %s, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.imm);
			break;
		case SUB_CR:
			sprintf(output,"  %s = sub %s %d, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.reg);
			break;
 		case SUB_CC_NSW:
			sprintf(output,"  %s = sub nsw %s %d, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.imm);
			break;
		case SUB_RR_NSW:
			sprintf(output,"  %s = sub nsw %s %s, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.reg);
			break;
		case SUB_RC_NSW:
			sprintf(output,"  %s = sub nsw %s %s, %d\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.reg,stmnt->arg2.imm);
			break;
		case SUB_CR_NSW:
			sprintf(output,"  %s = sub nsw %s %d, %s\n",stmnt->defined_regs,stmnt->branch[0],stmnt->arg1.imm,stmnt->arg2.reg);
			break;   
		case DEC_SCANF:
			sprintf(output, "declare i32 @scanf(i8*, ...)\n\n");
			break;
		case DEC_PRINTF:   
			sprintf(output, "declare i32 @printf(i8*, ...)\n\n");
			break;    
		case FUNC_DEC:
			sprintf(output, "\n%s {\n", stmnt->label_name);
			break; 
		case FUNC_END:
			sprintf(output, "}\n\n");
			break;
        case GLOBAL_VAR:
			sprintf(output, "%s = %s %d\n", stmnt->defined_regs, stmnt->label_name, stmnt->arg1.imm);
			break;
            
		default: sprintf(output,"Failed to identify \n");
            
	}
    fprintf(fp,"%s",output);
}

void register_promotion() {
current = HEAD;
char names[200][50];
int count=0;

while(current != NULL) {
	if( current->type == ALLOC || current->type == GLOBAL_VAR ) {
 		strcpy(names[count++],current->defined_regs);
	}
	current=current->next;
}
int i;
for (i=0; i<count; i++){
	printf("name  %d: %s\n",i,names[i]);
}


}

void dead_code(){
/*
current=HEAD;
//stmnt *step=HEAD;
char dead[100][50]; 

while(current != NULL) {
	if( current->defined_regs != NULL && strcmp(current->defined_regs,"") ) {
 		printf("defd found: %s\n",current->defined_regs);
	
		while(step=>next != NULL){
			if (type != SUB_CC || type != SUB_CR || type != ADD_CC || type != ADD_CR || type != CMP_CC || type != CMP_CR || type != ALLOC_ARRAY || type != CALL_PRINTF || type != ADD_CR || type != CMP_CC || type != CMP_CR || type != STR_CONST || type != ALLOC_ARRAY || type != CALL_SCANF || type != GLOBAL_CONST || type != RET_NUM){
								
			}

			if (type != SUB_CC || type != SUB_RC || type != ADD_CC || type != ADD_RC || type != CMP_CC || type != CMP_RC || type != ALLOC_ARRAY || type != CALL_SCANF || type != CALL_PRINTF || type != GEP_RC || type != GEP_RCC) {

			}
			
		}
		
		

	}
	current=current->next;
}

*/
}

void ssa_form(stmt stmnt){


}

