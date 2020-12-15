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