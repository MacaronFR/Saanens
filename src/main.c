#include <variable.h>
#include <interpret.h>

FILE *in;
extern s_vars vartab;

int main(int argc,char **argv){
	in = stdin;
	printf("#%s#\n","'([^\\\\]|\\\\[abfnrtv\\\\'\"?])'");
	if(argc == 2){
		in = fopen(argv[1], "rb");
	}
	clearlog();
	using_history();
	char **cmd;
	int nbcmd;
	printf("Saanens V0.1\n");
	boolean quit = False;
	while(!quit){
		if(in == stdin) {
			printf("> ");
		}
		cmd = NULL;
		nbcmd = getinput(in, &cmd);
		if(nbcmd == 1){
			trim(cmd[0]);
			add_history(cmd[0]);
			if (history_length != 1)
				history_offset++;
			quit = !interpret_command(cmd[0], False);
		}else {
			int hist = where_history();
			for (int i = 0; i < nbcmd; i++) {
				trim(cmd[i]);
				add_history(cmd[i]);
				if (history_length != 1)
					history_offset++;
			}
			history_set_pos(hist+1);
			while(where_history() != history_length - 1) {
				quit = !interpret_command(cmd[0], True);
				if(quit)
					break;
			}
		}
		fflush(stderr);
		fflush(stdout);
		//printf("Name %s, type %s value %d\n",vartab.tab[0].name,get_name_from_type(vartab.tab[0].type),vartab.tab[0].value.ve);
	}
	return 0;
}
