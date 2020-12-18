#ifndef SAANENS_VARIABLE_H
#define SAANENS_VARIABLE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S_TYPE_ENTIER 1
#define S_TYPE_FLOTTANT 2
#define S_TYPE_CARACTERE 4
#define S_TYPE_CHAINE 8
#define S_TYPE_TABLEAU 16

/*#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif*/

typedef struct{
	uint8_t type;
	char *name;
	void *var;
} s_var;

typedef struct {
	s_var *vars;
	uint64_t length;
} s_vars;

//typedef uint8_t boolean;

typedef enum boolean {FALSE = 0, TRUE = 1} boolean;

boolean new_var(void *value, const char *name, size_t name_size, uint8_t type, s_vars *vars);
void *get_var_i(uint64_t index,s_vars *vars);
void *get_var(const char *name, size_t name_size, s_vars *vars);
uint64_t get_index(const char *name, size_t name_size,s_vars *vars);
uint8_t get_type_i(uint64_t index, s_vars *vars);
uint8_t get_type(const char *name,size_t name_size, s_vars *vars);

#endif //SAANENS_VARIABLE_H