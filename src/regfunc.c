#include <regfunc.h>

boolean s_testreg(const char* exp, const char *command, regmatch_t **pmatch, int cflags){ //Fonction de test d'une expression régulière
	regex_t reg;
	int match;
	regcomp(&reg, exp, cflags);
	if(cflags & REG_NOSUB) {
		match = regexec(&reg, command, 0, NULL, 0);
	}else{
		if(pmatch == NULL){
			slog("In %s at line %d in function regretrieve : parameter pmatch must not be NULL",__FILE__,__LINE__);
			exit(EXIT_FAILURE);
		}
		if(*pmatch != NULL){
			free(*pmatch);
		}
		*pmatch = calloc(reg.re_nsub + 2, sizeof(regmatch_t));
		if(*pmatch == NULL){
			regfree(&reg);
			return False;
		}
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
		info[i-1] = malloc(end - start + 1);
		fflush(stdout);
		strncpy(info[i-1], string + start, 	end - start);
		info[i-1][end - start] = '\0';
//		slog("Match %d = *%s*\n",i,info[i-1]);
	}
	free(pmatch);
	return True;
}

boolean regparenthesis(const char *input, char **match, int **se){
	int len = strlen(input);
	int count = 0;
	int i;
	const char *first;
	boolean present = False;
	for(i =0; i < len; ++i){
		if(input[i] == '('){
			++count;
			if(!present){
				first = input + i + 1;
				present = True;
			}
		}
		if(input[i] == ')'){
			--count;
		}
		if(present && count == 0){
			break;
		}
	}
	if(i == len){
		return False;
	}
	if(se != NULL) {
		(*se)[0] = first - input;
		(*se)[1] = i;
	}
	*match = malloc(i - (first - input)+1);
	strncpy(*match, first, i - (first - input));
	(*match)[i - (first - input)] = '\0';
	return True;
}