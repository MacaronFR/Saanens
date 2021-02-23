#include <condboucle.h>

extern FILE *in;

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

boolean chevre(char *arg, boolean history){ //execute condition
	char reg[] = "^(chevre|breche).*[(](.*)[)].*:";
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
		return -1;
	}
	chevreau = where_history();
	do{
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
		cmd[0] = malloc(strlen(next_history()->line));
		strcpy(cmd[0], current_history()->line);
		if(regpresent(reg, cmd[0])){
			if(regpresent("breche", cmd[0])){
				if(i == 0) {
					if (brebis == -1)
						brebis = where_history();
					else {
						slog("Error already have brebis");
						return False;
					}
				}
			}
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
	if( cond.value.vb){
		history_set_pos(chevreau+1);
		while (where_history() != finchevre && where_history() != brebis) {
			if(!interpret_command(current_history()->line, True)){
				history_set_pos(finchevre);
				return False;
			}
			printf("%s*\n",current_history()->line);
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