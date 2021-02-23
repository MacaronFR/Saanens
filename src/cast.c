#include <cast.h>

boolean cast(s_var *v, type t){
	switch (t) {
		case S_ENT: return castInt(v);
		case S_FLOT: return castFloat(v);
		case S_CAR: return castChar(v);
		case S_CHAINE: return castString(v);
		case S_BOOL: return castBool(v);
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