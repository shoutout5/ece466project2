#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "project2.y.h"
#include "functions.h"

#define MORE_TO_DO 1
#define DONE 0

extern char type_arr[6][100];

char pass[100];

char repNames[200][50];
char names[200][50];
int version[200];
int count=0;

int process_instruction(int type, char *defined_regs, param_t *arg1, param_t *arg2, char *cmp, char **branch, char *label_name){
    int i;
    
    //printf("starting\n");
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
		if (type == BR_COND) {
            strcpy(data->branch[i],branch[i]);
            if (i == 3)
                break;
        }
        else {
            if(type_arr[i] != NULL)
            {
                //printf("%d %s\n", i, type_arr[i]);
                strcpy(data->branch[i],type_arr[i]);
            }
        }
    }
    
	data->next=NULL;
	if (current != NULL)
		current->next=data;
	if (HEAD == NULL)
		HEAD=data;
	current=data;
	//printf("finished\n");
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
			sprintf(output,"  br i1 %s, label %s, label %s\n",stmnt->branch[0],stmnt->branch[1],stmnt->branch[2]);
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
	stmt *cur;
	char *newName;
	int i;
    
	for(i=0;i<200;i++)
		version[i]=0;
    
	stmt *temp;
	stmt *prev;
    
	cur = HEAD;
    
	//scan for vaiable to promote
	while(cur != NULL) {
		if( cur->type == ALLOC || cur->type == GLOBAL_VAR ) {
 			strcpy(names[count++],cur->defined_regs);
		}
		cur=cur->next;
	}
    
    
	// scan for passing var addresses to function call
	cur = HEAD;
	while(cur != NULL)
	{
		if(cur->type == CALL_SCANF)
		{
			for(i=0; i<count; i++)
			{
				if(contains(cur->label_name, names[i]))
					strcpy(names[i],"NOT A VAR");
			}
		}
		cur=cur->next;
	}
    
	// replace variables with register
	for(i=0;i<count;i++)
	{
		if(!strcmp(names[i],"NOT A VAR"))
			continue;
        
		cur = HEAD;
		prev = NULL;
		while(cur != NULL)
		{
			if(((cur->type == ALLOC) || (cur->type == GLOBAL_VAR)) && (!strcmp(cur->defined_regs, names[i])))
			{
				if(prev != NULL)
					prev->next = cur->next;
				else
					HEAD = cur->next;
                
				free(cur);
                
				sprintf(repNames[i], "%%rep_%s", &names[i][1]);	//generate new reg name
				break;
			}
			prev = cur;
			cur = cur->next;
		}
	}
    
	// replace loads and stores of used variables
	cur = HEAD;
	while(cur != NULL)
	{
		if(cur->type == LOADD)
		{
			newName = isPromtedVar(cur->arg1.reg, LOADD);
			if(newName != NULL)
			{
				strcpy(cur->branch[0],"i32");
				strcpy(cur->arg1.reg, newName);
				cur->arg2.imm = 0;
				cur->type = ADD_RC;
			}			
		}
		else if(cur->type == STR_REG)
		{
			newName = isPromtedVar(cur->defined_regs, STR_REG);
			if(newName != NULL)
			{
				char temp[50];
				strcpy(temp,cur->defined_regs);
				strcpy(cur->defined_regs, newName);
				//strcpy(cur->arg1.reg, temp);
				cur->arg2.imm = 0;
				cur->type = ADD_RC;
			}
		}
		else if(cur->type == STR_CONST)
		{
			newName = isPromtedVar(cur->defined_regs, STR_CONST);
			if(newName != NULL)
			{
				strcpy(cur->defined_regs, newName);
				cur->arg2.imm = 0;
				cur->type = ADD_CC;
			}
		}	
		
		cur=cur->next;
	}
}

char* isPromtedVar(char *reg, int type)
{
	int i;
	for(i=0;i<count;i++)
	{
		if(!strcmp(reg, names[i]))
		{
			if(type != LOADD)
				version[i]++;
            
			sprintf(pass, "%s_%d", repNames[i], version[i]);
			return pass;
		}
	}
	return NULL;
}


int contains(char *string, char *find)
{
	int i;
	if(!strcmp(find,"NOT A VAR"))
		return 0;
    
	for(i=0;i<=(strlen(string)-strlen(find));i++)
	{
		if(!strncmp(find,&string[i],strlen(find)))
		{
			if(((i+strlen(find) == strlen(string)) || (string[i+strlen(find)] == ' ') || (string[i+strlen(find)] == ',')))
			{
				return 1;
			}
		}
	}
	return 0;
}

int dead_code(){
    stmt *curr=HEAD;
    stmt *step=HEAD;
    stmt *prev=NULL;
    char returnSSA[50];
    int used=0;
    //iterate until we reach the end of the linked list
    while(curr != NULL) {	
        
        if( curr->defined_regs != NULL && strcmp(curr->defined_regs,"") ) {//as long as defined_regs is readable
            //printf("found type %d \n",curr->type);
            if(curr->type == GLOBAL_CONST || curr->type == FUNC_DEC || curr->type == CALL_PRINTF || curr->type == CALL_SCANF){  //if the type isn't part of the DC elimination,
                prev=curr;						//skip it
                curr=curr->next;
                continue;	
                
            } else {
                printf("defd found: %s\n",curr->defined_regs);
                step=curr;
                //run through the file from the current point and see if there are any uses of defined_regs
                while(step != NULL){
                    //printf("type: %d\n",step->type);
                    //if the type is not something we care about, move to the next item
                    if (step->type == GLOBAL_CONST || step->type == FUNC_DEC || step->type == LABELL || step->type == LABEL ) { 
                        step=step->next;
                        continue;
                    }
                    
                    //since the type is now something we care about we make sure that the value in arg1 is a register
                    if (step->type != SUB_CC || step->type != SUB_CR || step->type != ADD_CC || step->type != ADD_CR || step->type != CMP_CC || step->type != CMP_CR || step->type != ALLOC_ARRAY || step->type != CALL_PRINTF || step->type != ADD_CR || step->type != CMP_CC || step->type != CMP_CR || step->type != STR_CONST || step->type != ALLOC_ARRAY || step->type != CALL_SCANF || step->type != GLOBAL_CONST || step->type != RET_NUM){
                        //now that we're sure it's a register check to see if it is used
                        if (!strcmp(step->arg1.reg,curr->defined_regs) && strcmp(step->arg1.reg,"") && strcmp(step->arg1.reg,"\n")) {
                            printf("use found1: '%s'\n",step->arg1.reg);
                            used++;
                        }
                    }
                    //since the type is now something we care about we make sure that the value in arg2 is a register
                    if (step->type != SUB_CC || step->type != SUB_RC || step->type != ADD_CC || step->type != ADD_RC || step->type != CMP_CC || step->type != CMP_RC || step->type != ALLOC_ARRAY || step->type != CALL_SCANF || step->type != CALL_PRINTF || step->type != GEP_RC || step->type != GEP_RCC ) {
                        //now that we're sure it's a register check to see if it is used
                        if (!strcmp(step->arg2.reg,curr->defined_regs) && strcmp(step->arg2.reg,"") && strcmp(step->arg2.reg,"\n")) {
                            printf("use found2: %s\n",step->arg2.reg);
                            used++;
                        }
                    }
                    if (step->type == CALL_PRINTF || step->type == CALL_SCANF){
                        int i=0;
                        int j;
                        char *begin, *end;
                        char regIn[50];	
                        char printscan[20][50];
                        char printscan1[20][50];
                        char temp[50];
                        begin = step->label_name;
                        char * val1, val2;
                        char original[100]; 
                        strcpy(original, step->label_name);	
                        //	printf("or: %s\n",original);
                        val1 = strtok(original, " ,");
                        //	printf("or: %s\n",original);
                        while(val1 != NULL) {
                            strcpy(printscan[i], val1);
                            //		printf("%s\n",printscan[i]);
                            i++;
                            val1 = strtok(NULL, " ,");
                        }
                        for(j=1;j<=i;j=j+2){
                            sprintf(temp,"%s",printscan[j]);
                            //printf("tmp: %s\n",temp);
                            if(!strcmp(temp,curr->defined_regs)){
                                printf("found %s\n",temp);	
                                used++;	
                            }
                        }
                        
                    }
                    //if the register is used break out of the while loop
                    if (used > 0){
                        break;
                    }
                    else { //otherwise continue searching
                        step=step->next;
                    }
                }
                //we're now done checking for this register
            } 
            //		printf("used: %d\n",used);	
            //now we see if it is ever used
            if(used == 0) {
                
                //			printf("none used for '%s'",curr->defined_regs); 
                strcpy(returnSSA,curr->defined_regs);		
                //if never used delete the node in the linked list
                if(curr->next != NULL && curr != HEAD) { //check to see if we are at the end or beginning of list	
                    prev->next=curr->next;
                    free(curr);
                    curr=prev->next;
                } else if(curr == HEAD) {
                    HEAD=curr->next;
                    prev=NULL;
                    free(curr);
                }	
                else { //if we are at the end of the list
                    prev->next=NULL;
                    free(curr);
                    curr=prev->next;
                }
                break;
                
            } else { //if the register is used move on
                prev=curr;	
                curr=curr->next;
                used=0;
            }
        } else {
            prev=curr;                                              //skip it
            curr=curr->next;
            continue;
        }	
    }
    ssa_form(curr,returnSSA);
    //if we quit because we found a match tell the user to run again
    if(used==0)
        return MORE_TO_DO;
    else //otherwise tell the user we're done with analysis.
        return DONE;
}



//}

void ssa_form(stmt *stmnt, char *reg)
{
	int ref;
	int currentReg;
	stmt *curr = stmnt;
	
	char *begin;
	char *end;
	char regIn[50];
	char argsOut[100] = "";
	
	//printf("REG: %s\n", reg);
	
	if(stmnt == NULL)		//no new statments to rename
	{
		//printf("NULL REturn\n");
		return;
	}
    
	ref = atoi(&reg[1]);
	if(ref == 0)		//removed a variable or something not a register
	{
		//printf("No NUm Return\n");
		return;
	}
    
	while(curr != NULL)
	{
		if(isReg(curr, 1))
		{
			currentReg = atoi(&curr->arg1.reg[1]);
			if((currentReg != 0) && (currentReg > ref))
			{
				sprintf(curr->arg1.reg, "%%%d", (currentReg-1));
				//printf("Reg Deced %d\n", (currentReg-1));
			}
		}
		if(isReg(curr, 2))
		{
			currentReg = atoi(&curr->arg2.reg[1]);
			if((currentReg != 0) && (currentReg > ref))
			{
				sprintf(curr->arg2.reg, "%%%d", (currentReg-1));
				//printf("Reg Deced %d\n", (currentReg-1));
			}
		}
        
		currentReg = atoi(&curr->defined_regs[1]);
		if((currentReg != 0) && (currentReg > ref))
		{
			sprintf(curr->defined_regs, "%%%d", (currentReg-1));
			//printf("Reg Deced %d\n", (currentReg-1));
		}
        
		if((curr->type == CALL_SCANF) || (curr->type == CALL_PRINTF))
		{			
			begin = curr->label_name;
			while(begin != NULL)
			{
				end = strchr(begin, '%');
				if(end == NULL) break;
                
				strncat(argsOut, begin, (end-begin-1));
                
				begin = end+1;
				end = strchr(begin, ' ');
				if(end == NULL)
					end = begin + strlen(begin);
                
				strncpy(regIn, begin, (end-begin));
                
				currentReg = atoi(regIn);
				if(currentReg > ref)
					sprintf(argsOut, "%s %%%d", argsOut, (currentReg-1));
				else
					sprintf(argsOut, "%s %%%d", argsOut, currentReg);
                
				begin = strchr(begin, ',');
				if(begin == NULL)
					break;
				else 
				{
					begin += 2;
					strcat(argsOut, ", ");
				}
			}
            
			sprintf(curr->label_name, "%s", argsOut);
		}
        
		curr = curr->next;
	}
}

int isReg(stmt *step, int arg)
{
	if (step->type != SUB_CC || step->type != SUB_CR || step->type != ADD_CC || step->type != ADD_CR || step->type != CMP_CC || step->type != CMP_CR || step->type != ALLOC_ARRAY || step->type != CALL_PRINTF || step->type != ADD_CR || step->type != CMP_CC || step->type != CMP_CR || step->type != STR_CONST || step->type != ALLOC_ARRAY || step->type != CALL_SCANF || step->type != GLOBAL_CONST || step->type != RET_NUM){
		//now that we're sure it's a register check to see if it is used
		if (strcmp(step->arg1.reg,"") && strcmp(step->arg1.reg,"\n")) {
            
			if(arg==1)
				return 1;
		}
	}
	//since the type is now something we care about we make sure that the value in arg2 is a register
	if (step->type != SUB_CC || step->type != SUB_RC || step->type != ADD_CC || step->type != ADD_RC || step->type != CMP_CC || step->type != CMP_RC || step->type != ALLOC_ARRAY || step->type != CALL_SCANF || step->type != CALL_PRINTF || step->type != GEP_RC || step->type != GEP_RCC ) {
		//now that we're sure it's a register check to see if it is used
		if (strcmp(step->arg2.reg,"") && strcmp(step->arg1.reg,"\n")) {
            
			if(arg==2)
				return 1;
		}
	}
	return 0;
}

block *generate_cfg() 
{    
    int i = -1;
    int j = 0;
    int k = -1;
    int q = 0;
    stmt *line = HEAD;
    block *label_list[20];
    block *present;
    
    while (line->type != FUNC_DEC)
        line=line->next;
    
    while (q != 1) 
    {
        label_list[++i] = (block *) malloc(sizeof(block));
        present = label_list[i];
        strcpy(present->preds,"; preds =");
        
        while (q != 1) 
        {
            present->instruction = line;
            present->right = NULL;
            
            if (line->next != NULL)
            {
                present->left = (block *) malloc(sizeof(block));
                strcpy(present->left->preds,"");
                line = line->next;
                present = present->left;
            }
            else
                q = 1;
            
            if (line->type == LABELL)
            {
                present->left = NULL;
                present->right = NULL;
                break;
            }
        }
    }
    
    while (k < i) 
    {
        present = label_list[++k];
        j = 0;
        
        while (present->instruction->type != BR_COND && present->instruction->type != BR_UNCOND)
        {
            present=present->left;
            
            if (present->instruction->type == RET_NUM)
            {
                break;
            }
        }
        
        if (present->instruction->type == BR_UNCOND)
        {
            while (strcmp(strtok(label_list[j]->instruction->label_name," "), &present->instruction->label_name[1]) != 0)
            {
                j++;
            }
            
            present->left = label_list[j];
            
            if (strcmp(present->left->preds, "; preds =") != 0)
                strcat(present->left->preds,",");
            
            strcat(present->left->preds," \%");
            if (strcmp(strtok(label_list[k]->instruction->label_name," "), "define") == 0)
                strcat(present->left->preds, "0");  
            else
                strcat(present->left->preds, strtok(label_list[k]->instruction->label_name," "));
        }
        else if (present->instruction->type == BR_COND)
        {
            while (strcmp(strtok(label_list[j]->instruction->label_name," "), &present->instruction->branch[1][1]) != 0)
            {
                j++;
            }
            
            present->left = label_list[j];
            
            if (strcmp(present->left->preds, "; preds =") != 0)
                strcat(present->left->preds,",");
            
            strcat(present->left->preds," \%");
            if (strcmp(strtok(label_list[k]->instruction->label_name," "), "define") == 0)
                strcat(present->left->preds, "0");  
            else
                strcat(present->left->preds, strtok(label_list[k]->instruction->label_name," "));
            
            j = 0;
            while (strcmp(strtok(label_list[j]->instruction->label_name," "), &present->instruction->branch[2][1]) != 0)
            {
                j++;
            }
            
            present->right = label_list[j];
            
            if (strcmp(present->left->preds, "; preds =") != 0)
                strcat(present->left->preds,",");
            
            strcat(present->right->preds," \%");
            if (strcmp(strtok(label_list[k]->instruction->label_name," "), "define") == 0)
                strcat(present->right->preds, "0");  
            else
                strcat(present->right->preds, strtok(label_list[k]->instruction->label_name," "));
        }
        else    // RETURN STATEMENT
            break;
    }
    
    present = label_list[0];
    
    sprintf(label_list[0]->preds,"%s","");
    
    /*for (i = 0; i<= 11; i++)
     {
     printf("%d, %s\n", label_list[i]->instruction->type, label_list[i]->preds);
     }*/
    
    return present;
}
