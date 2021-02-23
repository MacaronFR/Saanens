#include <condboucle.h>

boolean condboucle(char *command, boolean history){
	char *expcondboucle = "^(chevre|fromage)[ \t\n\r\f]*[(][ \t\n\r\f]*(.*[^ \t\n\r\f])[ \t\n\r\f]*[)][ \t\n\r\f]*:$"; //regexp pour condition
	regmatch_t *pmatch = NULL;
	char *info[2];
	regretrieve(expcondboucle,command,&pmatch);
	process_pmatch(command,pmatch,2,info);
	if(strcmp(info[0], "chevre") == 0){//si if
		if(chevre(info[1],history)){//si if sans erreur
			freematch(info, 2);
			return True;
		}
	}else if(strcmp(info[0], "fromage") == 0){
		if(fromage(info[1], history)){
			freematch(info, 2);
			return True;
		}
	}
	freematch(info, 2);
	return False;
}

boolean chevre(char *arg, boolean history){ //execute condition
	char reg[] = "^(chevre).*[(](.*)[)].*:";
	int brebis = -1, chevreau, finchevre;
	int i = 0;
	char **cmd;
	int nbcmd;
	if(!history) { //si pas de recherche dans l'historique recup depuis le stdin
		cmd = NULL;
		nbcmd = getinput(in, &cmd);
		for(i = 0; i < nbcmd; i++){
			add_history(cmd[i]);
			history_offset++;
		}
		i = 0;
	}else{ //sino on recup depuis l'historique
		cmd = malloc(sizeof(char *));
		cmd[0] = malloc(strlen(next_history()->line)+1);
		strcpy(cmd[0],current_history()->line);
		//printf("%s**\n",input);
	}
	if (strcmp(cmd[0], "chevreau:") != 0) {
		fprintf(stderr, "Needed chevreau after chevre\n");
		free(cmd);
		return -1;
	}
	free(cmd);
	cmd = NULL;
	chevreau = where_history();
	do{
		if(cmd != NULL){
			free(cmd[0]);
			free(cmd);
		}
		if(history_offset == history_length-1) {
			nbcmd = 0;
			while(nbcmd == 0){
				cmd = NULL;
				nbcmd = getinput(in, &cmd);
				for (int j = 0; j < nbcmd; j++) {
					add_history(cmd[j]);
					free(cmd[j]);
				}
				free(cmd);
				cmd = NULL;
			}
		}
		cmd = malloc(sizeof(char *));
		cmd[0] = malloc(strlen(next_history()->line)+1);
		strcpy(cmd[0], current_history()->line);
		if(regpresent(reg, cmd[0])){
			++i;
		}
		if(strcmp(cmd[0],"brebis:") == 0 && i == 0){
			if(brebis == -1)
				brebis = where_history();
			else{
				slog("Error brebis already declared");
				return False;
			}
		}
		if(strcmp(cmd[0], "finchevre;") == 0 && i != 0){
			--i;
			cmd[0][0] = '\0';
		}
	} while (i != 0 || strcmp(cmd[0],"finchevre;") != 0);
	finchevre = where_history();
	s_var cond = processOperation(arg,0);
	if(cond.undefined){
		return False;
	}
	castBool(&cond);
	if(cond.value.vb){
		history_set_pos(chevreau+1);
		while (where_history() != finchevre && where_history() != brebis) {
			if(!interpret_command(current_history()->line, True)){
				history_set_pos(finchevre);
				return False;
			}
			history_set_pos(where_history()+1);
		}
	}else if(brebis != -1){
		history_set_pos(brebis+1);
		while(where_history() != finchevre){
			if(!interpret_command(current_history()->line, True)){
				history_set_pos(finchevre);
				return False;
			}
			history_set_pos(where_history()+1);
		}
	}
	history_set_pos(finchevre);
	return True;
}

boolean fromage(char *arg, boolean history){
	int fromage, fin;
	int i = 0;
	char **cmd = NULL;
	char *histline;
	int nbcmd;
	s_var cond;
	fromage = where_history() + 1;
	do{
		if(cmd != NULL) {
			free(cmd[0]);
			free(cmd);
		}
		if(history_offset == history_length-1) {
			nbcmd = 0;
			while(nbcmd == 0){
				cmd = NULL;
				nbcmd = getinput(in, &cmd);
				for (int j = 0; j < nbcmd; j++) {
					add_history(cmd[j]);
					free(cmd[j]);
				}
				free(cmd);
				cmd = NULL;
			}
		}
		cmd = malloc(sizeof(char *));
		cmd[0] = malloc(strlen(next_history()->line) + 1);
		strcpy(cmd[0], current_history()->line);
		if(strcmp(cmd[0], "finfromage;") == 0 && i != 0){
			--i;
			continue;
		}
		if(regpresent(cmd[0], "fromage")){
			++i;
			continue;
		}
	}while(i != 0 || strcmp(cmd[0], "finfromage;") != 0);
	free(cmd[0]);
	free(cmd);
	fin = where_history()+1;
	cond = processOperation(arg, 0);
	if(cond.undefined){
		return False;
	}
	castBool(&cond);
	while(cond.value.vb){
		for(i = fromage + 1; i < fin; ++i){
			histline = malloc(strlen(history_get(i)->line)+1);
			strcpy(histline, history_get(i)->line);
			if(!interpret_command(histline, True)){
				free(histline);
				return False;
			}
		}
		cond = processOperation(arg, 0);
		if(cond.undefined){
			return False;
		}
		castBool(&cond);
	}
	return True;
}