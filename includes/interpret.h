#ifndef SAANENS_INTERPRET_H
#define SAANENS_INTERPRET_H

#include <gtk/gtk.h>
#include <string.h>
#include <variable.h>
#include <regex.h>

#define regpresent(exp, command) (s_testreg(exp, command, NULL, REG_NOSUB | REG_EXTENDED))
#define regretrieve(exp, command, pmatch) (s_testreg(exp, command, pmatch, REG_EXTENDED))

boolean interpret_command(gchar *command);
boolean is_declaration(gchar *command);
boolean is_affectation(gchar *command);
boolean s_testreg(const char *exp, gchar *command, regmatch_t **pmatch,int cflags);
boolean declare(gchar *command);

#endif //SAANENS_INTERPRET_H