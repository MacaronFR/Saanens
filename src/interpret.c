#include <interpret.h>

extern s_vars vartab;

boolean interpret_command(char *command, boolean history){
//	if(command[strlen(command) - 1] != ';'){
//		fprintf(stderr, "Not terminated command\n");
//		return False;
//	}
	if(!history) { //Si on prend de l'entré et pas de l'historique
		add_history(command);
		if (history_length != 1)
			history_offset++;
	}
	slog("command : *%s*\n", command);
	if(detect_keyword(command,history)){
		slog("Keyword\n");
		return True;
	}else if(detect_operation(command, history)){
		slog("operation\n");
		return True;
	}
	return False;
}

boolean declare(char *command){ //Fonction declaration de variable
	char *exp = "^[ \t\n\r\f]*(int|float|char|string)[ \t\n\r\f]+([a-zA-Z][a-zA-Z0-9_]*)(?:[ \t\n\r\f]*=[ \t\n\r\f]*(.+[^ \t\n\r\f]*)[ \t\n\r\f]*)?;";
	char *info[3];
	void *val;
	s_var *nvar;
	int start = 0;
	int end = 0;
	regmatch_t *pmatch = NULL;
	if(!regretrieve(exp,command,&pmatch)){//Recupération des infos importantes de la commande
		fprintf(stderr, "Invalid declaration");
		return False;
	}
	process_pmatch(command, pmatch, 3, info); //Process des pmatch vers des chaines
	type typeid = get_type_from_name(info[0], strlen(info[0])); //Recuperation du type
	free(info[0]);
	if(typeid == S_NOT) { //si le type est invalide
		free(info[1]);
		free(info[2]);
		fprintf(stderr,"Invalid type");
		return False;
	}
	if(get_index(info[1],sizeof(info[1])) != vartab.length){ //vérification de la non existence de la variable
		fprintf(stderr,"Variable %s already declared\n",info[1]);
		free(info[1]);
		free(info[2]);
		return False;
	}
	nvar = new_var(info[1], sizeof(info[1]), typeid); //déclaration de la variable
	free(info[1]);
	if(nvar == NULL) { //Vérification pour pas d'erreur durant la déclaration
		free(info[2]);
		fprintf(stderr,"Error while declaring new variable");
		return False;
	}
	if(*(info[2]) != '\0'){ //Si il y a une affectation
		val = check_value(info[2],typeid);
		if(val == NULL){
			free(info[2]);
			fprintf(stderr, "Out of memory");
			return False;
		}
		if(!assign_value(nvar,val)){ //Affectation de la variable
			fprintf(stderr, "Can't assign value %s to var %s",info[2],nvar->name);
			free(info[2]);
			return False;
		}
	}
	free(info[2]);
	return True;
}

boolean detect_keyword(char *command, boolean history){
	char *exptype = "^[ \t\n\r\f]*(int|float|char|string|bool)[ \t\n\r\f]+([a-zA-Z][a-zA-Z0-9]*)"; //Regexp pour type
	char *expcondboucle = "^[ \t\n\r\f]*(bouc|fromage|lait|chevre|troupeau|cassemire)[ \t\n\r\f]*[(].*[)][ \t\n\r\f]*:[ \t\n\r\f]*$"; //Regexp pour boucle/condition
	if(regpresent(exptype, command)) { //Si type
		slog("Declaration\n");
		if(declare(command)){
			slog("Declared\n");
		}
		return True;
	}else if(regpresent(expcondboucle,command)){ //Si cond/boucle
		slog("Condition/Boucle\n");
		if(condboucle(command,history)){
			return True;
		}
	}else if(regpresent("^print[ \n\t\r\f]*\\([ \n\t\r\f]*([^)]+)[ \n\t\r\f]*\\);$",command)){//Si print
		regmatch_t *match = NULL;
		regretrieve("^print[ \n\t\r\f]*\\([ \n\t\r\f]*([^)]+)[ \n\t\r\f]*\\);$", command, &match);
		char *info[1];
		process_pmatch(command, match, 1, info);
		print(info[0]);
	}else if(strcmp(command, "clearlog;") == 0){
		clearlog();
	}
	return False;
}

boolean detect_operation(char *command, boolean history){
	char *reg = "[=/*+<>]|[&]{2}|[|]{2}|-";
	if(regpresent(reg, command)){
		s_var res = processOperation(command, 0);
		return True;
	}
	return False;
}

boolean condboucle(char *command, boolean history){
	char *expcondition = "^[ \t\n\r\f]*(chevre|troupeau)[ \t\n\r\f]*[(][ \t\n\r\f]*(.*[^ \t\n\r\f])[ \t\n\r\f]*[)][ \t\n\r\f]*:[ \t\n\r\f]*$"; //regexp pour condition
	regmatch_t *pmatch = NULL;
	char *info[2];
	int start,end;
	regretrieve(expcondition,command,&pmatch);
	process_pmatch(command,pmatch,2,info);
	if(strcmp(info[0], "chevre") == 0){//si if
		if(chevre(info[1],history)){//si if sans erreur
			return True;
		}
	}
	return False;
}

void *check_value(char *value, type tid){
	switch (tid){ //verif de la valeur en fonction du type
		case S_ENT: return (void*)check_int(value);
		case S_FLOT: return (void*)check_double(value);
	}
}

int *check_int(const char *value){//verif valeur entière
	int *val = malloc(sizeof(int));
	if(sscanf(value,"%d",val) == EOF){
		free(val);
		return NULL;
	}
	return val;
}

double *check_double(const char*value){ //verif valeur flottante
	double *val = malloc(sizeof(double));
	if(sscanf(value,"%lf",val) == EOF){
		free(val);
		return NULL;
	}
	return val;
}

//TODO verif valeur char et string

boolean check_chevre(char *command){
	
	regmatch_t *pmatch = NULL;
	//regretrieve(reg,command, &pmatch);
	//if()
}

boolean chevre(const char *arg, boolean history){ //execute condition
	char *reg = "^[ \t\n\r\f]*(chevre|breche)[ \t\n\r\f]*[(][ \t\n\r\f]*(.*[^ \t\n\r\f])[ \t\n\r\f]*[)][ \t\n\r\f]*:[ \t\n\r\f]*$";
	char input[1024];
	int brebis = -1, chevreau, finchevre;
	int i = 0;
	if(!history) { //si pas de recherche dans l'historique recup depuis le stdin
		fflush(stdin);
		scanf("%[^\n]", input);
		add_history(input);
		history_offset++;
	}else{ //sino on recup depuis l'historique
		strcpy(input,next_history()->line);
		printf("%s**\n",input);
	}
	if (strcmp(input, "chevreau:") != 0) {
		fprintf(stderr, "Needed chevreau after chevre\n");
		return -1;
	}
	chevreau = where_history();
	do{
		if(!history) {
			fflush(stdin);
			scanf("%[^\n]", input);
			add_history(input);
			history_offset++;
		}else{
			strcpy(input, next_history()->line);
		}
		if(regpresent(reg, input)){
			if(regpresent("breche",input)){
				if(i == 0) {
					if (brebis == -1)
						brebis = where_history();
					else {
						printf("Error already have brebis");
						return False;
					}
				}
			}
			++i;
			//printf("ici i = %d\n",i);
		}
		if(strcmp(input,"brebis:") == 0 && i == 0){
			if(brebis == -1)
				brebis = where_history();
			else{
				printf("Error brebis already declared");
				return False;
			}
		}
		if(strcmp(input, "finchevre;") == 0 && i != 0){
			--i;
			input[0] = '\0';
		}
	} while (i != 0 || strcmp(input,"finchevre;") != 0);
	finchevre = where_history();
	if(arg != NULL){
		history_set_pos(chevreau+1);
		while (where_history() != finchevre || where_history() != brebis) {
			printf("ici**");
			if(!interpret_command(current_history()->line, True)){
				history_set_pos(where_history());
				return False;
			}
			printf("%s*\n",current_history()->line);
			history_set_pos(where_history()+1);
		}
	}
	history_set_pos(finchevre);
	return True;
}

boolean syntax_check(char *command){

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