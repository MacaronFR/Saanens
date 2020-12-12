#include <gtk/gtk.h>

G_MODULE_EXPORT void end_program(GtkWidget *object, gpointer user_data);
G_MODULE_EXPORT char *send_command(GtkWidget *textView, GdkEvent *event, gpointer user_data);

int main(int argc,char **argv){
	GtkBuilder *builder;
	GtkWidget *window;
	GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;
	gtk_init(&argc,&argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "../test.glade",NULL);
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
	gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider),"../src/style.css", NULL);

	gtk_widget_show(window);
	gtk_main();
	return 0;
}

G_MODULE_EXPORT void end_program(GtkWidget *object, gpointer user_data){
	gtk_main_quit();
}

G_MODULE_EXPORT char *send_command(GtkWidget *textView, GdkEvent *event, gpointer user_data){
	if(event->key.keyval == GDK_KEY_Return) {
		gchar *contents, *locale;
		GtkTextIter start, end;
		GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
		gtk_text_buffer_get_bounds(buffer, &start, &end);
		contents = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
		locale = g_locale_from_utf8(contents, -1, NULL, NULL, NULL);
		printf("command : %s\n", locale);
		g_free(contents), contents = NULL;
		return locale;
	}
}