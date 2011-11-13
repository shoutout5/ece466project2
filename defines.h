#ifndef DEFINES_H
#define DEFINES_H

#define RR (0)
#define CC (1)
#define RC (2)
#define CR (3)
#define CONST_VAL	(4)
#define REG_VAL	(5)

#define ADD_CC  1
#define ADD_CC_NSW 13
#define ADD_RR  2
#define ADD_RR_NSW 14
#define ADD_RC  3
#define ADD_RC_NSW 17
#define ADD_CR  4
#define ADD_CR_NSW 33
#define SUB_CC  6
#define SUB_CC_NSW 34
#define SUB_RR  7
#define SUB_RR_NSW 35
#define SUB_RC  8
#define SUB_RC_NSW 36
#define SUB_CR  9
#define SUB_CR_NSW 37
#define CMP_CC  0
#define CMP_RR  10
#define CMP_RC  15
#define CMP_CR  16
#define BR_UNCOND   11
#define BR_COND     12

#define STR_REG     18
#define STR_CONST   19
#define LABELL	20
#define ALLOC	21
#define LOADD	22
#define GEP_RC 23
#define GEP_RR 24
#define RETURN 25
#define GLOBAL_CONST 26
#define CALL_PRINTF 27
#define CALL_SCANF 28
#define ALLOC_ARRAY 29
#define GEP_RRC 30
#define GEP_RCC 31
#define GEP_RCR 32
#define GEP_RRR 38
#define GLOBAL_VAR 39
#define DEC_SCANF  40
#define DEC_PRINTF 41
#define FUNC_DEC 42
#define FUNC_END 43

#define RET_NUM 44
#define RET_REG 45

typedef union {
	int  imm;
	char reg[100];
} param_t;

typedef struct node{
	int type;
	char defined_regs[50];
	param_t arg1;
	param_t arg2;
	char cmp[50];
	char branch[5][100];
	char label_name[100];
	struct node *next;
} stmt;

typedef struct {
    int size;
    char type[50];
} array_def;

extern stmt *current;
extern stmt *HEAD;

#endif





