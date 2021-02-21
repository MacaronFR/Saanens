#include <regfunc.h>

boolean s_testreg(const char* exp, const char *command, regmatch_t **pmatch, int cflags){ //Fonction de test d'une expression régulière
	regex_t reg;
	int match;
	regcomp(&reg, exp, cflags);
	if(cflags & REG_NOSUB) {
		match = regexec(&reg, command, 0, NULL, 0);
	}else{
		if(pmatch == NULL){
			fprintf(stderr, "In %s at line %d in function regretrieve : parameter pmatch must not be NULL",__FILE__,__LINE__);
			exit(EXIT_FAILURE);
		}
		if(*pmatch != NULL){
			free(*pmatch);
		}
		*pmatch = malloc(sizeof(pmatch) * reg.re_nsub + 1);
		if(pmatch == NULL){
			regfree(&reg);
			return False;
		}
//		printf("groups = %d\n",reg.re_nsub);
		match = regexec(&reg, command, reg.re_nsub + 1, *pmatch, 0);
	}
	regfree(&reg);
	if(match == 0)
		return True;
	return False;
}

boolean process_pmatch(const char *string ,regmatch_t *pmatch, size_t nmatch, char **info){ //Fonction pour récuperer les chaine a partir des match de regexp
	int start,end;
	for(int i = 1; i < nmatch + 1; ++i){
		start = pmatch[i].rm_so;
		end = pmatch[i].rm_eo;
		info[i-1] = malloc(end - start);
		fflush(stdout);
		strncpy(info[i-1], string + start, end - start);
		info[i-1][end - start] = '\0';
		slog("Match %d = *%s*\n",i,info[i-1]);
	}
	free(pmatch);
	return True;
}