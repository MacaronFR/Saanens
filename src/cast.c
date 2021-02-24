#include <cast.h>

boolean castVar(s_var *variable, type type_to_cast){
	switch (type_to_cast) {
		case S_ENT: return castInt(variable);
		case S_FLOT: return castFloat(variable);
		case S_CAR: return castChar(variable);
		case S_CHAINE: return castString(variable);
		case S_BOOL: return castBool(variable);
		default: return False;
	}
}

boolean castString(s_var *v){
	char format[5];
	char input[100];
	switch (v->type){
		case S_ENT: strcpy(format, "%d");sprintf(input, format, v->value.ve);
			break;
		case S_FLOT: strcpy(format, "%lf");sprintf(input, format, v->value.vf);break;
		case S_BOOL: strcpy(format, "%hhd");sprintf(input, format, v->value.vb);break;
		case S_CAR: strcpy(format, "%c");sprintf(input, format, v->value.vc);break;
		case S_CHAINE: return True;
		default: return False;
	}
	v->value.vs = malloc(strlen(input) + 1);
	strcpy(v->value.vs, input);
	return True;
}

boolean castInt(s_var *v){
	switch(v->type){
		case S_ENT: return True;
		case S_FLOT: v->type = S_ENT;v->value.ve = (int)v->value.vf;break;
		case S_CAR: v->type = S_ENT;v->value.ve = (int)v->value.vc != 0;break;
		case S_BOOL: v->type = S_ENT;v->value.ve = (int)v->value.vb;break;
		case S_CHAINE: v->type = S_ENT;v->value.ve = (v->value.vs == NULL)?0:parseInt(v->value.vs);break;
		default: return False;
	}
	return True;
}

boolean castFloat(s_var *v){
	switch(v->type){
		case S_ENT: v->type = S_FLOT;v->value.vf = (double)v->value.ve;break;
		case S_FLOT: return True;
		case S_CAR: v->type = S_FLOT;v->value.vf = (double)v->value.vc != 0;break;
		case S_BOOL: v->type = S_FLOT;v->value.vf = (double)v->value.vb;break;
		case S_CHAINE: v->type = S_FLOT;v->value.vf = (v->value.vs == NULL)?0.:parseFloat(v->value.vs);break;
		default: return False;
	}
	return True;
}

boolean castChar(s_var *v){
	switch(v->type){
		case S_ENT: v->type = S_CAR;v->value.vc = (char)v->value.ve;break;
		case S_FLOT: v->type = S_CAR;v->value.vc = (char)v->value.vf;break;
		case S_CAR: return True;
		case S_BOOL: v->type = S_CAR;v->value.vc = v->value.vb?'T':'F';break;
		case S_CHAINE: v->type = S_CAR;v->value.vc = (v->value.vs == NULL)?'\0':v->value.vs[0];break;
		default: return False;
	}
	return True;
}

boolean castBool(s_var *v){
	switch(v->type){
		case S_ENT: v->type = S_BOOL;v->value.ve = (v->value.ve != 0)?True:False;break;
		case S_FLOT: v->type = S_BOOL;v->value.vf = (v->value.vf != 0.)?True:False;break;
		case S_CAR: v->type = S_BOOL;v->value.vc = (v->value.vc != 0)?True:False;break;
		case S_BOOL: return True;
		case S_CHAINE: v->type = S_BOOL;v->value.vb = (v->value.vs == NULL || strcmp(v->value.vs, "") == 0)?True:False;break;
		default: return False;
	}
	return True;
}

char *cast(char *input){
	char *regcast = "(int|float|char|string|bool)";
	char *tmp;
	regmatch_t *pmatch = NULL;
	char *arg[2];
	int *se = malloc(sizeof(int) * 2);
	type t;
	regretrieve(regcast, input, &pmatch);
	regparenthesis(input, arg+1, &se);
	se[0] = pmatch[0].rm_so;
	process_pmatch(input, pmatch, 1, arg);
	t = get_type_from_name(arg[0], strlen(arg[0]));
	s_var res = processOperation(arg[1], 0);
	freematch(arg, 2);
	castVar(&res, t);
	char *resstr = varToString(res);
	tmp = replace_in_string(input, resstr, se[0], se[1]+1);
	free(input);
	input = tmp;
	return input;
}