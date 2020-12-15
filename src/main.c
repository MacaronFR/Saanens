#include <keyEvent.h>
#include <variable.h>

G_MODULE_EXPORT void end_program(GtkWidget *object, gpointer user_data);

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
	free(test->vars);
	free(test);
	/*
	GtkBuilder *builder;
	GtkWidget *window;
	GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;
	gtk_init(&argc,&argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "../glade/test.glade",NULL);
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	if(window == NULL){
		perror("Unknow widget window");
		return 1;
	}
	gtk_builder_connect_signals(builder, window);
	g_object_unref(builder);

	provider = gtk_css_provider_new();
	display = gdk_display_get_default();
	screen = gdk_display_get_default_screen(display);
	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider),"../style/style.css", NULL);

	gtk_widget_show(window);
	gtk_main();
	 */
	return 0;
}

G_MODULE_EXPORT void end_program(GtkWidget *object, gpointer user_data){
	gtk_main_quit();
}