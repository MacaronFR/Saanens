#include <interpret.h>

extern s_vars vartab;

boolean interpret_command(char *command){
//	if(command[strlen(command) - 1] != ';'){
//		fprintf(stderr, "Not terminated command\n");
//		return False;
//	}
	add_history(command);
//	printf("command : *%s*\n", command);
	if(detect_keyword(command)){
		printf("Keyword\n");
	}
	return False;
}

boolean s_testreg(const char* exp, char *command, regmatch_t **pmatch, int cflags){
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

boolean declare(char *command){
	char *exp = "^[ \t\n\r\f]*(int|float|char|string)[ \t\n\r\f]+([a-zA-Z][a-zA-Z0-9_]*)(?:[ \t\n\r\f]*=[ \t\n\r\f]*(.+[^ \t\n\r\f]*)[ \t\n\r\f]*)?;";
	char *info[3];
	void *val;
	s_var *nvar;
	int start = 0;
	int end = 0;
	regmatch_t *pmatch = NULL;
	if(!regretrieve(exp,command,&pmatch)){
		fprintf(stderr, "Invalid declaration");
		return False;
	}
	process_pmatch(command, pmatch, 3, info);
	type typeid = get_type_from_name(info[0], strlen(info[0]));
	free(info[0]);
	if(typeid == S_NOT) {
		free(info[1]);
		free(info[2]);
		fprintf(stderr,"Invalid type");
		return False;
	}
	if(get_index(info[1],sizeof(info[1])) != vartab.length){
		fprintf(stderr,"Variable %s already declared\n",info[1]);
		free(info[1]);
		free(info[2]);
		return False;
	}
	nvar = new_var(info[1], sizeof(info[1]), typeid);
	free(info[1]);
	if(nvar == NULL) {
		free(info[2]);
		fprintf(stderr,"Error while declaring new variable");
		return False;
	}
	if(*(info[2]) != '\0'){
		val = check_value(info[2],typeid);
		if(val == NULL){
			free(info[2]);
			fprintf(stderr, "Out of memory");
			return False;
		}
		if(!assign_value(nvar,val)){
			fprintf(stderr, "Can't assign value %s to var %s",info[2],nvar->name);
			free(info[2]);
			return False;
		}
	}
	free(info[2]);
	return True;
}

boolean detect_keyword(char *command){
	char *exptype = "^[ \t\n\r\f]*(int|float|char|string|bool)[ \t\n\r\f]+([a-zA-Z][a-zA-Z0-9]*)";
	char *expcondboucle = "^[ \t\n\r\f]*(bouc|fromage|lait|chevre|troupeau|cassemire)[ \t\n\r\f]*[(].*[)][ \t\n\r\f]*:[ \t\n\r\f]*$";
	if(regpresent(exptype, command)) {
		printf("Declaration\n");
		if(declare(command)){
			printf("Declared\n");
		}
		return True;
	}else if(regpresent(expcondboucle,command)){
		printf("Condition/Boucle\n");
		condboucle(command);
	}
	return False;
}

boolean condboucle(char *command){
	char *expcondition = "^[ \t\n\r\f]*(chevre|troupeau)[ \t\n\r\f]*[(][ \t\n\r\f]*(.+[^ \t\n\r\f])[ \t\n\r\f]*[)][ \t\n\r\f]*:[ \t\n\r\f]*$";
	regmatch_t *pmatch = NULL;
	char *info[2];
	int start,end;
	regretrieve(expcondition,command,&pmatch);
	process_pmatch(command,pmatch,2,info);
	if(strcmp(info[0], "chevre") == 0){
		chevre(info[1]);
	}
	return True;
}

void *check_value(char *value, type tid){
	switch (tid){
		case S_ENT: return (void*)check_int(value);
		case S_FLOT: return (void*)check_double(value);
	}
}

int *check_int(const char *value){
	int *val = malloc(sizeof(int));
	if(sscanf(value,"%d",val) == EOF){
		free(val);
		return NULL;
	}
	return val;
}

double *check_double(const char*value){
	double *val = malloc(sizeof(double));
	if(sscanf(value,"%lf",val) == EOF){
		free(val);
		return NULL;
	}
	return val;
}

boolean process_pmatch(char *string ,regmatch_t *pmatch, size_t nmatch, char **info){
	int start,end;
	for(int i = 1; i < nmatch + 1; ++i){
		start = pmatch[i].rm_so;
		end = pmatch[i].rm_eo;
		info[i-1] = malloc(end - start);
		strncpy(info[i-1], string + start, end - start);
		info[i-1][end - start] = '\0';
		printf("Match %d = *%s*\n",i,info[i-1]);
	}
	free(pmatch);
	return True;
}

boolean chevre(char *arg){
	char input[1024];
	HIST_ENTRY *brebis;
	HIST_ENTRY *chevreau;
	int i = 0;
	while(strcmp(input, "chevreau:") != 0) {
		fflush(stdin);
		scanf("%[^\n]", input);
		if (strcmp(input, "chevreau:") != 0) {
			fprintf(stderr, "Needed chevreau after chevre\n");
		}
	}
	add_history(input);
	chevreau = current_history();
	do{
		fflush(stdin);
		scanf("%[^\n]",input);
		// TODO verif si chaine commande valide
		add_history(input);
		if(strcmp(input,"chevre") == 0){
			++i;
		}
		if(strcmp(input, "brebis") == 0 && i == 0){
			brebis = current_history();
		}
		if(strcmp(input,"breche") == 0){
			if(i == 0){
				brebis = current_history();
			}
			++i;
		}
		if(strcmp(input, "finchevre") == 0 && i != 0){
			--i;
		}
		printf("**i = %d**\n",i);
	} while (i != 0 || strcmp(input,"finchevre;") != 0);
	return True;
}