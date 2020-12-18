#include <variable.h>

boolean new_var(void *value, const char *name, size_t name_size, uint8_t type, s_vars *vars){
	s_var *new_vars = malloc(sizeof(s_var) * vars->length+1);
	s_var new_var;
	new_var.name = malloc(name_size+1);
	for(uint64_t i = 0; i < name_size; ++i){
		new_var.name[i] = name[i];
	}
	new_var.name[name_size] = '\0';
	new_var.type = type;
	for(uint64_t i = 0; i < vars->length; ++i){
		new_vars[i] = vars->vars[i];
	}
	new_vars[vars->length] = new_var;
	vars->length++;
	free(vars->vars);
	vars->vars = new_vars;
	return TRUE;
}

uint64_t get_index(const char *name,size_t name_size, s_vars *vars){
	uint64_t i = 0;
	while(strcmp(name,vars->vars[i].name) != 0 && i < vars->length)
		++i;
	return i;
}

void *get_var_i(uint64_t index, s_vars *vars){
	return vars->vars[index].var;
}

void *get_var(const char *name, size_t name_size, s_vars *vars){
	return get_var_i(get_index(name,name_size,vars),vars);
}

uint8_t get_type_i(uint64_t index, s_vars *vars){
	return vars->vars[index].type;
}

uint8_t get_type(const char *name,size_t name_size, s_vars *vars){
	return get_type_i(get_index(name,name_size,vars),vars);
}