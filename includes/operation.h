#ifndef SAANENS_OPERATION_H
#define SAANENS_OPERATION_H

#include <variable.h>
#include <regfunc.h>
#include <stdio.h>
#include <interpret.h>
#define returnNillVar return (s_var){S_NOT, "nill",.undefined = True};


typedef enum s_cat {S_LOG = 1, S_AFF = 2, S_COMP = 4, S_ADSB = 8, S_MOD = 16, S_MLDV = 32} s_cat;
typedef enum s_op {S_AND = 1, S_OR = 2, S_NO = 3, S_XOR = 4, S_EQ = 5, S_BEL = 6, S_BLE = 7, S_ABV = 8, S_ABE = 9, S_DIF = 10, S_ADD = 11, S_SUB = 12, S_MDL = 13, S_MUL = 14, S_DIV = 15} s_op;

boolean check_parenthese(const char *line);
s_var execute_parenthese(char *line);
s_var processOperation(const char *op, s_cat level);
s_var processLog(const char *command);
s_var processAff(const char *command);
s_var processComp(const char *command);
s_var processAddSub(const char *command);
s_var processMod(const char *command);
s_var processMulDiv(const char *command);
s_var *resolve_var(const char *command);
int doIntOp(int op1, int op2, s_op);
int parseInt(const char *number);

#endif //SAANENS_OPERATION_H