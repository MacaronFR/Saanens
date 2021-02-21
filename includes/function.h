#ifndef SAANENS_FUNCTION_H
#define SAANENS_FUNCTION_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void print(char *string);
void exitSaanens();
void slog(char *format, ...);
void clearlog();
void freematch(char *match[], size_t n);
int getinput(FILE *file, char ***input);

#endif //SAANENS_FUNCTION_H
