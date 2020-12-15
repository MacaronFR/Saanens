#ifndef SAANENS_VARIABLE_H
#define SAANENS_VARIABLE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S_TYPE_ENTIER
#define S_TYPE_FLOTTANT
#define S_TYPE_CARACTERE
#define S_TYPE_CHAINE
#define S_TYPE_TABLEAU

#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif

typedef struct{
	uint8_t type;
	char *name;
	void *var;
} s_var;

typedef struct {
	s_var *vars;
	uint64_t length;
} s_vars;

typedef uint8_t boolean;

boolean new_var(void *value, const char *name, size_t name_size, uint8_t type, s_vars *vars);

#endif //SAANENS_VARIABLE_H