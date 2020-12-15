#include <keyEvent.h>
#include <stdlib.h>

G_MODULE_EXPORT gboolean keypressInterpretor(GtkWidget *widget, GdkEvent *event, gpointer user_data){
	GtkTextView *textView = GTK_TEXT_VIEW(widget);
	printf("%s\n",gdk_keyval_name(event->key.keyval));
	GdkRectangle *strong = NULL, *weak = NULL;
	strong = g_malloc(sizeof(GdkRectangle));
	weak = g_malloc(sizeof(GdkRectangle));
	gtk_text_view_get_cursor_locations(textView, NULL, strong, weak);
	if(event->key.keyval == GDK_KEY_Home){
		return homePush(textView);
	}
	if(event->key.keyval == GDK_KEY_BackSpace || event->key.keyval == GDK_KEY_Left){
		if(strong->x <= 14){ //2 char from begining of line
			printf("\a");
			return TRUE;
		}
	}
	if(event->key.keyval == GDK_KEY_Return){
		gchar *contents;
		static gchar *locale;
		GtkTextIter start, end;
		GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
		gtk_text_buffer_get_bounds(buffer, &start, &end);
		gtk_text_iter_forward_chars(&start, 2);
		contents = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
		locale = g_locale_from_utf8(contents, -1, NULL, NULL, NULL);
		g_free(contents), contents = NULL;
		free(locale);
		return TRUE;
	}
	return FALSE;
}

gboolean homePush(GtkTextView *textView){
	return TRUE;
}