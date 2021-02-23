#include <parse.h>

int parseInt(const char *n){
	return atoi(n);
}

double parseFloat(const char *n){
	return atof(n);
}

char parseChar(const char *n){
	if(n[0] == '\'' && n[2] == '\'')
		return n[1];
	return -1;
}

char *parseString(const char *s){
	int count = 0;
	unsigned long long i, len = strlen(s);
	char *old = malloc(len + 1);
	char *new = malloc(len + 1);
	strcpy(old, s);
	for(i = 0; i + count < len; ++i){
		if(old[i+count] == '\\') {
			switch (old[i+count + 1]) {
				case 'a': new[i] = '\a';break;
				case 'b': new[i] = '\b';break;
				case 'f': new[i] = '\f';break;
				case 'n': new[i] = '\n';break;
				case 'r': new[i] = '\r';break;
				case 't': new[i] = '\t';break;
				case 'v': new[i] = '\v';break;
				case '\\': new[i] = '\\';break;
				case '\'': new[i] = '\'';break;
				case '\"': new[i] = '\"';break;
				case '\?': new[i] = '\?';break;
				default: count = -1;break;
			}
			if(count == -1){
				free(old);free(new);
				return NULL;
			}
			count++;
			continue;
		}
		new[i] = old[i+count];
	}
	new[i] = '\0';
	free(old);
	old = malloc(i+1);
	strcpy(old,new);
	free(new);
	return old;
}