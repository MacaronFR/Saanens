#ifndef SAANENS_VARIABLE_H
#define SAANENS_VARIABLE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <s_type.h>

s_var *new_var(const char *name, size_t name_size, type t);
boolean assign_value(s_var *var, s_value value);
void *get_val_i(uint64_t index);
void *get_val(const char *name, size_t name_size);
uint64_t get_index(const char *name, size_t name_size);
type get_type_i(uint64_t index);
type get_type(const char *name,size_t name_size);
type get_type_from_name(const char *name, size_t name_size);
char *get_name_from_type(type t);
s_var *get_var(const char *name, size_t name_size);
s_var *get_var_i(uint64_t index);
char *varToString(s_var var);

#endif //SAANENS_VARIABLE_H