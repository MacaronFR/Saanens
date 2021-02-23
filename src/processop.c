#include <processop.h>

boolean check_parenthese(const char *l){
	if(l != NULL){
		char *reg = "[(].+[)]";
		return regpresent(reg, l);
	}
	return False;
}

char *execute_parenthese(const char *l){
	s_var resparenthese;
	const char *substr;
	char *resstr, *nl;
	int nlen;
	if(l != NULL) {
		char *command[1];
		if(regparenthesis(l, command)){
			trim(command[0]);
			resparenthese = processOperation(command[0], S_LOG);
			substr = NULL;
			for(int i = 0; i < strlen(l); ++i){
				if(l[i] == '('){
					substr = l+i+1;
					break;
				}
			}
			resstr = varToString(resparenthese);
			nlen = strlen(l) - strlen(command[0]) - 2 +strlen(resstr);
			nl = malloc(nlen);
			strncpy(nl,l,substr - l - 1);
			strcpy(nl + (substr - l - 1), resstr);
			strcpy(nl+(substr-l-1) + strlen(resstr), substr + strlen(command[0]) + 1);
			freematch(command, 1);
			free(resstr);
			return nl;
		}
		return NULL;
	}
	return NULL;
}

s_var processLog(const char *c){
	char *reg = "([^|]+)([|&]{2})(.+)";
	regmatch_t *pmatch = NULL;
	s_op operator = 0;
	s_var op1, op2;
	s_var res = {.undefined = True, .type = S_BOOL};
	if(regretrieve(reg, c, &pmatch)){
		char *info[3];
		process_pmatch(c, pmatch, 4, info);
		trim(info[0]);
		trim(info[1]);
		trim(info[2]);
		op1 = processOperation(info[0], S_LOG);
		op2 = processOperation(info[2], S_LOG);
		freematch(info, 3);
		if (op1.undefined || op2.undefined){
			returnNillVar;
		}
		if(strcmp(info[1], "||") == 0){
			operator = S_OR;
		}else if(strcmp(info[1], "&&") == 0){
			operator = S_AND;
		}
		if(operator != 0) {
			res.undefined = False;
			cast(&op1, S_BOOL);
			cast(&op2, S_BOOL);
			res.value.vb = doLog(op1.value.vb, op2.value.vb, operator);
			return res;
		}
	}
	returnNillVar;
}

s_var processAff(const char *c){
	char *reg = "([a-zA-Z][a-zA-Z0-9_]*)[ \t\n\r\f]*=(.+)";
	regmatch_t *pmatch = NULL;
	char *match[2];
	s_var *op1, op2;
	if(regretrieve(reg, c, &pmatch)){
		process_pmatch(c, pmatch, 2, match);
		trim(match[0]);
		trim(match[1]);
		op1 = resolve_var(match[0]);
		if (op1 == NULL){
			freematch(match, 2);
			returnNillVar;
		}
		op2 = processOperation(match[1], S_AFF);
		freematch(match, 2);
		if(op2.undefined){
			returnNillVar;
		}
		if(op2.type != op1->type){
			cast(&op2, op1->type);
		}
		if(assign_value(op1, op2.value)){
			return *op1;
		}
	}
	returnNillVar;
}

s_var processComp(const char *c){
	char *reg = "([^<]+)(==|>=|<=|<|>|<>)([^>]+)";
	regmatch_t *pmatch = NULL;
	char *match[3];
	s_op operator;
	s_var op1, op2;
	if(regretrieve(reg, c, &pmatch)){
		process_pmatch(c, pmatch, 3, match);
		trim(match[0]);
		trim(match[1]);
		trim(match[2]);
		operator = 0;
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
		op1 = processOperation(match[0], S_COMP);
		op2 = processOperation(match[2], S_COMP);
		freematch(match,3);
		if (op1.undefined || op2.undefined){
			returnNillVar;
		}
		s_var res;
		res.type = S_BOOL;
		res.undefined = True;
		if((op1.type == S_CHAINE || op2.type == S_CHAINE) && op1.type != op2.type){
			cast(&op2, S_CHAINE);
			cast(&op1, S_CHAINE);
		}else if(op1.type != op2.type){
			cast(&op1, S_ENT);
			cast(&op2, S_ENT);
		}
		res.value.vb = doComp(&op1, &op2, operator);
		res.undefined = False;
		return res;
	}
	returnNillVar;
}

s_var processAddSub(const char *c){
	char *reg = "(.+)([+-])(.+)";
	regmatch_t *pmatch = NULL;
	char *match[3];
	s_var res;
	s_var op1;
	s_var op2;
	s_op operator = 0;
	char *resstr;
	if(regretrieve(reg, c, &pmatch)){
		process_pmatch(c, pmatch, 3, match);
		trim(match[0]);
		trim(match[1]);
		trim(match[2]);
		if(strcmp(match[1], "+") == 0){
			operator = S_ADD;
		}else if(strcmp(match[1], "-") == 0){
			operator = S_SUB;
		}
		op1 = processOperation(match[0], S_ADSB);
		op2 = processOperation(match[2], S_ADSB);
		freematch(match, 3);
		if(op1.undefined || op2.undefined){
			returnNillVar;
		}
		if((op1.type == S_CHAINE || op2.type == S_CHAINE) && operator == S_ADD){
			cast(&op1, S_CHAINE);
			cast(&op2, S_CHAINE);
			resstr = malloc(sizeof(op1.value.vs) + sizeof(op2.value.vs) + 1);
			strcpy(resstr, op1.value.vs);
			strcat(resstr, op2.value.vs);
			res.undefined = False;
			res.type = S_CHAINE;
			res.value.vs = resstr;
		}else if((op1.type == S_CAR && op2.type == S_ENT) || (op2.type == S_CAR && op1.type == S_ENT)){
			cast(&op1, S_CAR);
			cast(&op2, S_CAR);
			res.undefined = False;
			res.type = S_CAR;
			doIntOp((int)op1.value.vc, (int)op2.value.vc, operator);
		}else if(op1.type == S_FLOT || op2.type == S_FLOT){
			cast(&op1, S_FLOT);
			cast(&op2, S_FLOT);
			res.undefined = False;
			res.type = S_FLOT;
			res.value.vf = doFloatOp(op1.value.vf, op1.value.vf, operator);
		}else if(op1.type == S_BOOL || op1.type == S_ENT || op2.type == S_BOOL || op2.type == S_ENT){
			res.type = S_ENT;
			cast(&op1, S_ENT);
			cast(&op2, S_ENT);
			res.value.ve = doIntOp(op1.value.ve, op2.value.ve, operator);
		}else{
			returnNillVar;
		}
		return res;
	}
	returnNillVar;
}

s_var processMod(const char *c){
	char *reg = "([^%]+)(%)(.+)";
	regmatch_t *pmatch = NULL;
	char *match[3];
	s_var res;
	s_var op1;
	s_var op2;
	if(regretrieve(reg, c, &pmatch)){
		process_pmatch(c, pmatch, 3, match);
		trim(match[0]);
		trim(match[1]);
		trim(match[2]);
		op1 = processOperation(match[0], S_MOD);
		op2 = processOperation(match[2], S_MOD);
		freematch(match, 3);
		if (op1.undefined || op2.undefined){
			returnNillVar;
		}
		if(op1.type == S_ENT && op2.type == S_ENT){
			if(op1.value.ve == 0 && op2.value.ve == 0){
				returnNillVar;
			}
			res.type = S_ENT;
			res.undefined = False;
			res.value.ve = doIntOp(op1.value.ve,op2.value.ve,S_MDL);
			return res;
		}
		returnNillVar;
	}
	returnNillVar;
}

s_var processMulDiv(const char *c){
	char *reg = "([^/*]+)([*]|/)(.+)";
	regmatch_t *pmatch = NULL;
	char *match[3];
	s_var res, op1, op2;
	s_op operator;
	if(regretrieve(reg, c, &pmatch)){
		process_pmatch(c, pmatch, 3, match);
		trim(match[0]);
		trim(match[1]);
		trim(match[2]);
		op1 = processOperation(match[0],S_MLDV);
		op2 = processOperation(match[2],S_MLDV);
		if(strcmp(match[1], "/") == 0){
			operator = S_DIV;
		}else if(strcmp(match[1], "*") == 0){
			operator = S_MUL;
		}
		freematch(match, 3);
		if (op1.undefined || op2.undefined){
			returnNillVar;
		}
		if(op1.type == S_FLOT || op2.type == S_FLOT){
			res.type = S_FLOT;
			res.undefined = False;
			cast(&op1, S_FLOT);
			cast(&op2, S_FLOT);
			res.value.vf = doFloatOp(op1.value.vf, op2.value.vf, operator);
		}else if(op1.type == S_ENT || op2.type == S_ENT || op1.type == S_BOOL || op2.type == S_BOOL){
			cast(&op1, S_ENT);
			cast(&op2, S_ENT);
			res.type = S_ENT;
			res.undefined = False;
			res.value.ve = doIntOp(op1.value.ve, op2.value.ve, operator);
		}else{
			returnNillVar;
		}
		return res;
	}
	returnNillVar;
}

s_var *resolve_var(const char *c){
	char *var = malloc(strlen(c)+1);
	strcpy(var, c);
	trim(var);
	s_var *p = get_var(var, strlen(var));
	if(p == NULL){
		slog("Error no variable named %s\n",var);
	}
	return p;
}