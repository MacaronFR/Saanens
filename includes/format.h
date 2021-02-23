#ifndef SAANENS_FORAMT_H
#define SAANENS_FORAMT_H

#include <s_type.h>
#include <regfunc.h>

char *prepareString(char *input);
boolean check_parenthese(const char *line);
char *execute_parenthese(const char *line);
char *replace_in_string(const char *source, const char *replace, int start, int end);

#endif //SAANENS_FORAMT_H