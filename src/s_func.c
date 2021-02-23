#include <s_func.h>

void slog(char *format, ...){
	va_list arg;
	va_start(arg,format);
	FILE *f = fopen("SaanensCLI.log", "ab");
	vfprintf(f, format, arg);
	va_end(arg);
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

void trim(char *s){
	int st = 0, ed = (int)strlen(s)-1;
	while(s[st] == ' ' || s[st] == '\n' || s[st] == '\r' || s[st] == '\t' || s[st] == '\f'){
		st++;
	}
	while((s[ed] == ' ' || s[ed] == '\n' || s[ed] == '\r' || s[ed] == '\t' || s[ed] == '\f') && ed > st){
		ed--;
	}
	for(int i = 0; i < ed - st +1; ++i){
		s[i] = s[i+st];
	}
	s[ed-st+1] = '\0';
}


boolean preparePrint(char *to_print){
	regmatch_t *pmatch = NULL;
	char *info[1];
	s_var vtoprint;
	if (regretrieve("[(](.+)[)]", to_print, &pmatch)) {
		process_pmatch(to_print, pmatch, 1, info);
		vtoprint = processOperation(info[0], 0);
		if (vtoprint.undefined) {
			return False;
		}
		if (vtoprint.type != S_CHAINE) {
			castVar(&vtoprint, S_CHAINE);
		}
		print(vtoprint.value.vs);
		free(vtoprint.value.vs);
		return True;
	}
	return False;
}