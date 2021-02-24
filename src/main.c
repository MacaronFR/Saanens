#include <variable.h>
#include <interpret.h>

FILE *in;
FILE *out;
extern s_vars vartab;

int check_options(int argc, char **argv){
	for(int i = 1; i < argc; ++i){
		if(argv[i][0] == '-'){
			switch (argv[i][1]){
				case 'h': printf("Saanens V1.0\nUsage :\n\tSaanens <file> [-o output-file]->Interpret <file> with optional-output file\n\tSaanens -h -> Display this help\n\tSaanens -v -> Show actual version");return 1;
				case 'v': printf("Saanens V1.0\nMade by TURBIEZ Denis and BOUDEDJA Kamilia");return 1;
				case 'o': out = fopen(argv[i+1],"wb");if(out == NULL){printf("Error in opening output file : %s",argv[i+1]);exitSaanens();}return 0;
				default: printf("Error. To see option available type Saanens -h");return -1;
			}
		}else{
			in = fopen(argv[i], "rb");
			if(in == NULL){
				in = stdout;
			}
		}
	}
	return 0;
}

int main(int argc,char **argv){
	in = stdin;
	out = stdout;
	int res = check_options(argc, argv);
	if(argc >= 2){
		if(res == -1){
			return -1;
		}
		if(res == 1){
			return 0;
		}
	}
	clearlog();
	using_history();
	char **cmd;
	int nbcmd;
	printf("Saanens V1.0\n");
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
	}
	if(in != stdin)
		fclose(in);
	if(out != stdin)
		fclose(out);
	return 0;
}
