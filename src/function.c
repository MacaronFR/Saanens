#include <function.h>

void print(char *string){
	slog("%s",string);
}

void exitSaanens(){
	destroy_vars();
	exit(0);
}

void clearlog(){
	FILE *f = fopen("SaanensCLI.log", "w");
	fclose(f);
}