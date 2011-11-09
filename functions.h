#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "defines.h"

int process_instruction(int type, char *defined_regs, param_t arg1, param_t arg2, char *cmp, char **branch, char *label_name);

#endif
