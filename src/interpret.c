#include <interpret.h>

gboolean interpret_command(gchar *command){
	printf("command : %s\n", command);
	if(is_declaration(command)){
		printf("déclaration");
		if(is_affectation(command)){
			printf("affectation");
		}
	}
	return FALSE;
}

gboolean is_declaration(gchar *command){
	const char * exp = "^[ \t\n\r\f]*(int|float|char|string)[ \t\n\r\f]+[a-zA-Z][a-zA-Z0-9_]*";
	if(regtest(exp, command) == 0){
		return TRUE;
	}
	return FALSE;
}

gboolean is_affectation(gchar *command){
	const char * exp = "^[ \t\n\r\f]*(int|float|char|string)[ \t\n\r\f]+[a-zA-Z][a-zA-Z0-9_]*";
	if(regtest(exp,command) == 0){
		return TRUE;
	}
	return FALSE;
}

int regtest(const char* exp, gchar *command){
	regex_t reg;
	int match;
	regcomp(&reg, exp, REG_NOSUB | REG_EXTENDED);
	match = regexec(&reg, command, 0, NULL, 0);
	regfree(&reg);
	return match;
}