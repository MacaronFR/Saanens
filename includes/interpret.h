#ifndef SAANENS_INTERPRET_H
#define SAANENS_INTERPRET_H

#include <gtk/gtk.h>
#include <string.h>
#include <variable.h>
#include <regex.h>

gboolean interpret_command(gchar *command);
gboolean is_declaration(gchar *command);
gboolean is_affectation(gchar *command);
int regtest(const char *exp, gchar *command);

#endif //SAANENS_INTERPRET_H