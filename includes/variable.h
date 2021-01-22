#ifndef SAANENS_VARIABLE_H
#define SAANENS_VARIABLE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum s_bool{False = 0, True = 1} boolean;

typedef enum s_type{S_NOT = 0, S_ENT = 1, S_FLOT = 2, S_CAR = 4, S_CHAINE = 8, S_TAB = 16} type;

typedef union{
	int ve;
	double vf;
	char vc;
	char *vs;
	void *vb;
} s_value;

typedef struct{
	type type;
	char *name;
	s_value value;
	boolean undefined;
} s_var;

typedef struct {
	s_var *tab;
	uint64_t length;
} s_vars;

s_var *new_var(const char *name, size_t name_size, type t);
boolean assign_value(s_var *var, void *value);
void *get_var_i(uint64_t index);
void *get_var(const char *name, size_t name_size);
uint64_t get_index(const char *name, size_t name_size);
type get_type_i(uint64_t index);
type get_type(const char *name,size_t name_size);
type get_type_from_name(const char *name, size_t name_size);
char *get_name_from_type(type t);

#endif //SAANENS_VARIABLE_H