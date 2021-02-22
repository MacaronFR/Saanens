#include <function.h>

void print(char *string){
	slog("%s",string);
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

int getinput(FILE *file, char ***input){
	char buffer[256];
	char *lineend;
	char *command = NULL;
	char *start;
	int size = 0;
	int nbcmd = 0;
	while(fgets(buffer, sizeof(buffer), file) != 0){
		if(buffer[strlen(buffer) - 2] == '\r'){
			buffer[strlen(buffer) - 2] = '\0';
		}else if(buffer[strlen(buffer) - 1] == '\n'){
			buffer[strlen(buffer) - 1] = '\0';
		}
		if (strlen(buffer) == 0){
			return 0;
		}
		start = buffer;
		
		do{
			lineend = strpbrk(start, ";:");
			if(lineend == NULL) {
				size += strlen(buffer);
				command = realloc(command, size + 1);
				strncpy(command + size - strlen(buffer), buffer, strlen(buffer));
				command[size] = '\0';
			}else {
				size += lineend - start;
				command = realloc(command, size + 2);
				strncpy(command + size - (lineend - start), start, lineend - start + 1);
				command[size + 1] = '\0';
				++nbcmd;
				*input = realloc(*input, sizeof(char *) * nbcmd);
				(*input)[nbcmd - 1] = command;
				command = NULL;
				start += size + 1;
				if(lineend == buffer + strlen(buffer) - 1){
					return nbcmd;
				}
				size = 0;
			}
		}while(lineend != NULL);
	}
	return nbcmd;
}