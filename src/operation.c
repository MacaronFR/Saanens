#include <operation.h>

boolean doLog(boolean op1, boolean op2 ,s_op op){
	switch (op) {
		case S_AND: return (op1 && op2)?True:False;
		case S_OR: return (op1 || op2)?True:False;
		default: return False;
	}
}

boolean doComp(s_var *op1, s_var *op2, s_op operator){
	switch (op1->type) {
		case S_ENT: return doIntComp(op1->value.ve, op2->value.ve, operator);
		case S_FLOT: return doFloatComp(op1->value.vf, op2->value.vf, operator);
		case S_CAR: return doCharComp(op1->value.vc, op2->value.vc, operator);
		case S_CHAINE: return doStringComp(op1->value.vs, op2->value.vs, operator);
		case S_BOOL: return doBoolComp(op1->value.vb, op2->value.vb, operator);
		default: return False;
	}
}

boolean doIntComp(int op1, int op2, s_op op){
	switch (op) {
		case S_EQ: return (op1 == op2)?True:False;
		case S_ABV: return (op1 > op2)?True:False;
		case S_ABE: return (op1 >= op2)?True:False;
		case S_BEL: return (op1 < op2)?True:False;
		case S_BLE: return (op1 <= op2)?True:False;
		case S_DIF: return (op1 != op2)?True:False;
		default: return False;
	}
}

boolean doFloatComp(double op1, double op2, s_op op){
	switch (op) {
		case S_EQ: return (op1 == op2)?True:False;
		case S_ABV: return (op1 > op2)?True:False;
		case S_ABE: return (op1 >= op2)?True:False;
		case S_BEL: return (op1 < op2)?True:False;
		case S_BLE: return (op1 <= op2)?True:False;
		case S_DIF: return (op1 != op2)?True:False;
		default: return False;
	}
}

boolean doCharComp(char op1, char op2, s_op op){
	switch (op) {
		case S_EQ: return (op1 == op2)?True:False;
		case S_ABV: return (op1 > op2)?True:False;
		case S_ABE: return (op1 >= op2)?True:False;
		case S_BEL: return (op1 < op2)?True:False;
		case S_BLE: return (op1 <= op2)?True:False;
		case S_DIF: return (op1 != op2)?True:False;
		default: return False;
	}
}

boolean doStringComp(char *op1, char *op2, s_op op){
	if(op1 == NULL || op2 == NULL){
		return False;
	}
	int test = strcmp(op1,op2);
	switch (op) {
		case S_EQ: return (test == 0)?True:False;
		case S_ABV: return (test > 0)?True:False;
		case S_ABE: return (test >= 0)?True:False;
		case S_BEL: return (test < 0)?True:False;
		case S_BLE: return (test <= 0)?True:False;
		case S_DIF: return (test != 0)?True:False;
		default: return False;
	}
}

boolean doBoolComp(boolean op1, boolean op2, s_op op){
	switch (op) {
		case S_EQ: return (op1 == op2)?True:False;
		case S_ABV: return (op1 > op2)?True:False;
		case S_ABE: return (op1 >= op2)?True:False;
		case S_BEL: return (op1 < op2)?True:False;
		case S_BLE: return (op1 <= op2)?True:False;
		case S_DIF: return (op1 != op2)?True:False;
		default: return False;
	}
}

int doIntOp(int op1, int op2, s_op op){
	switch (op) {
		case S_ADD: return op1 + op2;
		case S_SUB: return op1 - op2;
		case S_MDL: return op1 % op2;
		case S_MUL: return op1 * op2;
		case S_DIV: return op1 / op2;
		default: return 0;
	}
}

double doFloatOp(double op1, double op2, s_op op){
	switch (op) {
		case S_ADD: return op1 + op2;
		case S_SUB: return op1 - op2;
		case S_MUL: return op1 * op2;
		case S_DIV: return op1 / op2;
		default: return 0.;
	}
}