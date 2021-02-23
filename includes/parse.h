#ifndef SAANENS_PARSE_H
#define SAANENS_PARSE_H

#include <string.h>
#include <stdlib.h>

int parseInt(const char *number);
double parseFloat(const char *number);
char parseChar(const char *character);
char *parseString(const char *string);

#endif //SAANENS_PARSE_H