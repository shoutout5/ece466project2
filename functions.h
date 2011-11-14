#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "defines.h"

int process_instruction(int type, char *defined_regs, param_t *arg1, param_t *arg2, char *cmp, char **branch, char *label_name);

void generate_llvm(stmt *stmnt, FILE *fp);
int contains(char *string, char *find);
void register_promotion();
void ssa_form(stmt *stmnt, char *reg);
char* isPromtedVar(char *reg, int type);
int isReg(stmt *step, int arg);
int dead_code();


#endif
