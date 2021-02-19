#ifndef SAANENS_FUNCTION_H
#define SAANENS_FUNCTION_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void print(char *string);
void exitSaanens();
void slog(char *format, ...);
void clearlog();
void freematch(char *match[], size_t n);

#endif //SAANENS_FUNCTION_H
