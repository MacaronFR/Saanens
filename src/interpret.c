#include <interpret.h>

boolean interpret_command(gchar *command){
//	printf("command : %s\n", command);
	if(is_declaration(command)){
		declare(command);
		if(is_affectation(command)){
//			printf("affectation");
		}
	}
	return False;
}

boolean is_declaration(gchar *command){
	const char * exp = "^[ \t\n\r\f]*(int|float|char|string)[ \t\n\r\f]+[a-zA-Z][a-zA-Z0-9_]*";
	if(regpresent(exp, command)){
		return True;
	}
	return False;
}

boolean is_affectation(gchar *command){
	const char * exp = "^([ \t\n\r\f]*(int|float|char|string)?[ \t\n\r\f]*)*[a-zA-Z][a-zA-Z0-9_]*[ \t\n\r\f]*=[ \t\n\r\f]*[^; \t\n\r\f]+;[ \t\n\r\f]*";
	if(regpresent(exp,command)){
		return True;
	}
	return False;
}

boolean s_testreg(const char* exp, gchar *command, regmatch_t **pmatch, int cflags){
	regex_t reg;
	int match;
	regcomp(&reg, exp, cflags);
	if(cflags & REG_NOSUB) {
		match = regexec(&reg, command, 0, NULL, 0);
	}else{
		if(pmatch == NULL){
			fprintf(stderr, "In %s at line %d in function regretrieve : parameter pmatch must not be NULL");
			exit(EXIT_FAILURE);
		}
		if(*pmatch != NULL){
			free(*pmatch);
		}
		*pmatch = malloc(sizeof(pmatch) * reg.re_nsub);
		printf("groups = %d\n",reg.re_nsub);
		match = regexec(&reg, command, reg.re_nsub, *pmatch, 0);

	}
	regfree(&reg);
	if(match == 0)
		return True;
	return False;
}

boolean declare(gchar *command){
	char *exp = "^[ \t\n\r\f]*((int|float|char|string))[ \t\n\r\f]+(([a-zA-Z][a-zA-Z0-9_]*))";
	char *info[2];
	int start = 0;
	int end = 0;
	regmatch_t *pmatch = NULL;
	regretrieve(exp,command,&pmatch);
	for(int i = 2; i < 4; ++i){
		start = pmatch[i].rm_so;
		end = pmatch[i].rm_eo;
		info[i-2] = malloc(end - start + 1);
		strncpy(info[i-2], command + start, end - start);
		info[i-2][end -start] = '\0';
//		printf("match N %d : *%s*\n",i,info[i-2]);
	}
	type typeid = get_type_from_name(info[0], strlen(info[0]));
	if(typeid != S_NOT) {
		new_var(NULL, info[1], sizeof(info[1]), typeid);
	}else{
		perror("Error on type");
		return False;
	}
	return True;
}

boolean affect(gchar *command){
	char *exp = "([a-zA-Z][a-zA-Z0-9_]*)[ \n\r\t\f]*=[ \n\r\t\f]*([^; \n\r\t\f]+);";
	regmatch_t *pmatch = NULL;
	regretrieve(exp,command,&pmatch);
	return True;
}