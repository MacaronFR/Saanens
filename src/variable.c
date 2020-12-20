#include <variable.h>

s_vars vartab;

boolean new_var(void *value, const char *name, size_t name_size, type t){
	s_var *new_vars = malloc(sizeof(s_var) * (vartab.length+1));
	s_var new_var;
	new_var.name = malloc(name_size+1);
	for(uint64_t i = 0; i < name_size; ++i){
		new_var.name[i] = name[i];
	}
	new_var.name[name_size] = '\0';
	new_var.type = t;
	for(uint64_t i = 0; i < vartab.length; ++i){
		new_vars[i] = vartab.vars[i];
	}
	new_vars[vartab.length] = new_var;
	printf("*%d*\n",vartab.length);
	vartab.length++;

	free(vartab.vars);
	vartab.vars = new_vars;
	return True;
}

uint64_t get_index(const char *name,size_t name_size){
	uint64_t i = 0;
	while(strcmp(name,vartab.vars[i].name) != 0 && i < vartab.length)
		++i;
	return i;
}

void *get_var_i(uint64_t index){
	return vartab.vars[index].var;
}

void *get_var(const char *name, size_t name_size){
	return get_var_i(get_index(name,name_size));
}

type get_type_i(uint64_t index){
	return vartab.vars[index].type;
}

type get_type(const char *name,size_t name_size){
	return get_type_i(get_index(name,name_size));
}

type get_type_from_name(const char *name, size_t name_size){
	char *str = malloc(name_size + 1);
	strncpy(str, name, name_size);
	str[name_size] = '\0';
	if(strcmp(str, "int") == 0){
		return S_ENT;
	}else if(strcmp(str,"float") == 0){
		return S_FLOT;
	}else if(strcmp(str, "char") == 0){
		return S_CAR;
	}else if(strcmp(str, "string") == 0){
		return S_CHAINE;
	}else if(strcmp(str, "tab") == 0){
		return S_TAB;
	}
	return S_NOT;
}

char *get_name_from_type(type t){
	char *res = malloc(7);
	switch (t) {
		case S_ENT: strcpy(res,"int");break;
		case S_FLOT: strcpy(res,"float");break;
		case S_CAR: strcpy(res,"char");break;
		case S_CHAINE: strcpy(res,"string");break;
		case S_TAB: strcpy(res,"tab");break;
		default: free(res);res = NULL;break;
	}
	return res;
}