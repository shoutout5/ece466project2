#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct a {
	int type;
	char * defined_regs;
	int imm1;
	int imm2;
	char reg1[50];
	char reg2[50];
	char label_name[50];
	struct a *next;
	
} stmt;

stmt *current=NULL;

int proccess_instruction(int type, char * defined_regs, int imm1, int imm2, char *reg1, char *reg2, char *label_name){
	
	stmt *data = (stmt *) malloc(sizeof(stmt));
	data->type = type;
	data->defined_regs = defined_regs;
	data->imm1=imm1;
	data->imm2=imm2;
	strcpy(data->reg1,reg1);
	strcpy(data->reg2,reg2);
	strcpy(data->label_name,label_name);
	data->next=NULL;
	if (current != NULL)
		current->next=data;

	current=data;

	
}
