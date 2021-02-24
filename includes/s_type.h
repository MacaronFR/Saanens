#ifndef SAANENS_S_TYPE_H
#define SAANENS_S_TYPE_H

#include <stdint.h>
#include <stdio.h>

typedef enum s_cat {S_LOG = 1, S_AFF = 2, S_COMP = 4, S_ADSB = 8, S_MOD = 16, S_MLDV = 32} s_cat;
typedef enum s_op {S_AND = 1, S_OR = 2, S_NO = 3, S_XOR = 4, S_EQ = 5, S_BEL = 6, S_BLE = 7, S_ABV = 8, S_ABE = 9, S_DIF = 10, S_ADD = 11, S_SUB = 12, S_MDL = 13, S_MUL = 14, S_DIV = 15} s_op;
typedef enum s_bool{False = 0, True = 1} boolean;

typedef enum s_type{S_NOT = 0, S_ENT = 1, S_FLOT = 2, S_CAR = 4, S_CHAINE = 8, S_TAB = 16, S_BOOL} type;

typedef union s_value{
	int ve;
	double vf;
	char vc;
	char *vs;
	boolean vb;
} s_value;

typedef struct s_var{
	type type;
	char *name;
	s_value value;
	boolean undefined;
} s_var;

typedef struct s_vars{
	s_var *tab;
	uint64_t length;
} s_vars;

extern FILE *in;
extern FILE *out;

#define returnNillVar return (s_var){S_NOT,.undefined = True}

#endif //SAANENS_S_TYPE_H
