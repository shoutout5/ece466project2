#ifndef DEFINES_H
#define DEFINES_H

#define ADD_CC  1
#define ADD_RR  2
#define ADD_RC  3
#define ADD_CR  4
#define SUB_CC  6
#define SUB_RR  7
#define SUB_RC  8
#define SUB_CR  9
#define CMP_CC  0
#define CMP_RR  10
#define CMP_RC  15
#define CMP_CR  16
#define BR_UNCOND   11
#define BR_COND     12
#define RR (0)
#define CC (1)
#define RC (2)
#define CR (3)
#define STR_REG     18
#define STR_CONST   19

typedef union {
	int  imm;
	char reg[50];
} param_t;

typedef struct {
	int type;
	char * defined_regs;
	param_t arg1;
	param_t arg2;
	int cmp;
	char *branch[3];
	char label_name[50];
	struct a *next;
} stmt;

#endif



