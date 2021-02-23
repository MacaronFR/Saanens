#include <interpret.h>

extern s_vars vartab;

boolean interpret_command(char *command, boolean history){
	trim(command);
	if (detect_keyword(command, history)) {
		return True;
	} else if (detect_operation(command, history)) {
		return True;
	} else if (strcmp(command, "exit;") == 0) {
		return False;
	}
	return True;
}

boolean declare(char *command){ //Fonction declaration de variable
	char *exp = "^[ \t\n\r\f]*(int|float|char|string|bool)[ \t\n\r\f]+([a-zA-Z][a-zA-Z0-9_]*)(?:[ \t\n\r\f]*=[ \t\n\r\f]*(.+[^ \t\n\r\f]*)[ \t\n\r\f]*)?;";
	char *info[3];
	s_var val;
	s_var *nvar;
	int start = 0;
	int end = 0;
	regmatch_t *pmatch = NULL;
	if(!regretrieve(exp,command,&pmatch)){//Recupération des infos importantes de la commande
		slog("Invalid declaration\n");
		return False;
	}
	process_pmatch(command, pmatch, 3, info); //Process des pmatch vers des chaines
	type typeid = get_type_from_name(info[0], strlen(info[0])); //Recuperation du type
	free(info[0]);
	if(typeid == S_NOT) { //si le type est invalide
		free(info[1]);
		free(info[2]);
		slog("Invalid type\n");
		return False;
	}
	if(get_index(info[1],sizeof(info[1])) != vartab.length){ //vérification de la non existence de la variable
		slog("Variable %s already declared\n",info[1]);
		free(info[1]);
		free(info[2]);
		return False;
	}
	nvar = new_var(info[1], sizeof(info[1]), typeid); //déclaration de la variable
	free(info[1]);
	if(nvar == NULL) { //Vérification pour pas d'erreur durant la déclaration
		free(info[2]);
		slog("Error while declaring new variable\n");
		return False;
	}
	if(*(info[2]) != '\0'){ //Si il y a une affectation
		val = processOperation(info[2], 0);
		if(val.undefined){
			free(info[2]);
			return False;
		}
		if(val.type != nvar->type){
			cast(&val, nvar->type);
		}
		if(!assign_value(nvar,val.value)){ //Affectation de la variable
			slog("Can't assign value %s to var %s\n",info[2],nvar->name);
			free(info[2]);
			return False;
		}
		free(info[2]);
		return True;
	}
	free(info[2]);
	return True;
}

boolean detect_keyword(char *command, boolean history){
	char *exptype = "^[ \t\n\r\f]*(int|float|char|string|bool)[ \t\n\r\f]+([a-zA-Z][a-zA-Z0-9]*)"; //Regexp pour type
	char *expcondboucle = "^[ \t\n\r\f]*(bouc|fromage|lait|chevre|troupeau|cassemire)[ \t\n\r\f]*[(].*[)][ \t\n\r\f]*:[ \t\n\r\f]*$"; //Regexp pour boucle/condition
	if(regpresent(exptype, command)) { //Si type
		if(declare(command)){
		}
		return True;
	}else if(regpresent(expcondboucle,command)){ //Si cond/boucle
		if(condboucle(command,history)){
			return True;
		}
		return True;
	}else if(regpresent("^print[ \n\t\r\f]*[(]([^)]+)[)][ \n\t\r\f]*;$",command)){//Si print
		regmatch_t *pmatch = NULL;
		char *info[1];
		s_var toprint;
		if(regretrieve("^print[ \n\t\r\f]*[(]([^)]+)[)][ \n\t\r\f]*;$", command, &pmatch)){
			process_pmatch(command, pmatch, 1, info);
			toprint = processOperation(info[0], 0);
			if(toprint.undefined){
				return False;
			}
			if(toprint.type != S_CHAINE){
				cast(&toprint, S_CHAINE);
			}
			print(toprint.value.vs);
			free(toprint.value.vs);
			return True;
		}
	}else if(strcmp(command, "clearlog") == 0){
		clearlog();
	}
	return False;
}

boolean detect_operation(char *command, boolean history){
	char *reg = "[=/*+<>&|-]";
	if(regpresent(reg, command)){
		if(command[strlen(command)-1] == ';'){
			command[strlen(command)-1] = '\0';
		}
		s_var res = processOperation(command, 0);
		//TODO log pour voir res d'une opération;
		return True;
	}
	return False;
}

s_var processOperation(const char *command, s_cat lev){
	char *reglog = "[|&]{2}";
	char *regaff = "[a-zA-Z][a-zA-Z0-9_]*[ \t\n\r\f]*=[^=]+";
	char *regcomp = "[=><]";
	char *regaddsub = "[+-]";
	char *regmod = "%";
	char *regmuldiv = "[*/]";
	char *regfloat = "^([0-9]*[.][0-9]+)|([0-9]*[.][0-9]+)$";
	char *regint = "^[0-9]+$";
	char *regchar = "'([^\\]|\\[abfnrtv\\'\"?])'";
	char *regstr = "\"(.*)\"";
	char *regbool = "^True|False$";
	char *regvar = "[a-zA-Z][a-zA-Z0-9_]*";
	s_var res;
	while(check_parenthese(command)){
		char *tmp = execute_parenthese(command);
		if(tmp == NULL){
			returnNillVar;
		}
		command = tmp;
	}
	if(regpresent(reglog, command) && lev <= S_LOG){
		return processLog(command);
	}else if(regpresent(regaff, command) && lev <= S_AFF){
		return processAff(command);
	}else if(regpresent(regcomp, command) && lev <= S_COMP){
		return processComp(command);
	}else if(regpresent(regaddsub, command) && lev <= S_ADSB){
		return processAddSub(command);
	}else if(regpresent(regmod, command) && lev <= S_MOD){
		return processMod(command);
	}else if(regpresent(regmuldiv, command) && lev <= S_MLDV){
		return processMulDiv(command);
	}else if(regpresent(regfloat, command)){
		res.type = S_FLOT;
		res.undefined = False;
		res.value.vf = parseFloat(command);
		return res;
	}else if(regpresent(regint, command)){
		res.type = S_ENT;
		res.undefined = False;
		res.value.ve = parseInt(command);
		return res;
	}else if(regpresent(regchar, command)) {
		res.type = S_CAR;
		res.undefined = False;
		res.value.vc = parseChar(command);
		return res;
	}else if(regpresent(regstr, command)) {
		char *s = malloc(strlen(command));
		strcpy(s, command + 1);
		s[strlen(s) - 1] = '\0';
		res.value.vs = parseString(s);
		if (res.value.vs != NULL) {
			res.type = S_CHAINE;
			res.undefined = False;
			return res;
		}
		returnNillVar;
	}else if(regpresent(regbool, command)){
		res.undefined = False;
		res.type = S_BOOL;
		if(strcmp(command, "True") == 0){
			res.value.vb = True;
			return res;
		}
		if(strcmp(command, "False") == 0){
			res.value.vb = False;
			return res;
		}
		returnNillVar;
	}else if(regpresent(regvar, command)){
		s_var *p = resolve_var(command);
		return (p==NULL)?(s_var){S_NOT, .undefined=True}:*p;
	}
	slog("%hhd", regpresent(regchar, command));
	slog("Error unrecognized command \"%s\"\n", command);
	returnNillVar;
}