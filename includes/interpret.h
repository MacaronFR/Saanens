#ifndef SAANENS_INTERPRET_H
#define SAANENS_INTERPRET_H

#include <string.h>
#include <variable.h>
#include <regex.h>
#include <function.h>
#include <readline/history.h>

#define regpresent(exp, command) (s_testreg(exp, command, NULL, REG_NOSUB | REG_EXTENDED))
#define regretrieve(exp, command, pmatch) (s_testreg(exp, command, pmatch, REG_EXTENDED))

typedef enum s_operator {S_NOTOP = 0, S_EGALITE = 1, S_DIFF = 2, S_INF = 4, S_SUP = 8, S_INFEG = 16, S_SUPEG = 32} operator;
typedef struct{
	operator op;
	char *operande1;
	char *operande2;
} s_comp;

boolean interpret_command(char *command, boolean history);
boolean s_testreg(const char *exp, char *command, regmatch_t **pmatch,int cflags);
boolean declare(char *command);
boolean condboucle(char *command, boolean history);
boolean affect(char *command);
boolean detect_keyword(char *command, boolean history);
void *check_value(char *value, type id);
int *check_int(const char *value);
double *check_double(const char*value);
boolean process_pmatch(char *string, regmatch_t *pmatch, size_t nmatch, char **info);
boolean syntax_check(char *command);
boolean chevre(const char *arg, boolean history);

#endif //SAANENS_INTERPRET_H