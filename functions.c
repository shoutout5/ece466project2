#include <stdio.h>

typedef struct {
    stmt *next;
    char *defined;
    char *used[2];
    int type;
} stmt;

