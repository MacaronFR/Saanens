#include <variable.h>
#include <interpret.h>

extern s_vars vartab;

int main(int argc,char **argv){
	using_history();
	char input[1024];
	printf("Saanens V0.1\n");
	while(strcmp(input,"exit") != 0){
		printf("> ");
		scanf("%[^\n]",input);
		fflush(stdin);
		interpret_command(input);
		//printf("Name %s, type %s value %d\n",vartab.tab[0].name,get_name_from_type(vartab.tab[0].type),vartab.tab[0].value.ve);
	}
	return 0;
}
