#include <variable.h>

s_vars vartab;

s_var *new_var(const char *name, size_t name_size, type t){
	if(t == S_NOT)
		return NULL;
	s_var *new_vars = malloc(sizeof(s_var) * (vartab.length+1)); //new tab variable
	if(new_vars == NULL)
		return NULL;
	s_var new_var; //new variable
	new_var.name = malloc(name_size+1); //alloc name string
	if(new_var.name == NULL){
		free(new_vars);
		return NULL;
	}
	strncpy(new_var.name, name, name_size); //copy new name
	new_var.name[name_size] = '\0'; //Null Byte at end
	new_var.type = t; //assign type
	new_var.undefined = True;
	for(uint64_t i = 0; i < vartab.length; ++i) //copy ancient vartab to new one
		new_vars[i] = vartab.tab[i];
	new_vars[vartab.length] = new_var; //add new var to vartab
	//printf("*%d*\n",vartab.length);
	vartab.length++; //increment vartab length
	free(vartab.tab); //free ancient vartab ptr
	vartab.tab = new_vars; //assign new vartab
	return (vartab.tab + vartab.length - 1); //return address of the created var
}

boolean assign_value(s_var *var, void *value){
	var->undefined = False;
	switch (var->type) {
		case S_ENT: var->value.ve = *((int*)value);break;
		case S_FLOT: var->value.vf = *((double*)value);break;
		case S_CAR: var->value.vc = *((char*)value);break;
		case S_CHAINE: var->value.vs = malloc(strlen((char*)value));strcpy(var->value.vs, (char*)value);break;
		default: return False;
	}
	return True;
}

uint64_t get_index(const char *name,size_t name_size){
	uint64_t i = 0;
	if(vartab.length > 0) {
		while (i < vartab.length && strcmp(name, vartab.tab[i].name) != 0)
			++i;
	}
	return i;
}

void *get_val_i(uint64_t index){
	switch (vartab.tab[index].type){
		case S_ENT: return &(vartab.tab[index].value.ve);
		case S_FLOT: return &(vartab.tab[index].value.vf);
		default: return NULL;
	}
}

void *get_val(const char *name, size_t name_size){
	return get_val_i(get_index(name,name_size));
}

type get_type_i(uint64_t index){
	return vartab.tab[index].type;
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

s_var *get_var(const char *name, size_t name_size){
	uint64_t i = get_index(name, name_size);
	if(i == vartab.length){
		return NULL;
	}
	return get_var_i(i);
}

s_var *get_var_i(uint64_t index){
	if(index >= 0 && index < vartab.length)
		return vartab.tab + index;
}