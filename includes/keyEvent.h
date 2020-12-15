#ifndef SAANENS_KEYEVENT_H
#define SAANENS_KEYEVENT_H

#include <gtk/gtk.h>

G_MODULE_EXPORT gboolean keypressInterpretor(GtkWidget *textView, GdkEvent *event, gpointer user_data);
gboolean homePush(GtkTextView *textView);

#endif //SAANENS_KEYEVENT_H