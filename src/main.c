#include <variable.h>
#include <interpret.h>

extern s_vars vartab;

int main(int argc,char **argv){
	s_var temp;
	vartab.length = 2;
	vartab.tab = malloc(sizeof(s_var) * 2);
	temp.name = "TEST";
	temp.type = 1;
	temp.value.undefined = True;
	vartab.tab[0] = temp;
	temp.name = "TEST2";
	temp.type = 2;
	temp.value.undefined = True;
	temp.value.ve = 10;
	printf("%d",temp.value.undefined);
	vartab.tab[1] = temp;
	int test1 = 7;
	printf("***%d***\n",vartab.length);
	if(!new_var(&test1, "TEST3", 5, S_ENT)){
		perror("Error on new value");
	}
	interpret_command("int a = 5;");
	printf("\n**%d**\n", vartab.length);
	char * type;
	for(int i = 0; i < vartab.length; ++i){
		type = get_name_from_type(vartab.tab[i].type);
		printf("Name = %s, Type = %s\n", vartab.tab[i].name, type);
	}
	return 0;
}
