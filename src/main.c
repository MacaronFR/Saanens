#include <variable.h>
#include <interpret.h>

extern s_vars vartab;

int main(int argc,char **argv){
	char input[1024];
	printf("Saanens V0.1\n");
	while(strcmp(input,"exit") != 0){
		printf("> ");
		scanf("%s",input);
		fflush(stdin);
		interpret_command(input);
	}
	return 0;
}
