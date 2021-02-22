#ifndef SAANENS_INTERPRET_H
#define SAANENS_INTERPRET_H

#include <string.h>
#include <variable.h>
#include <regfunc.h>
#include <function.h>
#include <readline/history.h>
#include <operation.h>

boolean interpret_command(char *command, boolean history);
boolean declare(char *command);
boolean condboucle(char *command, boolean history);
boolean affect(char *command);
boolean detect_keyword(char *command, boolean history);
boolean detect_operation(char *command, boolean history);
void *check_value(char *value, type id);
int *check_int(const char *value);
double *check_double(const char*value);
char *check_car(const char*value);
boolean chevre(char *arg, boolean history);
void trim(char *string);

#endif //SAANENS_INTERPRET_H