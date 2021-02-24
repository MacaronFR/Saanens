#include <function.h>

void print(char *string){
	slog("%s",string);
}

void exitSaanens(){
	if(in != stdin)
		fclose(in);
	if(out != stdin)
		fclose(out);
	destroy_vars();
	clear_history();
	exit(0);
}

void clearlog(){
	FILE *f = fopen("SaanensCLI.log", "w");
	fclose(f);
}