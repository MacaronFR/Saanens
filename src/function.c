#include <function.h>

void print(char *string){
	printf("%s",string);
}

void exitSaanens(){
	exit(0);
}

void slog(char *format, ...){
	va_list arg;
	va_start(arg,format);
	FILE *f = fopen("SaanensCLI.log", "ab");
	vfprintf(f, format, arg);
	va_end(arg);
	fclose(f);
}

void clearlog(){
	FILE *f = fopen("SaanensCLI.log", "w");
	fclose(f);
}

void freematch(char *match[], size_t n){
	for (size_t i = 0; i < n; ++i){
		free(match[i]);
	}
}