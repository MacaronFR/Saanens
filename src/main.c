#include <variable.h>
#include <interpret.h>

int main(int argc,char **argv){
	s_vars *test = malloc(sizeof(s_vars));
	s_var temp;
	test->length = 2;
	test->vars = malloc(sizeof(s_var) * 2);
	temp.name = "TEST";
	temp.type = 1;
	temp.var = NULL;
	test->vars[0] = temp;
	temp.name = "TEST2";
	temp.type = 2;
	temp.var = NULL;
	test->vars[1] = temp;
	int test1 = 7;
	new_var(&test1, "TEST3", 5, 3, test);
	for(int i = 0; i < test->length; ++i){
		printf("Name : %s ; Type %d\n",test->vars[i].name,test->vars[i].type);
	}
	printf("index of TEST2 : %d",get_index("TEST2",5,test));
	interpret_command("int a = 5;");
	free(test->vars);
	free(test);
	return 0;
}