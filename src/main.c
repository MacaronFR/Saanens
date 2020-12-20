#include <variable.h>
#include <interpret.h>

int main(int argc,char **argv){
	s_var temp;
	vartab.length = 2;
	vartab.vars = malloc(sizeof(s_var) * 2);
	temp.name = "TEST";
	temp.type = 1;
	temp.var = NULL;
	vartab.vars[0] = temp;
	temp.name = "TEST2";
	temp.type = 2;
	temp.var = NULL;
	vartab.vars[1] = temp;
	int test1 = 7;
	if(!new_var(&test1, "TEST3", 5, S_ENT)){
		perror("Error on new var");
	}
	interpret_command("int a = 5;");
	printf("\n**%d**\n", vartab.length);
	char * type;
	for(int i = 0; i < vartab.length; ++i){
		type = get_name_from_type(vartab.vars[i].type);
		printf("Name = %s, Type = %s\n",vartab.vars[i].name, type);
	}
	return 0;
}