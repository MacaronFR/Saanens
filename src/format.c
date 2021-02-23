#include <format.h>

char *prepareString(char *input){
	char *tmp;
	char *regcast = "(int|float|char|string|bool)[ \\t\\n\\r\\f]*[(]([^)]+)[)]";
	char *regscan = "scan[(](.+)[)]";
	while(regpresent(regcast, input)){
		input = cast(input);
	}
	while(regpresent(regscan, input)){
		int *se = malloc(sizeof(int)*2);
		char *arg;
		char buf[256];
		char *instr = NULL;
		int l;
		regparenthesis(input, &arg, &se);
		se[0] = input - strstr(input,"scan");
		tmp = malloc(strlen(arg) + 3);
		tmp[0] = '(';
		strcpy(tmp+1, arg);
		tmp[strlen(tmp)+1] = '\0';
		tmp[strlen(tmp)] = ')';
		free(arg);
		arg = tmp;
		preparePrint(arg);
		freematch(&arg, 1);
		while(fgets(buf, 255, stdin)){
			l = strlen(buf);
			if(buf[l-1] == '\n'){
				buf[l-1] = '\0';
				l--;
			}
			if(instr != NULL){
				arg = instr;
				instr = malloc(strlen(arg) + l);
				strcpy(instr, arg);
				free(arg);
			}else{
				instr = malloc(l);
				*instr = '\0';
			}
			strcpy(instr + strlen(instr),buf);
			if(l < 255){
				break;
			}
		}
		arg = replace_in_string(input, instr, se[0], se[1] + 1);
		free(input);
		input = arg;
	}
	while(check_parenthese(input)){
		tmp = execute_parenthese(input);
		if(tmp == NULL){
			return NULL;
		}
		free(input);
		input = tmp;
	}
	return input;
}

boolean check_parenthese(const char *l){
	if(l != NULL){
		char *reg = "[(].+[)]";
		return regpresent(reg, l);
	}
	return False;
}

char *execute_parenthese(const char *l){
	s_var resparenthese;
	const char *substr;
	char *resstr, *nl;
	int nlen;
	if(l != NULL) {
		char *command[1];
		if(regparenthesis(l, command, NULL)){
			trim(command[0]);
			resparenthese = processOperation(command[0], S_LOG);
			substr = NULL;
			for(int i = 0; i < strlen(l); ++i){
				if(l[i] == '('){
					substr = l+i+1;
					break;
				}
			}
			resstr = varToString(resparenthese);
			nlen = strlen(l) - strlen(command[0]) - 2 +strlen(resstr);
			nl = malloc(nlen);
			strncpy(nl,l,substr - l - 1);
			strcpy(nl + (substr - l - 1), resstr);
			strcpy(nl+(substr-l-1) + strlen(resstr), substr + strlen(command[0]) + 1);
			freematch(command, 1);
			free(resstr);
			return nl;
		}
		return NULL;
	}
	return NULL;
}

char *replace_in_string(const char *source, const char *replace, int start, int end){
	char *new = malloc(strlen(source) - (end-start) + strlen(replace) + 1);
	strncpy(new, source, start);
	strcpy(new + start, replace);
	strcpy(new+start+strlen(replace), source+end);
	return new;
}

