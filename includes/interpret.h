#ifndef SAANENS_INTERPRET_H
#define SAANENS_INTERPRET_H

#include <processop.h>
#include <condboucle.h>

boolean interpret_command(char *command, boolean history);
boolean declare(char *command);
boolean detect_keyword(char *command, boolean history);
boolean detect_operation(char *command, boolean history);
s_var processOperation(const char *op, s_cat level);

#endif //SAANENS_INTERPRET_H