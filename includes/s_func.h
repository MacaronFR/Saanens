#ifndef SAANENS_S_FUNC_H
#define SAANENS_S_FUNC_H

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void slog(char *format, ...);
void freematch(char *match[], size_t n);
int getinput(FILE *file, char ***input);
void trim(char *string);

#endif //SAANENS_S_FUNC_H
