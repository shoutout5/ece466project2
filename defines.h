#define ADD
#define SUB
#define CMP
#define BRANCH_UNCOND

typedef union {
	int  imm;
	char reg[50];
} param_t;

typedef struct a {
	int type;
	char * defined_regs;
	param_t arg1;
	param_t arg2;
	int cmp;
	char *branch[3];
	char label_name[50];
	struct a *next;
	
} stmt;


