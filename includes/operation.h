#ifndef SAANENS_OPERATION_H
#define SAANENS_OPERATION_H

#include <variable.h>
#include <regfunc.h>
#include <stdio.h>
#include <interpret.h>
#include <cast.h>

boolean doLog(boolean op1, boolean op2, s_op);
boolean doComp(s_var *op1, s_var *op2, s_op);
boolean doIntComp(int op1, int op2, s_op);
boolean doFloatComp(double op1, double op2, s_op);
boolean doCharComp(char op1, char op2, s_op);
boolean doStringComp(char *op1, char *op2, s_op);
boolean doBoolComp(boolean op1, boolean op2, s_op);
int doIntOp(int op1, int op2, s_op);
double doFloatOp(double op1, double op2, s_op);



#endif //SAANENS_OPERATION_H