#include <operation.h>

s_var processOperation(const char *command, s_cat lev){
	char *reglog = "([^|]+)(([|]|[&]){2})(.+)";
	char *regaff = "([a-zA-Z][a-zA-Z0-9_]*)[ \t\n\r\f]*=(.+)";
	char *regcomp = "([^<]+)(==|>=|<=|<|>|<>)([^>]+)";
	char *regaddsub = "([^+-]+)([+]|-)(.+)";
	char *regmod = "([^%]+)(%)(.+)";
	char *regmuldiv = "([^/*]+)([*]|/)(.+)";
	char *regint = "^([0-9]+)$";
	char *regfloat = "^([0-9]+[.][0-9]*)|([0-9]*[.][0-9]+)$";
	char *regvar = "([a-zA-Z][a-zA-Z0-9_]*)";
	s_var res;
	if(regpresent(reglog, command) && lev <= S_LOG){
		return processLog(command);
	}else if(regpresent(regaff, command) && lev <= S_AFF){
		return processAff(command);
	}else if(regpresent(regcomp, command) && lev <= S_COMP){
		return processComp(command);
	}else if(regpresent(regaddsub, command) && lev <= S_ADSB){
		return processAddSub(command);
	}else if(regpresent(regmod, command) && lev <= S_MOD){
		return processMod(command);
	}else if(regpresent(regmuldiv, command) && lev <= S_MLDV){
		return processMulDiv(command);
	}else if(regpresent(regint, command)){
		res.type = S_ENT;
		res.value.ve = parseInt(command);
		return res;
	}else if(regpresent(regfloat, command)){
	
	}else if(regpresent(regvar, command)){
		s_var *p = resolve_var(command);
		return (p==NULL)?(s_var){S_ENT, "nill", .undefined=True}:*p;
	}
}

boolean check_parenthese(const char *l){
	if(l != NULL){
		char *reg = "[(].+[)]";
		return regpresent(reg, l);
	}
}

s_var execute_parenthese(char *l){
	if(l != NULL) {
		char *reg = "[(](.+)[)][^(]*[(]([^()]*([(].*[)])*[^()]*)[)]";
		char *command[1];
		regmatch_t *pmatch = NULL;
		if(regretrieve(reg, l, &pmatch)){
			process_pmatch(l, pmatch, 1, command);
			if(check_parenthese(l)){
				//test
			}else{
				processOperation(command[0], S_LOG);
			}
		}
	}
	return (s_var){S_NOT, "nill",.undefined = True};
}

s_var processLog(const char *c){
	char *reg = "([^|]+)(([|]|[&]){2})(.+)";
	regmatch_t *pmatch = NULL;
	if(regretrieve(reg, c, &pmatch)){
		char *info[4];
		process_pmatch(c, pmatch, 4, info);
		trim(info[0]);
		trim(info[3]);
		s_var op1 = processOperation(info[0], S_LOG);
		s_var op2 = processOperation(info[3], S_LOG);
		s_op operator = 0;
		if(strcmp(info[1], "||") == 0){
			operator = S_OR;
		}else if(strcmp(info[1], "&&") == 0){
			operator = S_AND;
		}
		s_var res = {S_BOOL, "temp", .value.vb = True};
		if(op1.type == S_ENT || op1.type == S_BOOL){
			res.value.vb = doIntOp(op1.value.ve, op2.value.ve, operator);
		}
		//printf("%d, %d op = %d and res = %d\n",op1.value.ve, op2.value.ve, operator, res.value.vb);
		return res;
	}
	return (s_var){S_NOT, "nill",.undefined = True};
}

s_var processAff(const char *c){
	char *reg = "([a-zA-Z][a-zA-Z0-9_]*)[ \t\n\r\f]*=(.+)";
	regmatch_t *pmatch = NULL;
	char *match[2];
	if(regretrieve(reg, c, &pmatch)){
		process_pmatch(c, pmatch, 2, match);
		s_var *op1 = resolve_var(match[0]);
		s_var op2 = processOperation(match[1], S_AFF);
		freematch(match, 2);
		if(op1->type == op2.type){
			if(op1->type == S_ENT){
				op1->value.ve = op2.value.ve;
			}
			return *op1;
		}
	}
}

s_var processComp(const char *c){
	char *reg = "([^<]+)(==|>=|<=|<|>|<>)([^>]+)";
	regmatch_t *pmatch = NULL;
	char *match[3];
	if(regretrieve(reg, c, &pmatch)){
		process_pmatch(c, pmatch, 3, match);
		s_op operator = 0;
		if(strcmp(match[1], "==") == 0){
			operator = S_EQ;
		}else if(strcmp(match[1], "<>") == 0){
			operator = S_DIF;
		}else if(strcmp(match[1], ">") == 0){
			operator = S_ABV;
		}else if(strcmp(match[1], ">=") == 0){
			operator = S_ABE;
		}else if(strcmp(match[1], "<") == 0){
			operator = S_BEL;
		}else if(strcmp(match[1], "<=") == 0){
			operator = S_BLE;
		}
		trim(match[0]);
		trim(match[2]);
		s_var op1 = processOperation(match[0], S_COMP);
		s_var op2 = processOperation(match[2], S_COMP);
		freematch(match,3);
		s_var res;
		res.type = S_BOOL;
		if(op1.type == S_ENT || op2.type == S_BOOL) {
			res.value.vb = doIntOp(op1.value.ve, op2.value.ve, operator);
		}
		slog("%d, %d op = %d and res = %d\n",op1.value.ve, op2.value.ve, operator, res.value.vb);
		return res;
	}
	return (s_var){S_NOT, "nill",.undefined = True};
}

s_var processAddSub(const char *c){
	char *reg = "(.+)([+]|-)(.+)";
	regmatch_t *pmatch = NULL;
	char *match[3];
	if(regretrieve(reg, c, &pmatch)){
		process_pmatch(c, pmatch, 3, match);
		trim(match[0]);
		trim(match[1]);
		trim(match[2]);
		s_op operator = 0;
		if(strcmp(match[1], "+") == 0){
			operator = S_ADD;
		}else if(strcmp(match[1], "-") == 0){
			operator = S_SUB;
		}
		s_var op1 = processOperation(match[0], S_ADSB);
		s_var op2 = processOperation(match[2], S_ADSB);
		freematch(match, 3);
		s_var res = {.undefined = False, .type = S_ENT};
		if(op1.type == S_ENT || op1.type == S_BOOL) {
			res.value.ve = doIntOp(op1.value.ve, op2.value.ve, operator);
		}
		slog("%d, %d op = %d and res = %d\n", op1.value.ve, op2.value.ve, operator, res.value.vb);
		return res;
	}
	return (s_var){S_NOT, "nill",.undefined = True};
}

s_var processMod(const char *c){
	char *reg = "([^%]+)(%)(.+)";
	regmatch_t *pmatch = NULL;
	char *match[3];
	if(regretrieve(reg, c, &pmatch)){
		process_pmatch(c, pmatch, 3, match);
		trim(match[0]);
		trim(match[1]);
		trim(match[2]);
		s_var op1 = processOperation(match[0], S_MOD);
		s_var op2 = processOperation(match[2], S_MOD);
		freematch(match, 3);
		s_var res;
		if(op1.type == S_ENT){
			res.type = S_ENT;
			res.value.ve = doIntOp(op1.value.ve,op2.value.ve,S_MDL);
		}
		slog("%d, %d op = %d and res = %d\n", op1.value.ve, op2.value.ve, S_MDL, res.value.ve);
		return res;
	}
}

s_var processMulDiv(const char *c){
	char *reg = "([^/*]+)([*]|/)(.+)";
	regmatch_t *pmatch = NULL;
	char *match[3];
	if(regretrieve(reg, c, &pmatch)){
		process_pmatch(c, pmatch, 3, match);
		trim(match[0]);
		trim(match[1]);
		trim(match[2]);
		s_var op1 = processOperation(match[0],S_MLDV);
		s_var op2 = processOperation(match[2],S_MLDV);
		s_op operator = 0;
		if(strcmp(match[1], "/") == 0){
			operator = S_DIV;
		}else if(strcmp(match[1], "*") == 0){
			operator = S_MUL;
		}
		freematch(match, 3);
		s_var res;
		if(op1.type == S_ENT){
			res.type = S_ENT;
			res.value.ve = doIntOp(op1.value.ve, op2.value.ve, operator);
		}
		return res;
	}
}

s_var *resolve_var(const char *c){
	char *var = malloc(strlen(c)+1);
	strcpy(var, c);
	trim(var);
	return get_var(var, strlen(var));
}

int doIntOp(int op1, int op2, s_op op){
	slog("op 1 = %d, op 2 = %d, operator = %d op1%%op2 = %d\n",op1,op2,op,op1%op2);
	switch (op) {
		case S_OR: return (op1 || op2)?True:False;
		case S_AND: return (op1 && op2)?True:False;
		case S_EQ: return (op1 == op2)?True:False;
		case S_ABV: return (op1 > op2)?True:False;
		case S_ABE: return (op1 >= op2)?True:False;
		case S_BEL: return (op1 < op2)?True:False;
		case S_BLE: return (op1 <= op2)?True:False;
		case S_DIF: return (op1 != op2)?True:False;
		case S_ADD: return op1 + op2;
		case S_SUB: return op1 - op2;
		case S_MDL: return op1 % op2;
		case S_MUL: return op1 * op2;
		case S_DIV: return op1 / op2;
		default: return 0;
	}
}

int parseInt(const char *n){
	slog("str = %s. int = %d\n",n, atoi(n));
	return atoi(n);
}